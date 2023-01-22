import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property var assigneeIds: []
    property string baseRefName
    property string body
    property string title
    property var labelIds: []
    //property bool maintainerCanModify: true
    property string milestoneId
    property var projectIds: []
    property string state

    function getVariables() {
        const vars = {
            clientMutationId: viewerProfile.nodeId,
            pullRequestId: nodeId,
            //maintainerCanModify: maintainerCanModify
        }

        if (baseRefName.length > 0) vars.baseRefName = baseRefName
        if (body.length > 0) vars.body = body
        if (title.length > 0) vars.title = title
        if (assigneeIds.length > 0) vars.assigneeIds = assigneeIds
        if (labelIds.length > 0) vars.labelIds = labelIds
        if (milestoneId.length > 0) vars.milestoneId = milestoneId
        if (projectIds.length > 0) vars.projectIds = projectIds
        if (state.length > 0) vars.state = state

        return vars
    }

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UpdatePullRequestInput!) {
                                    updatePullRequest(input: $input) {
                                        pullRequest {
                                            title
                                            body
                                        }
                                    }
                                }',
                        variables: {
                            input: getVariables()
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to merge pull request"
                            notify.show(qsTrId("id-failed-to-merge-pull-request"))
                            return
                        }

                        result = data
                    })
    }
}
