import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                //% "Notification settings"
                title: qsTrId("id-notification-settings")
            }

            TextSwitch {
                id: notifySwitch
                //% "Notifications"
                text: qsTrId("Notifications")
                //% "Get notified of activities on your GitHub account."
                description: qsTrId("id-settings-notifications-desc")

                onCheckedChanged: SailHub.notify = checked

                Component.onCompleted: checked = SailHub.notify
            }

            ComboBox {
                id: updateIntervalComboBox

                enabled: notifySwitch.checked
                //% "Update interval"
                label: qsTrId("id-update-interval")
                menu: ContextMenu {
                    MenuItem {
                        //% "%n min(s)"
                        text: qsTrId("id-mins-count",  5)
                    }
                    MenuItem {
                        //% "%n min(s)"
                        text: qsTrId("id-mins-count", 10)
                    }
                    MenuItem {
                        //% "%n min(s)"
                        text: qsTrId("id-mins-count", 15)
                    }
                    MenuItem {
                        //% "%n min(s)"
                        text: qsTrId("id-mins-count", 30)
                    }
                    MenuItem {
                        //% "%n min(s)"
                        text: qsTrId("id-mins-count", 60)
                    }
                }

                onCurrentIndexChanged: SailHub.notificationUpdateInterval = currentIndex

                Component.onCompleted: currentIndex = SailHub.notificationUpdateInterval
            }
        }
    }

    onStatusChanged: if (status == PageStatus.Deactivating) SailHub.saveSettings()
}


