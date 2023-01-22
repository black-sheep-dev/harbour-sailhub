import QtQuick 2.0

import "../."

BaseQuery {
    property string nodeId

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: UnlockLockableInput!) {
                                    unlockLockable(input: $input) {
                                        unlockedRecord {
                                            locked
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                lockableId: nodeId
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to unlock item"
                            notify.show(qsTrId("id-failed-to-unlock-item"))
                            return
                        }

                        result = data
                    })
    }

    function getQueryVars() {
        var input = new Object

        input["input"] = new Object
        input["input"]["clientMutationId"] = viewerProfile.nodeId
        input["input"]["lockableId"] = nodeId
        if (reason.length > 0) input["input"]["LockReason"] = reason

        return input
    }
}
