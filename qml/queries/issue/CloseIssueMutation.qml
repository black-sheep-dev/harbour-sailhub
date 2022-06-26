import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string stateReason: ""

    resultNodePath: "closeIssue"

    query: 'mutation($input: CloseIssueInput!) {
                closeIssue(input: $input) {
                    issue {
                        state
                        stateReason
                    }
                }
            }'

    variables: {
        var input = new Object

        input["input"] = new Object
        input["input"]["clientMutationId"] = viewerProfile.nodeId
        input["input"]["issueId"] = nodeId
        if (stateReason.length > 0) input["input"]["stateReason"] = stateReason

        return input
    }

    onErrorChanged: notification.showErrorMessage(error)
}
