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
                text: qsTr("Profile")
                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              user: SailHub.api().profile
                                          })
            }
            MenuItem {
                text: qsTr("Search")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchSelectionPage.qml"))
            }
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

            SectionHeader {
                text: qsTr("My Work")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-about"
                title: qsTr("Issues")

                onClicked: pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                              description: SailHub.api().profile.login,
                                              identifier: SailHub.api().profile.nodeId,
                                              type: Issue.User,
                                              states: Issue.StateOpen
                                          })
            }
            IconRelatedItem {
                icon: "qrc:///icons/icon-m-pull-request"
                title: qsTr("Pull Requests")

                onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                              description: SailHub.api().profile.login,
                                              identifier: SailHub.api().profile.nodeId,
                                              type: PullRequest.User,
                                              states: PullRequest.StateOpen
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
    }
}

