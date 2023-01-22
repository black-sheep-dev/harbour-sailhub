import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId


    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: DeleteDiscussionInput!) {
                                    deleteDiscussion(input: $input) {
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
                            //% "Failed to delete discussion"
                            notify.show(qsTrId("id-failed-to-delete-discussion"))
                            return
                        }

                        result = data.createDiscussion
                    })
    }
}
