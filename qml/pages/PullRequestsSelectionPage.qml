import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    property string userId
    property string userLogin

    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        model: ListModel {
            ListElement {
                //% "Created"
                title: qsTrId("id-created");
                //% "Pull requests created by user"
                description: qsTrId("id-pull-requests-created-by-user")
                icon: "image://theme/icon-m-edit"
                queryType: "USER_CREATED"
                sorting: true
                editState: true
            }
            ListElement {
                //% "Assigned"
                title: qsTrId("Assigned");
                //% "Pull requests assigned to user"
                description: qsTrId("id-pull-requests-assigned-to-user")
                icon: "image://theme/icon-m-attach"
                queryType: "USER_ASSIGNED"
                sorting: true
                editState: true
            }
            ListElement {
                //% "Mentioned"
                title: qsTrId("id-mentioned");
                //% "Pull requests where user is mentioned"
                description: qsTrId("id-pull-requests-where-user-is-mentioned")
                icon: "image://theme/icon-m-annotation"
                queryType: "USER_MENTIONED"
                sorting: true
                editState: true
            }
        }

        anchors.fill: parent
        header: PageHeader {
            id: pageHeader
            //% "Pull requests"
            title: qsTrId("id-pull-requests")
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

            onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                          nodeId: userId,
                                          description: userLogin,
                                          itemsQueryType: queryType
                                      })
        }

        VerticalScrollDecorator {}
    }
}



