import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    query: 'mutation($input: RemoveStarInput!) {
                removeStar(input: $input) {
                    starrable {
                        stargazerCount
                        viewerHasStarred
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "starrableId": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
