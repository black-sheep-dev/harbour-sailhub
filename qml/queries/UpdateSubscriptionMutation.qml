import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string state

    query: 'mutation($input: UpdateSubscriptionInput!) {
                updateSubscription(input: $input) {
                    subscribable {
                        viewerSubscription
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "subscribableId": nodeId,
            "state": state
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
