import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property var assigneeIds: []
    property var labelsIds: []
    property var projectIds: []
    property string milestoneId: ""
    property string issueTemplate: ""
    property string categoryId
    property string title
    property string body: ""

    resultNodePath: "createIssue"

    query: 'mutation($input: CreateIssueInput!) {
                createIssue(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        var input = new Object

        input["input"] = new Object
        input["input"]["clientMutationId"] = viewerProfile.nodeId
        input["input"]["categoryId"] = categoryId
        input["input"]["title"] = title
        if (body.length > 0) input["input"]["body"] = body
        if (assigneeIds.length > 0) input["input"]["assigneeIds"] = assigneeIds
        if (labelsIds.length > 0) input["input"]["labelsIds"] = labelsIds
        if (projectIds.length > 0) input["input"]["projectIds"] = projectIds
        if (milestoneId.length > 0) input["input"]["milestoneId"] = milestoneId
        if (issueTemplate.length > 0) input["input"]["issueTemplate"] = issueTemplate

        return input
    }

    onErrorChanged: notification.showErrorMessage(error)
}
