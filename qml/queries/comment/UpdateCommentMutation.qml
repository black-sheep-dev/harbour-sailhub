import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UpdateIssueCommentInput!) {
                                    updateIssueComment(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                id: nodeId,
                                body: body
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to update comment"
                            notify.show(qsTrId("id-failed-to-update-comment"))
                            return
                        }

                        result = data.updateIssueComment
                    })
    }
}
