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
                //% "Created"
                title: qsTrId("id-created");
                //% "Pull requests created by user"
                description: qsTrId("id-pull-requests-created-by-user")
                icon: "image://theme/icon-m-edit"
                pullRequestType: PullRequest.CreatedBy
                sorting: true
                editState: true
            }
            ListElement {
                //% "Assigned"
                title: qsTrId("Assigned");
                //% "Pull requests assigned to user"
                description: qsTrId("id-pull-requests-assigned-to-user")
                icon: "image://theme/icon-m-attach"
                pullRequestType: PullRequest.Assigned
                sorting: true
                editState: true
            }
            ListElement {
                //% "Mentioned"
                title: qsTrId("id-mentioned");
                //% "Pull requests where user is mentioned"
                description: qsTrId("id-pull-requests-where-user-is-mentioned")
                icon: "image://theme/icon-m-annotation"
                pullRequestType: Issue.Mentioned
                sorting: true
                editState: true
            }
        }

        anchors.fill: parent
        header: PageHeader {
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
                                          canCreateNew: false,
                                          description: userLogin,
                                          identifier: userLogin,
                                          type: pullRequestType,
                                          states: PullRequestState.Open,
                                          sorting: sorting,
                                          editState: editState
                                      })
        }

        VerticalScrollDecorator {}
    }
}



