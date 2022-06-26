import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string body

    resultNodePath: "updateIssueComment"

    query: 'mutation($input: UpdateIssueCommentInput!) {
                updateIssueComment(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "id": nodeId,
            "body": body
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
