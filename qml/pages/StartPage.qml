import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        id: listView
        model: ListModel {
            ListElement {
                title: qsTr("Users");
                description: qsTr("Show, search and follow GitHub users")
                icon: "image://theme/icon-m-users"
                page: "user/UsersListPage.qml"
            }
            ListElement {
                title: qsTr("Repositories");
                description: qsTr("Show, search and watch GitHub repositories")
                icon: "image://theme/icon-m-share"
                page: "repo/ReposListPage.qml"
            }
        }

        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Settings")
        }

        delegate: ListItem {
            id: delegate
            width: parent.width
            contentHeight: Theme.itemSizeLarge

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * x
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: itemIcon
                    source: icon
                    anchors.verticalCenter: parent.verticalCenter
                }

                Item {
                    width:Theme.paddingMedium
                    height:1
                }

                Column {
                    id: data
                    width: parent.width - itemIcon.width
                    anchors.verticalCenter: itemIcon.verticalCenter
                    Label {
                        id: text
                        width: parent.width
                        text: title
                        color: pressed?Theme.secondaryHighlightColor:Theme.highlightColor
                        font.pixelSize: Theme.fontSizeLarge
                    }
                    Label {
                        text: description
                        color: Theme.secondaryColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl(page))
        }

        VerticalScrollDecorator {}
    }
}
