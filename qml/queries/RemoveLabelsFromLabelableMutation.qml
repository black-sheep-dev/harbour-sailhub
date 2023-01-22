import QtQuick 2.0

import "../."
import "."

BaseQuery {
    property string nodeId
    property var labelIds: []

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: RemoveLabelsFromLabelableInput!) {
                                    removeLabelsFromLabelable(input: $input) {
                                        labelable {
                                            __typename
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                labelableId: nodeId,
                                labelIds: labelIds
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to remove labels"
                            notify.show(qsTrId("id-failed-to-remove-labels"))
                            return
                        }

                        result = data
                    })
    }
}
