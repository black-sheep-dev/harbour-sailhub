import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../queries/"

Page {
    property string nodeId
    property alias organization: query.result

    id: page
    allowedOrientations: Orientation.All

    function refresh() { Api.request(query) }

    QueryObject {
        id: query
        resultNodePath: "node"
        query: '
            query($nodeId: ID!) {
                node(id: $nodeId) {
                    ... on Organization {
                        id
                        avatarUrl
                        description
                        email
                        location
                        login
                        membersWithRole {
                            totalCount
                        }
                        name
                        projects {
                            totalCount
                        }
                        repositories {
                            totalCount
                        }
                        teams {
                            totalCount
                        }
                        twitterUsername
                        viewerIsFollowing
                        websiteUrl
                    }
                }
            }'
        variables: {
            "nodeId": page.nodeId
        }

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            followMenu.viewerIsFollowing = result.node.viewerIsFollowing
        }

        onErrorChanged: notification.showErrorMessage(error)
    }

    FollowOrganizationMutation {
        id: followOrganizationMutation
        nodeId: page.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return

            followMenu.viewerIsFollowing = result.followOrganization.organization.viewerIsFollowing
        }
    }

    FollowOrganizationMutation {
        id: unfollowOrganizationMutation
        nodeId: page.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return

            followMenu.viewerIsFollowing = result.unfollowOrganization.organization.viewerIsFollowing
        }
    }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: !query.ready

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            //% "Loading data..."
            text: qsTrId("id-loading-data")
        }
    }

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy

            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    SailHub.api().request(query)
                }
            }

            MenuItem {
                property bool viewerIsFollowing: false

                id: followMenu
                text: viewerIsFollowing ?
                          //% "Unfollow"
                          qsTrId("id-unfollow") :
                          //% "Follow"
                          qsTrId("id-follow")

                onClicked: Api.request(viewerIsFollowing ? unfollowOrganizationMutation : followOrganizationMutation)
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            PageHeader {
                //% "Organization"
                title: qsTrId("id-organization")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Image {
                    id: avatarIcon
                    height: Theme.itemSizeMedium
                    width: height

                    source: organization.avatarUrl

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Column {
                    width: parent.width - avatarIcon.width - Theme.paddingMedium
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    Label {
                        visible: organization.name.length > 0

                        font.pixelSize: Theme.fontSizeLarge
                        color: Theme.highlightColor

                        text: organization.name
                    }

                    Label {
                        font.pixelSize: Theme.fontSizeMedium
                        color: Theme.highlightColor

                        text: organization.login
                    }
                }
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // description
            Label {
                visible: user.bio.length > 0

                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.WordWrap

                color: Theme.highlightColor

                text: organization.description
            }

            // Info
            IconLabel {
                visible: organization.twitterUsername !== null

                icon: "image://theme/icon-m-message"
                label: organization.twitterUsername
            }

            IconLabel {
                visible: organization.location !== null

                icon: "image://theme/icon-m-location"
                label: organization.location
            }

            IconLabel {
                visible: organization.websiteUrl !== null

                icon: "image://theme/icon-m-website"
                label: organization.websiteUrl
            }

            IconLabel {
                visible: organization.email !== null

                icon: "image://theme/icon-m-mail"
                label: organization.email
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // related items
            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            RelatedValueItem {
                //% "Repositories"
                label: qsTrId("id-repositories")
                value: organization.repositories.totalCount

                onClicked: {
                    if (organization.repositories.totalCount === 0) return;

                    console.log(organization.id)

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                  nodeId: nodeId,
                                                  itemsQueryType: "ORGANIZATION_REPOS",
                                                  //% "Repositories"
                                                  title: qsTrId("id-repositories"),
                                                  description: organization.name
                                              })
                }
            }
            RelatedValueItem {
                //% "Projects"
                label: qsTrId("id-projects")
                value: organization.projects.totalCount

            }
            RelatedValueItem {
                //% "Teams"
                label: qsTrId("id-teams")
                value: organization.teams.totalCount
            }
            RelatedValueItem {
                //% "Members"
                label: qsTrId("id-members")
                value: organization.membersWithRole.totalCount

                onClicked: {
                    if (organization.membersWithRole.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "ORGANIZATION_MEMBERS",
                                               //% "Members"
                                               title: qsTrId("id-members"),
                                               description: organization.name
                                          })
                }
            }
        }
    }

    Component.onCompleted: refresh()
}


