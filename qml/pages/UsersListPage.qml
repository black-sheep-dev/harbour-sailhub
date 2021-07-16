import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string title
    property string description
    property alias identifier: usersModel.identifier
    property alias userType: usersModel.modelType

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
                text: qsTr("Refresh")
                onClicked: refresh()
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
            text: qsTr("No users available")
        }

        VerticalScrollDecorator {}

        model: UsersModel { id: usersModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

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

    Component.onCompleted: refresh()
    Component.onDestruction: delete usersModel
}
