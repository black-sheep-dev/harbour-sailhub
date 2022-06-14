import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Notifications"
            title: qsTrId("id-notifications")
            description: SailHub.api().profile().login
        }

        PullDownMenu {
            busy: notificationsModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: notificationsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No notifications available"
            text: qsTrId("id-no-notifications-available")
        }

        VerticalScrollDecorator {}

        model: NotificationsModel { id: notificationsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: NotificationListDelegate {
            id: delegate

//            menu: ContextMenu {
//                MenuItem {
//                    text: qsTr("Mark as done")
//                }

//                MenuItem {
//                    text: qsTr("Mark as readed")
//                }

//            }
        }
    }

    function getNotifications() {
        SailHub.api().getNotifications(notificationsModel)
    }

    function refresh() {
        getNotifications()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete notificationsModel
}
