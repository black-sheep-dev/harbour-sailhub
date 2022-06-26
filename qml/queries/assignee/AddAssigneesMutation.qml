import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property var assigneeIds

    resultNodePath: "addAssigneesToAssignable"

    query: 'mutation($input: AddAssigneesToAssignableInput!) {
                addAssigneesToAssignable(input: $input) {
                    clientMutationId
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "assignableId": nodeId,
            "assigneeIds": assigneeIds
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}
