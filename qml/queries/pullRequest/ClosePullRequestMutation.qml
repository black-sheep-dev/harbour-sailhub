import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: ClosePullRequestInput!) {
                                    closePullRequest(input: $input) {
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
                            //% "Failed to close pull request"
                            notify.show(qsTrId("id-failed-to-close-pull-request"))
                            return
                        }

                        result = data
                    })
    }
}
