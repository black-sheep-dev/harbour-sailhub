import QtQuick 2.0
import Sailfish.Silica 1.0

import "."
import "../queries/"
import "../queries/comment/"

ListPage {
    // Comments mutations
    function addComment() {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

        dialog.accepted.connect(function() {
            addCommentMutation.body = dialog.body
            addCommentMutation.execute()
        })
    }

    function updateComment(id, body, index) {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                        edit: true,
                                        body: body
                                    })

        updateCommentMutation.nodeId = id
        updateCommentMutation.itemIndex = index

        dialog.accepted.connect(function() {
            updateCommentMutation.body = dialog.body
            updateCommentMutation.execute()
        })
    }

    function deleteComment(id, index) {
        deleteCommentMutation.nodeId = id
        deleteCommentMutation.itemIndex = index
        deleteCommentMutation.execute()
    }

    function replyToComment(body) {
        const text = ">"+ body + "\n\n"
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                        edit: false,
                                        body: text
                                    })

        dialog.accepted.connect(function() {
            addCommentMutation.body = dialog.body
            addCommentMutation.execute()
        })
    }

    AddCommentMutation {
        id: addCommentMutation
        nodeId: page.nodeId
        onResultChanged: refresh()
    }

    DeleteCommentMutation {
        id: deleteCommentMutation
        onResultChanged: refresh()
    }

    UpdateCommentMutation {
        id: updateCommentMutation
        onResultChanged: refresh()
    }

    // Reactions mutations
    AddReactionMutation {
        id: addReactionMutation
        onResultChanged: refresh()
    }

    RemoveReactionMutation {
        id: removeReactionMutation
        onResultChanged: refresh()
    }

    function addReaction(id, content, index) {
        addReactionMutation.nodeId = id
        addReactionMutation.content = content
        addReactionMutation.execute()
    }

    function removeReaction(id, content, index) {
        removeReactionMutation.nodeId = id
        removeReactionMutation.content = content
        removeReactionMutation.execute()
    }
}
