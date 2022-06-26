import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    resultNodePath: "deleteIssue"

    query: 'mutation($input: DeleteIssueInput!) {
                deleteIssue(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "issueId": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
