import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body
    property string categoryId
    property string repoId
    property string title


    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: CreateDiscussionInput!) {
                                    createDiscussion(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                categoryId: categoryId,
                                repositoryId: repoId,
                                body: body,
                                title: title
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to create discussion"
                            notify.show(qsTrId("id-failed-to-create-discussion"))
                            return
                        }

                        result = data.createDiscussion
                    })
    }
}
