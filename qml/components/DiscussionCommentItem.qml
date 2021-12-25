import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import ".."

ListItem {
    id: commentItem
    property DiscussionComment comment

    width: parent.width
    contentHeight: contentColumn.height + 2*Theme.paddingSmall

    menu: ContextMenu {
        MenuItem {
            visible: comment.viewerAbilities & Viewer.CanDelete
            text: qsTr("Delete")
            onClicked: commentItem.remorseAction(qsTr("Deleting comment"), function() {
                SailHub.api().deleteDiscussionComment(comment.nodeId)
            })
        }
        MenuItem {
            visible: comment.viewerAbilities & Viewer.CanUpdate
            text: qsTr("Edit")
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                edit: true,
                                                body: comment.body
                                            })

                dialog.accepted.connect(function() {
                    comment.body = dialog.body
                    SailHub.api().updateDiscussionComment(comment)
                })
            }
        }
        MenuItem {
            visible: !comment.isAnswer && (comment.viewerAbilities & Viewer.CanMarkAsAnswer)
            text: qsTr("Mark as answer")
            onClicked: {
                SailHub.api().markDiscussionCommentAsAnswer(comment.nodeId, true)
                comment.isAnswer = true
            }
        }
        MenuItem {
            visible: comment.isAnswer && (comment.viewerAbilities & Viewer.CanUnmarkAsAnswer)
            text: qsTr("Unmark as answer")
            onClicked: {
                SailHub.api().markDiscussionCommentAsAnswer(comment.nodeId, false)
                comment.isAnswer = false
            }
        }
        MenuItem {
            visible: comment.replyToId.length === 0
            text: qsTr("Reply")
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                reply: true
                                            })

                dialog.accepted.connect(function() {
                    SailHub.api().addDiscussionComment(dialog.body, comment.discussionId, comment.nodeId)
                })
            }
        }
        MenuItem {
            text: qsTr("Quote reply")
            onClicked: {
                const text = ">"+ comment.body + "\n\n";
                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                edit: false,
                                                body: text
                                            })

                dialog.accepted.connect(function() {
                    SailHub.api().addDiscussionComment(dialog.body, comment.discussionId, comment.replyToId)
                })
            }
        }
    }

    Column {
        id: contentColumn
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        spacing: Theme.paddingMedium

        AuthorItem {
            id: authorItem

            interactive: true
            avatar: comment.author.avatarUrl
            title: comment.author.login
            subtitle: {
                if (comment.edited)
                    return comment.updatedAtTimeSpan + " - " + qsTr("Edited")

                return comment.createdAtTimeSpan
            }

            onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), {
                                          login: comment.author.login
                                      })
        }

        Row {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingMedium

            Pill {
                visible: comment.isAnswer
                backgroundColor: "#64DD17"
                color: Theme.primaryColor
                icon: "image://theme/icon-s-checkmark"
                text: qsTr("Answer")
            }
        }

        MarkdownLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            text: MarkdownParser.parse(comment.body)
        }

        // replies
        Row {
            visible: comment.replyCount > 0
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingMedium

            Icon {
                id: replyIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-repost"
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - replyIcon.width - replyCounter.width - 2*parent.spacing
                font.pixelSize: Theme.fontSizeExtraSmall
                text: qsTr("Replies")
            }

            Label {
                id: replyCounter
                anchors.verticalCenter: parent.verticalCenter
                text: comment.replyCount
                font.pixelSize: Theme.fontSizeExtraSmall
            }
        }

        ReactionsItem {
            node: comment

            onClicked: {
                if (!(comment.viewerAbilities & Viewer.CanReact)) return;

                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"), {
                                                reactions: comment.viewerReactions
                                            })

                dialog.accepted.connect(function() {
                    if (comment.viewerReactions === dialog.reactions) return;

                    SailHub.api().updateReactions(
                                comment.nodeId,
                                comment.viewerReactions,
                                dialog.reactions)

                    comment.updateReactionCount(dialog.reactions)
                    comment.viewerReactions = dialog.reactions
                })
            }
        }
    }

    onClicked: pageStack.push(Qt.resolvedUrl("../pages/DiscussionCommentPage.qml"), { comment: comment })
}


