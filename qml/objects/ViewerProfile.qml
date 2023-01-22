import QtQuick 2.0

import "../."

Item {
    id: root

    property string avatarUrl
    property string login
    property string name
    property string nodeId
    property var profileStatus

    property bool loading: false
    property bool ready: false

    readonly property string mutationQuery: 'mutation($input: ChangeUserStatusInput!) {
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

    function refresh() {
        loading = true
        Api.request({
                        query: 'query {
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
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to fetch profile data"
                            notify.show(qsTrId("id-failed-to-fetch-profile-data"))
                            return
                        }

                        avatarUrl = result.viewer.avatarUrl
                        login = result.viewer.login
                        name = result.viewer.name
                        nodeId = result.viewer.id
                        profileStatus = result.viewer.status

                        ready = true
                    })
    }

    function clearStatus() {
        loading = true

        var date = new Date()
        date.setFullYear(2000, 1, 1)

        var input = {}
        input.clientMutationId = nodeId
        input.expiresAt = date.toISOString()

        Api.request({
                        query: mutationQuery,
                        variables: { input: input }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to clear profile status"
                            notify.show(qsTrId("id-failed-to-clear-profile-status"))
                            return
                        }

                        profileStatus = result.status
                    })
    }

    function updateStatus() {
        loading = true
        var input = {}
        input.clientMutationId = nodeId
        input.emoji = profileStatus.emoji
        input.limitedAvailability = profileStatus.indicatesLimitedAvailability
        if (profileStatus.expiresAt !== "") {
            input.expiresAt = profileStatus.expiresAt
        }

        input.message = profileStatus.message

        Api.request({
                        query: mutationQuery,
                        variables: { input: input }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to update profile status"
                            notify.show(qsTrId("id-failed-to-update-profile-status"))
                            return
                        }

                        profileStatus = result.status
                    })
    }
}
