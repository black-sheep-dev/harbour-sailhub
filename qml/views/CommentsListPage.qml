import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../queries/comment/"

ListPage {
    property string nodeType

    function addComment() {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

        dialog.accepted.connect(function() {
            addCommentMutation.body = dialog.body
            Api.request(addCommentMutation)
        })
    }

    function updateComment(id, body) {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                        edit: true,
                                        body: body
                                    })

        updateCommentMutation.nodeId = id

        dialog.accepted.connect(function() {
            updateCommentMutation.body = dialog.body
            Api.request(updateCommentMutation)
        })
    }

    function deleteComment(id) {
        deleteCommentMutation.nodeId = id
        Api.request(deleteCommentMutation)
    }

    function replyToComment(body) {
        const text = ">"+ body + "\n\n"
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                        edit: false,
                                        body: text
                                    })

        dialog.accepted.connect(function() {
            addCommentMutation.body = dialog.body
            Api.request(addCommentMutation)
        })
    }

    id: page

    showBusyIndicator: false
    paginationCount: 100

    itemsPath: ["node", "comments", "nodes"]

    itemsQuery: '
query(
    $nodeId: ID!,
    $itemCount: Int = 20,
    $itemCursor: String = null) {
    node(id: $nodeId) {
        ... on ' + nodeType + ' {
            id
            comments(
                first: $itemCount,
                after: $itemCursor
                ) {
                nodes {
                    id
                    author {
                        avatarUrl
                        login
                    }
                    body
                    bodyText
                    createdAt
                    lastEditedAt
                    reactionGroups {
                        ... on ReactionGroup {
                            content
                            users {
                                totalCount
                            }
                            viewerHasReacted
                        }
                    }
                    viewerCanDelete
                    viewerCanReact
                    viewerCanUpdate
                    viewerDidAuthor
                }
                totalCount
                pageInfo {
                    hasNextPage
                    endCursor
                }
            }
        }
    }
}'

    RemorsePopup { id: remorse }

    AddCommentMutation {
        id: addCommentMutation
        nodeId: page.nodeId
        onResultChanged: if (error === QueryObject.ErrorNone) refresh()
    }

    DeleteCommentMutation {
        id: deleteCommentMutation
        onResultChanged: if (error === QueryObject.ErrorNone) refresh()
    }

    UpdateCommentMutation {
        id: updateCommentMutation
        onResultChanged: if (error === QueryObject.ErrorNone) refresh()
    }
}
