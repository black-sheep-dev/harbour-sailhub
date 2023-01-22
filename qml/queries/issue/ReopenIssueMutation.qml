import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: ReopenIssueInput!) {
                                    reopenIssue(input: $input) {
                                        issue {
                                            state
                                            stateReason
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                issueId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to reopen issue"
                            notify.show(qsTrId("id-failed-to-reopen-issue"))
                            return
                        }

                        result = data.reopenIssue
                    })
    }
}
