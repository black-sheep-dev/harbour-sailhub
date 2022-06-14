import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        model: ListModel {
            ListElement {
                //% "Authentication"
                title: qsTrId("id-authentication");
                //% "Manage authentication data"
                description: qsTrId("id-manage-authentication-data")
                icon: "image://theme/icon-m-keys"
                page: "SettingsAuthenticationPage.qml"
            }
            ListElement {
                //% "Notification"
                title: qsTrId("id-notification");
                //% "Manage notification options"
                description: qsTrId("id-manage-notification-options")
                icon: "image://theme/icon-m-alarm"
                page: "SettingsNotificationPage.qml"
            }
            ListElement {
                //% "Pagination"
                title: qsTrId("id-pagination");
                description: qsTrId("id-manage-pagination-options")
                icon: "image://theme/icon-m-levels"
                page: "SettingsPaginationPage.qml"
            }
        }

        anchors.fill: parent
        header: PageHeader {
            //% "Settings"
            title: qsTrId("id-settings")
        }

        delegate: ListItem {
            id: delegate
            width: parent.width
            contentHeight: Theme.itemSizeMedium

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * x
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                spacing: Theme.paddingMedium

                Image {
                    id: itemIcon
                    source: icon
                    anchors.verticalCenter: parent.verticalCenter
                }

                Column {
                    id: data
                    width: parent.width - itemIcon.width
                    anchors.verticalCenter: itemIcon.verticalCenter
                    Label {
                        id: text
                        width: parent.width
                        text: title
                        color: pressed ? Theme.secondaryHighlightColor:Theme.highlightColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                    Label {
                        text: description
                        color: Theme.secondaryColor
                        font.pixelSize: Theme.fontSizeSmall
                    }
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl(page))
        }

        VerticalScrollDecorator {}
    }
}


