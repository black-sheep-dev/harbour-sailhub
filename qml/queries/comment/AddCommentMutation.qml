import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: AddCommentInput!) {
                                    addComment(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                subjectId: nodeId,
                                body: body
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to add comment"
                            notify.show(qsTrId("id-failed-to-add-comment"))
                            return
                        }

                        result = data.addComment
                    })
    }
}
