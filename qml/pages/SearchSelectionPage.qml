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
                title: qsTr("Search Selection")
            }

            IconRelatedItem {
                icon: "image://theme/icon-m-file-archive-folder"
                title: qsTr("Repository")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchRepositoryPage.qml"))
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-media-artists"
                title: qsTr("User")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchUserPage.qml"))
            }
            IconRelatedItem {
                icon: "image://theme/icon-m-company"
                title: qsTr("Organization")
                onClicked: pageStack.push(Qt.resolvedUrl("SearchOrganizationPage.qml"))
            }
        }
    }
}

