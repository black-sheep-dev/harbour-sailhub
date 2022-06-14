import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string title
    property string description
    property alias identifier: usersModel.identifier
    property alias userType: usersModel.modelType
    property string repoId
    property int permission: Repo.PermissionNone

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: page.title
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: usersModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
            MenuItem {
                visible: permission === Repo.PermissionAdmin || permission === Repo.PermissionMaintain
                //% "Assign user"
                text: qsTrId("id-assign-user")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/AssignUserDialog.qml"), { repoId: page.repoId })

                    dialog.accepted.connect(function() {
                        if (dialog.selected.lenth === 0) return

                        SailHub.api().assignUsers(usersModel.identifier, dialog.selected)
                    })
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: usersModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No users available"
            text: qsTrId("id-no-users-available")
        }

        VerticalScrollDecorator {}

        model: UsersModel { id: usersModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: UserListDelegate {
            id: delegate

            menu: ContextMenu {
                visible: permission === Repo.PermissionAdmin || permission === Repo.PermissionMaintain
                MenuItem {
                    //% "Remove"
                    text: qsTrId("id-remove")
                    //% "Remove user from assignees"
                    onClicked: delegate.remorseAction(qsTrId("id-remove-user-from-assignees"), function () {
                        SailHub.api().unassignUser(usersModel.identifier, model.nodeId)
                    })
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: usersModel.loading
            visible: usersModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", usersModel.totalCount - listView.count)
                onClicked: getUsers()
            }
        }
    }

    function getUsers() {
        SailHub.api().getPaginationModel(usersModel)
    }

    function refresh() {
        usersModel.reset()
        getUsers()
    }

    Connections {
        target: SailHub.api()
        onUserUnassigned: refresh()
        onUsersAssigned: refresh()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete usersModel
}
