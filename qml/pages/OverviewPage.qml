import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Profile")
                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              nodeId: SailHub.api().loginNodeId(),
                                              own: true
                                          })
            }
            MenuItem {
                text: qsTr("Search")
                //onClicked: SailHub.followRepo(repo.fullName)
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Home")
            }

            SectionHeader {
                text: qsTr("My Work")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-about"
                title: qsTr("Issues")
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-shuffle"
                title: qsTr("Pull Requests")
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-file-archive-folder"
                title: qsTr("Repositories")

                onClicked: pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                              identifier: SailHub.api().loginNodeId(),
                                              repoType: Repo.User
                                          })
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-company"
                title: qsTr("Organizations")
            }
        }
    }
}

