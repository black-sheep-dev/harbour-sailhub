import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import ".."

ListItem {
    id: commentItem
    property Comment comment
    property string parentId

    width: parent.width
    contentHeight: contentColumn.height + 2*Theme.paddingSmall

    menu: ContextMenu {
        MenuItem {
            visible: comment.viewerAbilities & Viewer.CanDelete
            //% "Delete"
            text: qsTrId("id-delete")
            //% "Deleting comment"
            onClicked: commentItem.remorseAction(qsTrId("id-deleting-comment"), function() {
                SailHub.api().deleteComment(comment.nodeId)
            })
        }
        MenuItem {
            visible: comment.viewerAbilities & Viewer.CanUpdate
            //% "Edit"
            text: qsTrId("id-edit")
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                edit: true,
                                                body: comment.body
                                            })

                dialog.accepted.connect(function() {
                    comment.body = dialog.body
                    SailHub.api().updateComment(comment)
                })
            }
        }
        MenuItem {
            //% "Quote reply"
            text: qsTrId("id-quote-reply")
            onClicked: {
                const text = ">"+ comment.body + "\n\n";
                var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                edit: false,
                                                body: text
                                            })

                dialog.accepted.connect(function() {
                    SailHub.api().addComment(dialog.body, parentId)
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
                    //% "Edited"
                    return comment.updatedAtTimeSpan + " - " + qsTrId("id-edited")

                return comment.createdAtTimeSpan
            }

            onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), {
                                          login: comment.author.login
                                      })
        }

        MarkdownLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            text: MarkdownParser.parse(comment.body)
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
}


