import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: DeleteIssueCommentInput!) {
                                    deleteIssueComment(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                id: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to delete comment"
                            notify.show(qsTrId("id-failed-to-delete-comment"))
                            return
                        }

                        result = data.deleteIssueComment
                    })
    }
}
