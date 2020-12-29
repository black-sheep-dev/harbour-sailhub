import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string title
    property string description
    property string identifier
    property int userType: User.Undefined

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
                onClicked: SailHub.api().getUsers(usersModel)
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

        model: UsersModel {
            id: usersModel
            identifier: page.identifier
            modelType: page.userType
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: UserListDelegate {
            id: delegate

            avatar: model.avatarUrl
            login: model.login
            name: model.name

            onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: usersModel.loading
            visible: usersModel.hasNextPage

            MenuItem {
                text: qsTr("Load more")
                onClicked: SailHub.api().getUsers(usersModel)
            }
        }
    }

    Component.onCompleted: {
        SailHub.api().getUsers(usersModel)
    }
}
