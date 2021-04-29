import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property bool busy: false
    property DiscussionComment comment

    id: page
    allowedOrientations: Orientation.All

    // model
    DiscussionCommentsModel {
        id: commentsModel
        identifier: comment.nodeId
        modelType: DiscussionComment.Reply
    }

    Connections {
        target: commentsModel
        onCommentsAdded: {
            page.busy = false
            updateComments(lastIndex, count)
        }
    }

    function updateComments(index, count) {
        for (var i=index; i < (index + count); i++) {
            var comment = commentsModel.commentAt(i)

            if (comment === undefined) continue

            var component = Qt.createComponent("../components/DiscussionCommentItem.qml")

            if (component.status !== Component.Ready)
                console.log("NOT READY")

            var obj = component.createObject(commentsColumn, {comment: comment})
        }
    }

    //

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.busy = true
                    refresh()
                }
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height + commentsColumn.height

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Thread")
            }

            CommentItem {
                authorAvatar: comment.author.avatarUrl
                authorLogin: comment.author.login
                body: comment.body
                edited: comment.edited
                timeSpan: comment.updatedAtTimeSpan
            }

            SectionHeader {
                text: qsTr("Reactions")
            }

            ReactionsItem {
                node: comment

                onClicked: {
                    if (!(comment.viewerAbilities & Viewer.CanReact)) return;

                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"), {
                                                    reactions: discussion.viewerReactions
                                                })

                    dialog.accepted.connect(function() {
                        if (discussion.viewerReactions === dialog.reactions) return;

                        SailHub.api().updateReactions(
                                    discussion.nodeId,
                                    discussion.viewerReactions,
                                    dialog.reactions)

                        discussion.updateReactionCount(dialog.reactions)
                        discussion.viewerReactions = dialog.reactions
                    })
                }
            }

            SectionHeader {
                text: qsTr("Replies")
            }
        }

        Column {
            id: commentsColumn
            anchors.top: headerColumn.bottom
            width: parent.width
            spacing: Theme.paddingSmall
        }

        VerticalScrollDecorator {}


        PushUpMenu {
            busy: commentsModel.loading

            MenuItem {
                text: qsTr("Write Reply")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addDiscussionComment(dialog.body, comment.discussionId, comment.nodeId)
                    })
                }
            }

            MenuItem {
                visible: commentsModel.hasNextPage
                text: qsTr("Load more (%n to go)", "", commentsModel.totalCount - commentsColumn.children.length)
                onClicked: getComments()
            }
        }
    }

    function getComments() {
        page.busy = true;
        SailHub.api().getPaginationModel(commentsModel)
    }

    function refresh() {
        commentsModel.reset()
        for(var i = commentsColumn.children.length; i > 0; i--) {
            commentsColumn.children[i-1].destroy()
        }
        getComments()
    }

    Connections {
        target: SailHub.api()
        onDiscussionCommentAdded: refresh()
        onDiscussionCommentDeleted: refresh()
    }


    Component.onCompleted: refresh()
}
