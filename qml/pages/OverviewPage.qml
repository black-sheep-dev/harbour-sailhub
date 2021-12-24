import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {    
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: !SailHub.api().ready
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("settings/SettingsPage.qml"))
            }
            MenuItem {
                text: qsTr("Search")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchSelectionPage.qml"))
            }
//            MenuItem {
//                text: "TEST"
//                onClicked: pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"))
//            }
        }

        ViewPlaceholder {
            enabled: !SailHub.api().ready

            text: qsTr("App initializing ...")
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: SailHub.api().ready ? 1.0 : 0.0

            Behavior on opacity {
                FadeAnimation {}
            }


            PageHeader {
                title: qsTr("Home")
            }

            AuthorItem {
                id: authorItem

                interactive: true
                title: SailHub.api().profile.login
                subtitle: SailHub.api().profile.name
                avatar: SailHub.api().profile.avatarUrl

                onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), {
                                              user: SailHub.api().profile
                                          })
            }

            SectionHeader {
                text: qsTr("Status")
            }

            ProfileStatusItem {
                width: parent.width

                profileStatus: SailHub.api().profileStatus

                onClicked: pageStack.push(Qt.resolvedUrl("ProfileStatusPage.qml"), { profileStatus: SailHub.api().profileStatus })
            }

            SectionHeader {
                text: qsTr("Activities")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-alarm"
                title: qsTr("Notifications")

                onClicked: pageStack.push(Qt.resolvedUrl("NotificationsListPage.qml"))

                Rectangle {
                    visible: SailHub.newNotificationsAvailable > 0
                    id: notificationBubble
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.horizontalPageMargin + Theme.iconSizeSmall
                    anchors.top: parent.top

                    width: Theme.iconSizeSmall
                    height: Theme.iconSizeSmall

                    color: Theme.highlightColor
                    opacity: 0.8
                    radius: width / 2
                }

                Label {
                    visible: SailHub.newNotificationsAvailable > 0
                    anchors.centerIn: notificationBubble
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.primaryColor

                    text: SailHub.newNotificationsAvailable
                }
            }

            SectionHeader {
                text: qsTr("My Work")
            }

            IconRelatedItem {
                icon: "qrc:///icons/icon-m-issue"
                title: qsTr("Issues")

                onClicked: pageStack.push(Qt.resolvedUrl("IssueSelectionPage.qml"), {
                                              userId: SailHub.api().profile.nodeId,
                                              userLogin: SailHub.api().profile.login
                                          })
            }
            IconRelatedItem {
                icon: "qrc:///icons/icon-m-pull-request"
                title: qsTr("Pull Requests")

                /*onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsSelectionPage.qml"), {
                                              userId: SailHub.api().profile.nodeId,
                                              userLogin: SailHub.api().profile.login
                                         })*/

                onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                                              description: SailHub.api().profile.login,
                                                              identifier: SailHub.api().profile.nodeId,
                                                              type: PullRequest.User,
                                                              states: PullRequestState.Open
                                                         })
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-file-archive-folder"
                title: qsTr("Repositories")

                onClicked: pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                              login: SailHub.api().profile.login,
                                              identifier: SailHub.api().profile.nodeId,
                                              repoType: Repo.User
                                          })
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-company"
                title: qsTr("Organizations")

                onClicked: pageStack.push(Qt.resolvedUrl("OrganizationsListPage.qml"), {
                                              login: SailHub.api().profile.login,
                                              identifier: SailHub.api().profile.nodeId,
                                              organizationType: Organization.IsMember
                                          })
            }
        }
    }

    function startSetupWizard() {
        pageStack.clear()
        pageStack.push(Qt.resolvedUrl("wizard/WizardIntroPage.qml"))
    }

    onStatusChanged: {
        if (status !== PageStatus.Active) return

        if (SailHub.accessToken.length === 0) startSetupWizard()

        SailHub.api().getProfileStatus()
    }
}

