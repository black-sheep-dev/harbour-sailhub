import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        running: searchModel.loading
        size: Theme.itemSizeLarge
    }

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
                    searchModel.reset()
                    searchModel.searchPattern = searchField.text
                    SailHub.api().getPaginationModel(searchModel)
                }

                onTextChanged: {
                    if (text.length === 0) {
                        focus = true
                        searchModel.reset()
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

            //opacity: searchModel.loading ? 0 : 1
            //Behavior on opacity { FadeAnimation {} }

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No users found")
                hintText: qsTr("Type in search pattern to find users")

            }

            model: UsersModel {
                id: searchModel
                modelType: User.Search
            }

            delegate: UserListDelegate {
                id: delegate

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              nodeId: model.nodeId
                                          })
            }

            PushUpMenu {
                busy: searchModel.loading
                visible: searchModel.hasNextPage

                MenuItem {
                    text: qsTr("Load more (%n to go)", "", searchModel.totalCount - listView.count)
                    onClicked: SailHub.api().getPaginationModel(searchModel)
                }
            }
            VerticalScrollDecorator {}
        }
    }
}


