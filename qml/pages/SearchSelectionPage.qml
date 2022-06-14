import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                //% "Search selection"
                title: qsTrId("id-search-selection")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-file-archive-folder"
                //% "Repository"
                title: qsTrId("id-repository")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchRepositoryPage.qml"))
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-media-artists"
                //% "User"
                title: qsTrId("id-user")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchUserPage.qml"))
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-company"
                //% "Organization"
                title: qsTrId("id-organization")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchOrganizationPage.qml"))
            }
        }
    }
}

