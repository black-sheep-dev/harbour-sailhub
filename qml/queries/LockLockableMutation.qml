import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string reason

    query: 'mutation($input: LockLockableInput!) {
                lockLockable(input: $input) {
                    lockedRecord {
                        locked
                        activeLockReason
                    }
                }
            }'

    variables: {
        var input = new Object

        input["input"] = new Object
        input["input"]["clientMutationId"] = viewerProfile.nodeId
        input["input"]["lockableId"] = nodeId
        if (reason.length > 0) input["input"]["LockReason"] = reason

        return input
    }

    onErrorChanged: notification.showErrorMessage(error)
}
