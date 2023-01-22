import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: ReopenPullRequestInput!) {
                                    reopenPullRequest(input: $input) {
                                        pullRequest {
                                            state
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                pullRequestId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to reopen pull request"
                            notify.show(qsTrId("id-failed-to-reopen-pull-request"))
                            return
                        }

                        result = data
                    })
    }
}
