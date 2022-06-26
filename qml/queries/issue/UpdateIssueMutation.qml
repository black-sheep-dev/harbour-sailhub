import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property var assigneeIds: []
    property var labelsIds: []
    property var projectIds: []
    property string milestoneId: ""
    property string nodeId
    property string title: ""
    property string body: ""

    resultNodePath: "updateIssue"

    query: 'mutation($input: UpdateIssueInput!) {
                updateIssue(input: $input) {
                    issue {
                        title
                        body
                    }
                }
            }'

    variables: {
        var input = new Object

        input["input"] = new Object
        input["input"]["clientMutationId"] = viewerProfile.nodeId
        input["input"]["id"] = nodeId
        if (assigneeIds.length > 0) input["input"]["assigneeIds"] = assigneeIds
        if (labelsIds.length > 0) input["input"]["labelsIds"] = labelsIds
        if (projectIds.length > 0) input["input"]["projectIds"] = projectIds
        if (title.length > 0) input["input"]["title"] = title
        if (body.length > 0) input["input"]["body"] = body
        if (milestoneId.length > 0) input["input"]["milestoneId"] = milestoneId

        return input
    }

    onErrorChanged: notification.showErrorMessage(error)
}
