import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId

    query: 'mutation($input: FollowOrganizationInput!) {
                followOrganization(input: $input) {
                    organization {
                        viewerIsFollowing
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "organizationId": nodeId
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
