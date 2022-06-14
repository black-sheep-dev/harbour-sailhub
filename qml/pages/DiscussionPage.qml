import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property bool busy: false
    property string nodeId
    property Discussion discussion

    id: page
    allowedOrientations: Orientation.All

    // model
    DiscussionCommentsModel {
        id: commentsModel
        identifier: discussion.nodeId
        modelType: DiscussionComment.Comment
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
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getDiscussion(page.nodeId)
                }
            }
            MenuItem {
                visible: discussion.viewerAbilities & Viewer.CanUpdate
                //% "Edit"
                text: qsTrId("id-edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditDiscussionDialog.qml"), {
                                                    edit: true,
                                                    title: discussion.title,
                                                    body: discussion.body
                                                })

                    dialog.accepted.connect(function() {
                        discussion.title = dialog.title
                        discussion.body = dialog.body
                        SailHub.api().updateDiscussion(discussion)
                    })
                }
            }

            MenuItem {
                visible: discussion.viewerAbilities & Viewer.CanDelete
                //% "Delete"
                text: qsTrId("id-delete")
                //% "Deleting discussion"
                onClicked: remorse.execute(qsTrId("id-deleting-discussion"), function() {
                    SailHub.api().deleteDiscussion(discussion.nodeId)
                })
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height + commentsColumn.height

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                //% "Discussion"
                title: qsTrId("id-discussion")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                height: Theme.itemSizeSmall
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    width: parent.height / 2
                    height: width
                    source: discussion.author.avatarUrl
                    anchors.verticalCenter: parent.verticalCenter

                    fallbackItemVisible: false

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: discussion.repository + " #" + discussion.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: discussion.title
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Image {
                    id: closedIcon
                    source: discussion.categoryEmoji
                }

                Label {
                    width: parent.width - closedIcon.width - parent.spacing
                    anchors.verticalCenter: closedIcon.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor

                    text: discussion.category
                }
            }

            Row {
                visible: discussion.locked
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                LockReasonPill {
                    lockReason: discussion.activeLockReason
                }
            }

            CommentItem {
                authorAvatar: discussion.author.avatarUrl
                authorLogin: discussion.author.login
                body: discussion.body
                edited: discussion.edited
                timeSpan: discussion.updatedAtTimeSpan
            }

            SectionHeader {
                //% "Reactions"
                text: qsTrId("id-reactions")
            }

            ReactionsItem {
                node: discussion

                onClicked: {
                    if (!(discussion.viewerAbilities & Viewer.CanReact)) return;

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
                //% "Comments"
                text: qsTrId("id-comments")
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
                enabled: !discussion.locked
                //% "Write comment"
                text: qsTrId("id-write-comment")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addDiscussionComment(dialog.body, commentsModel.identifier)
                    })
                }
            }

            MenuItem {
                visible: commentsModel.hasNextPage
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", commentsModel.totalCount - commentsColumn.children.length)
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
        onDiscussionAvailable: {
            if (discussion.nodeId !== page.nodeId) return

            page.discussion = discussion;
            refresh()
        }
        onDiscussionDeleted: pageStack.navigateBack()
        onDiscussionCommentAdded: refresh()
        onDiscussionCommentDeleted: refresh()
    }


    Component.onCompleted: SailHub.api().getDiscussion(page.nodeId)
}
