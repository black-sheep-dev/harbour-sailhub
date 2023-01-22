import QtQuick 2.0

import "../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: FollowUserInput!) {
                                    followUser(input: $input) {
                                        user {
                                            viewerIsFollowing
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                userId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to follow user"
                            notify.show(qsTrId("id-failed-to-follow-user"))
                            return
                        }

                        result = data
                    })
    }
}
