import QtQuick 2.0

import "../."
import "."

BaseQuery {
    property string nodeId
    property string state

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UpdateSubscriptionInput!) {
                                    updateSubscription(input: $input) {
                                        subscribable {
                                            viewerSubscription
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                subscribableId: nodeId,
                                state: state
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to update subscription"
                            notify.show(qsTrId("id-failed-to-update-subscription"))
                            return
                        }

                        result = data
                    })
    }
}
