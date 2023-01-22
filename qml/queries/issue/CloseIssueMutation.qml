import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string stateReason: ""

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: CloseIssueInput!) {
                                    closeIssue(input: $input) {
                                        issue {
                                            state
                                            stateReason
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                issueId: nodeId,
                                stateReason: stateReason
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to close issue"
                            notify.show(qsTrId("id-failed-to-close-issue"))
                            return
                        }

                        result = data.closeIssue
                    })
    }
}

