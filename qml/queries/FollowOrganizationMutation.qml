import QtQuick 2.0

import "../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: FollowOrganizationInput!) {
                                    followOrganization(input: $input) {
                                        organization {
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
                            //% "Failed to follow organization"
                            notify.show(qsTrId("id-failed-to-follow-organization"))
                            return
                        }

                        result = data
                    })
    }
}
