import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: SailHub.usersSearchModel().loading
    }

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Search Users")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.onClicked: {
                    focus = false
                    SailHub.searchUsers(text)
                }

                onTextChanged: if (text.length == 0) SailHub.usersSearchModel().reset()
            }
        }

        SilicaListView {
            id: listView

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            clip: true

            opacity: busyIndicator.running ? 0.3 : 1.0
            Behavior on opacity { FadeAnimator {} }

            model: SailHub.usersSearchModel()

            delegate: UserListDelegate {
                id: delegate

                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Follow");
                        onClicked: remorse.execute(delegate, qsTr("Following user"), function() {
                            SailHub.followUser(login)
                        })
                    }
                }

                RemorseItem { id: remorse }

                avatar: avatarUrl
                title: name
                subtitle: {
                    switch (userType) {
                    case User.TypeUser:
                        return qsTr("User")

                    case User.TypeOrganization:
                        return qsTr("Organization")

                    default:
                        return qsTr("Undefined user type")
                    }
                }

                onClicked: SailHub.getUser(login)
            }

            Connections {
                target: SailHub
                onUserAvailable: pageStack.push(Qt.resolvedUrl("UserDetailsPage.qml"), {user: user})
            }

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No users found")
            }

            VerticalScrollDecorator {}
        }
    }

    Component.onCompleted: SailHub.userSearchModel().reset()
}

