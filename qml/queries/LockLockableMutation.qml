import QtQuick 2.0

import "../."

BaseQuery {
    property string nodeId
    property string reason

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: LockLockableInput!) {
                                    lockLockable(input: $input) {
                                        lockedRecord {
                                            locked
                                            activeLockReason
                                        }
                                    }
                                }',
                        variables: getQueryVars()
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to lock item"
                            notify.show(qsTrId("id-failed-to-lock-item"))
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
