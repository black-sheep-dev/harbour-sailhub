import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: SailHub.usersModel().loading
    }

    SilicaListView {
        PullDownMenu {
            MenuItem {
                text: qsTr("Search")
                onClicked: pageStack.push(Qt.resolvedUrl("UsersSearchPage.qml"))
            }
        }

        id: listView
        model: SailHub.usersModel()

        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Users")
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: UserListDelegate {
            id: delegate

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Delete");
                    onClicked: remorse.execute(delegate, qsTr("Delete user"), function() {
                        SailHub.usersModel().removeNode()
                        SailHub.saveSettings()
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

            onClicked: pageStack.push(Qt.resolvedUrl("UserDetailsPage.qml"), { user: SailHub.usersModel().userAt(idx) })
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No users available")
            hintText: qsTr("Pull down to search for users you like to follow")
        }

        VerticalScrollDecorator {}
    }
}
