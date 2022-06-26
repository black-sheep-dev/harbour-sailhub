import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

Item {
    id: root

    property string avatarUrl
    property string login
    property string name
    property string nodeId
    property var profileStatus

    property bool loading: false
    property bool ready: false

    function clearStatus() {
        loading = true

        var date = new Date()
        date.setFullYear(2000, 1, 1)

        var input = {}
        input.clientMutationId = nodeId
        input.expiresAt = date.toISOString()

        mutationUpdateStatus.variables = {
            "input": input
        }

        Api.request(mutationUpdateStatus)
    }

    function refresh() {
        loading = true
        Api.request(query)
    }

    function updateStatus() {

        var input = {}
        input.clientMutationId = nodeId
        input.emoji = profileStatus.emoji
        input.limitedAvailability = profileStatus.indicatesLimitedAvailability
        if (profileStatus.expiresAt !== "") {
            input.expiresAt = profileStatus.expiresAt
        }

        input.message = profileStatus.message

        mutationUpdateStatus.variables = {
            "input": input
        }

        Api.request(mutationUpdateStatus)
    }

    QueryObject {
        id: query
        query: '
            query {
                viewer {
                    id
                    avatarUrl
                    login
                    name
                    status {
                        emoji
                        expiresAt
                        indicatesLimitedAvailability
                        message
                    }
                }
            }'

        onReadyChanged: {
            if (!ready) return

            loading = false

            if (error !== QueryObject.ErrorNone) return

            avatarUrl = result.viewer.avatarUrl
            login = result.viewer.login
            name = result.viewer.name
            nodeId = result.viewer.id
            profileStatus = result.viewer.status

            root.ready = true
        }

        onErrorChanged: notification.showErrorMessage(error)
    }

    QueryObject {
        id: mutationUpdateStatus
        query: '
            mutation($input: ChangeUserStatusInput!) {
                changeUserStatus(input: $input) {
                    clientMutationId
                    status {
                        emoji
                        expiresAt
                        indicatesLimitedAvailability
                        message
                    }
                }
            }'

        onResultChanged: profileStatus = result.status
        onErrorChanged: notification.showErrorMessage(error)
    }
}
