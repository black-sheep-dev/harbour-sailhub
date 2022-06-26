import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string body

    resultNodePath: "addComment"

    query: 'mutation($input: AddCommentInput!) {
                addComment(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "subjectId": nodeId,
            "body": body
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
