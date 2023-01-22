import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property var assigneeIds

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: RemoveAssigneesFromAssignableInput!) {
                                    removeAssigneesFromAssignable(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                assignableId: nodeId,
                                assigneeIds: assigneeIds
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to remove assignees"
                            notify.show(qsTrId("id-failed-to-remove-assignees"))
                            return
                        }

                        result = data.removeAssigneesFromAssignable
                    })
    }
}
