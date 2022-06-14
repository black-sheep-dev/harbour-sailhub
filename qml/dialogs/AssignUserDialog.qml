import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Dialog {
    id: dialog
    property var selected: []
    property alias repoId: usersModel.identifier

    canAccept: false

    DialogHeader {
        id: header
        //% "Assign user"
        title: qsTrId("id-assign-user")
        //% "Assign"
        acceptText: qsTrId("id-assign")
    }

    SilicaListView {
        id: listView
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        model: UsersModel {
            id: usersModel
            modelType: User.Assignable
        }

        delegate: UserListDelegate {
            Image {
                id: selectedIcon

                visible: false

                source: "image://theme/icon-m-acknowledge"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: {
                var index = selected.indexOf(model.nodeId)
                if (index >= 0) {
                    selected.splice(index, 1)
                    selectedIcon.visible = false
                } else {
                    selected.push(model.nodeId)
                    selectedIcon.visible = true
                }

                dialog.canAccept = selected.length > 0
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No users available"
            text: qsTrId("id-no-users-available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: SailHub.api().getPaginationModel(usersModel)
}
