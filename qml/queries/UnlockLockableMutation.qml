import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    query: 'mutation($input: UnlockLockableInput!) {
                unlockLockable(input: $input) {
                    unlockedRecord {
                        locked
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "lockableId": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
