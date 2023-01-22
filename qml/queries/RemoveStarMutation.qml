import QtQuick 2.0

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: RemoveStarInput!) {
                                    removeStar(input: $input) {
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
                            //% "Failed to remove star"
                            notify.show(qsTrId("id-failed-to-remove-star"))
                            return
                        }

                        result = data
                    })
    }
}
