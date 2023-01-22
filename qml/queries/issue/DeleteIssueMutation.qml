import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: DeleteIssueInput!) {
                                    deleteIssue(input: $input) {
                                        clientMutationId
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
                            //% "Failed to delete issue"
                            notify.show(qsTrId("id-failed-to-delete-issue"))
                            return
                        }

                        result = data.deleteIssue
                    })
    }
}
