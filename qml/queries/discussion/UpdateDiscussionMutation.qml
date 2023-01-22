import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body
    property string categoryId
    property string title


    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UpdateDiscussionInput!) {
                                    updateDiscussion(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                discussionId: nodeId,
                                categoryId: categoryId,
                                body: body,
                                title: title
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to update discussion"
                            notify.show(qsTrId("id-failed-to-update-discussion"))
                            return
                        }

                        result = data.updateDiscussion
                    })
    }
}
