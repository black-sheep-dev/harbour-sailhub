import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    query: 'mutation($input: FollowUserInput!) {
                followUser(input: $input) {
                    user {
                        viewerIsFollowing
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "userId": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
