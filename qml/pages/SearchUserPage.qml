import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Search User")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.enabled: text.length > 2
                EnterKey.iconSource: "image://theme/icon-m-search"
                EnterKey.onClicked: {
                    focus = false
                    SailHub.api().searchUser(searchField.text, usersModel)
                }

                onTextChanged: {
                    if (text.length === 0) {
                        focus = true
                        usersModel.reset()
                    }
                }
            }
        }

        SilicaListView {
            id: listView

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom

            clip: true

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No users found")
                hintText: qsTr("Type in search pattern to find users")

            }

            model: UsersModel {
                id: usersModel
                modelType: User.Search
            }

            delegate: UserListDelegate {
                id: delegate

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              nodeId: model.nodeId
                                          })
            }

            PushUpMenu {
                busy: usersModel.loading
                visible: usersModel.hasNextPage

                MenuItem {
                    text: qsTr("Load more (%n to go)", "", usersModel.totalCount - listView.count)
                    onClicked: SailHub.api().searchUser(searchField.text, usersModel)
                }
            }
            VerticalScrollDecorator {}
        }
    }
}


