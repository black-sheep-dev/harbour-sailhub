import QtQuick 2.0

import "../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UnfollowOrganizationIdInput!) {
                                    unfollowOrganizationId(input: $input) {
                                        user {
                                            viewerIsFollowing
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                organizationId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to unollow organization"
                            notify.show(qsTrId("id-failed-to-unfollow-organization"))
                            return
                        }

                        result = data
                    })
    }
}
