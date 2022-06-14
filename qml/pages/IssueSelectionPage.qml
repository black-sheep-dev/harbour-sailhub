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
                //% "Open"
                title: qsTrId("id-open");
                //% "Open issues in user repos"
                description: qsTrId("id-open-issues-in-user-repos")
                icon: "image://theme/icon-m-warning"
                issueType: Issue.Repos
                sorting: false
                editState: false
            }
            ListElement {
                //% "Created"
                title: qsTrId("id-created");
                //% "Issues created by user"
                description: qsTrId("id-issues-created-by-user")
                icon: "image://theme/icon-m-edit"
                issueType: Issue.CreatedBy
                sorting: true
                editState: true
            }
            ListElement {
                //% "Assigned"
                title: qsTrId("id-assigned");
                //% "Issues assigned to user"
                description: qsTrId("id-issues-assigned-to-user")
                icon: "image://theme/icon-m-attach"
                issueType: Issue.Assigned
                sorting: true
                editState: true
            }
            ListElement {
                //% "Mentioned"
                title: qsTrId("id-mentioned");
                //% "Issues where user is mentioned"
                description: qsTrId("id-issues-where-user-is-mentioned")
                icon: "image://theme/icon-m-annotation"
                issueType: Issue.Mentioned
                sorting: true
                editState: true
            }
        }

        anchors.fill: parent
        header: PageHeader {
            //% "Issues"
            title: qsTrId("id-issues")
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
                                          states: IssueState.Open,
                                          sorting: sorting,
                                          editState: editState
                                      })
        }

        VerticalScrollDecorator {}
    }
}



