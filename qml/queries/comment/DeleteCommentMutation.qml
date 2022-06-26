import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    resultNodePath: "deleteIssueComment"

    query: 'mutation($input: DeleteIssueCommentInput!) {
                deleteIssueComment(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "id": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
