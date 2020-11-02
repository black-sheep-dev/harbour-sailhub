import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../delegates/"

Page {
    property string title
    property UsersModel userModel

    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        model: userModel

        anchors.fill: parent
        header: PageHeader {
            title: page.title
        }

        Behavior on opacity { FadeAnimator {} }

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
            onUserAvailable: pageStack.push(Qt.resolvedUrl("UserDetailsPage.qml"), {user: userModel.userAt(idx)})
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No users available")
        }

        VerticalScrollDecorator {}
    }
}
