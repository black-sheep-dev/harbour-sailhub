import QtQuick 2.0

import "../."
import "."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: AddStarInput!) {
                                    addStar(input: $input) {
                                        starrable {
                                            stargazerCount
                                            viewerHasStarred
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                starrableId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to add star"
                            notify.show(qsTrId("id-failed-to-add-star"))
                            return
                        }

                        result = data
                    })
    }
}
