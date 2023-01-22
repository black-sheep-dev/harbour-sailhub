import QtQuick 2.0

import "../."
import "."

BaseQuery {
    property string nodeId
    property var labelIds: []

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: AddLabelsToLabelableInput!) {
                                    addLabelsToLabelable(input: $input) {
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
                            //% "Failed to add labels"
                            notify.show(qsTrId("id-failed-to-add-labels"))
                            return
                        }

                        result = data
                    })
    }
}
