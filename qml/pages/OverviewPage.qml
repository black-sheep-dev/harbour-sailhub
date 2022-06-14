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
                //% "About"
                text: qsTrId("id-about")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                //% "Settings"
                text: qsTrId("id-settings")
                onClicked: pageStack.push(Qt.resolvedUrl("settings/SettingsPage.qml"))
            }
            MenuItem {
                //% "Search"
                text: qsTrId("id-search")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchSelectionPage.qml"))
            }
//            MenuItem {
//                text: "TEST"
//                onClicked: pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"))
//            }
        }

        ViewPlaceholder {
            enabled: !SailHub.api().ready

            //% "App initializing ..."
            text: qsTrId("id-app-initializing")
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
                //% "Home"
                title: qsTrId("id-home")
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
                //% "Status"
                text: qsTrId("id-status")
            }

            ProfileStatusItem {
                width: parent.width

                profileStatus: SailHub.api().profileStatus

                onClicked: pageStack.push(Qt.resolvedUrl("ProfileStatusPage.qml"), { profileStatus: SailHub.api().profileStatus })
            }

            SectionHeader {
                //% "Activities"
                text: qsTrId("id-activities")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-alarm"
                //% "Notifications"
                title: qsTrId("id-notifications")

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
                //% "My work"
                text: qsTrId("id-my-work")
            }

            IconRelatedItem {
                icon: "qrc:///icons/icon-m-issue"
                //% "Issues"
                title: qsTrId("id-issues")

                onClicked: pageStack.push(Qt.resolvedUrl("IssueSelectionPage.qml"), {
                                              userId: SailHub.api().profile.nodeId,
                                              userLogin: SailHub.api().profile.login
                                          })
            }
            IconRelatedItem {
                icon: "qrc:///icons/icon-m-pull-request"
                //% "Pull requests"
                title: qsTrId("id-pull-requests")

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
                //% "Repositories"
                title: qsTrId("id-repositories")

                onClicked: pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                              login: SailHub.api().profile.login,
                                              identifier: SailHub.api().profile.nodeId,
                                              repoType: Repo.User
                                          })
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-company"
                //% "Organizations"
                title: qsTrId("id-organizations")

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

