import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    resultNodePath: "reopenIssue"

    query: 'mutation($input: ReopenIssueInput!) {
                reopenIssue(input: $input) {
                    issue {
                        state
                        stateReason
                    }
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
