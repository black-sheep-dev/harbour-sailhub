import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    property string userId
    property string userLogin

    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        model: ListModel {
            ListElement {
                title: qsTr("Created");
                description: qsTr("Issues created by user")
                icon: "image://theme/icon-m-edit"
                issueType: Issue.CreatedBy
            }
            ListElement {
                title: qsTr("Assigned");
                description: qsTr("Issues assigned to user")
                icon: "image://theme/icon-m-attach"
                issueType: Issue.Assigned
            }
            ListElement {
                title: qsTr("Mentioned");
                description: qsTr("Issues where user is mentioned")
                icon: "image://theme/icon-m-annotation"
                issueType: Issue.Mentioned
            }
        }

        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Issues")
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

            onClicked: pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                          canCreateNew: false,
                                          description: userLogin,
                                          identifier: userLogin,
                                          type: issueType,
                                          states: Issue.StateOpen
                                      })
        }

        VerticalScrollDecorator {}
    }
}



