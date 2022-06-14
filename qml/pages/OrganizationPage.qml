import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    property bool busy: false
    property bool loading: false
    property string nodeId
    property Organization organization

    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: page.loading
    }

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy

            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getOrganization(page.nodeId)
                }
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

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
                visible: organization.twitterUsername.length > 0

                icon: "image://theme/icon-m-message"
                label: organization.twitterUsername
            }

            IconLabel {
                visible: organization.location.length > 0

                icon: "image://theme/icon-m-location"
                label: organization.location
            }

            IconLabel {
                visible: organization.websiteUrl.length > 0

                icon: "image://theme/icon-m-website"
                label: organization.websiteUrl
            }

            IconLabel {
                visible: organization.email.length > 0

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
                value: organization.repositories

                onClicked: {
                    if (organization.repositories === 0) return;

                    console.log(organization.nodeId)

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                  login: organization.login,
                                                                  identifier: organization.nodeId,
                                                                  repoType: Repo.Organization
                                                              })
                }
            }
            RelatedValueItem {
                //% "Projects"
                label: qsTrId("id-projects")
                value: organization.projects

            }
            RelatedValueItem {
                //% "Teams"
                label: qsTrId("id-teams")
                value: organization.teams
            }
            RelatedValueItem {
                //% "Members"
                label: qsTrId("id-members")
                value: organization.members

                onClicked: {
                    if (organization.members=== 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              identifier: organization.nodeId,
                                              userType: User.OrganizationMember
                                          })
                }
            }
        }
    }

    Connections {
        target: SailHub.api()
        onOrganizationAvailable: {
            if (page.nodeId !== organization.nodeId) return

            page.organization = organization
            page.loading = false
        }
    }

    Component.onCompleted: {
        if (page.nodeId.length > 0) {
            page.loading = true
            SailHub.api().getOrganization(page.nodeId)
        } else {
            page.nodeId = organization.nodeId
        }
    }
}


