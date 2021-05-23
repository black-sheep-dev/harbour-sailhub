import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../tools/"

ListItem {
    id: commentItem
    property Comment comment
    property string parentId

    width: parent.width
    contentHeight: contentColumn.height + 2*Theme.paddingSmall

    RemorseItem { id: remorse }

    menu: ContextMenu {
        MenuItem {
            visible: comment.viewerAbilities & Viewer.CanDelete
            text: qsTr("Delete")
            onClicked: remorse.execute(commentItem, qsTr("Deleting comment"), function() {
                SailHub.api().deleteComment(comment.nodeId)
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
                    SailHub.api().updateComment(comment)
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
                    SailHub.api().addComment(dialog.body, parentId)
                })
            }
        }
    }

    MarkdownParser {
        id: markdownParser
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

        MarkdownLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            text: markdownParser.parse(comment.body)
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


