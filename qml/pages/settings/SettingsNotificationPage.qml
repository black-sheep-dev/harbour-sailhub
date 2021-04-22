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
                title: qsTr("Notification Settings")
            }

            TextSwitch {
                id: notifySwitch
                text: qsTr("Notifications")
                description: qsTr("Get notified of activities on your GitHub account.")

                onCheckedChanged: SailHub.notify = checked

                Component.onCompleted: checked = SailHub.notify
            }

            ComboBox {
                id: updateIntervalComboBox

                enabled: notifySwitch.checked
                label: qsTr("Update Interval")
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("%n min(s)", "", 5)
                    }
                    MenuItem {
                        text: qsTr("%n min(s)", "", 10)
                    }
                    MenuItem {
                        text: qsTr("%n min(s)", "", 15)
                    }
                    MenuItem {
                        text: qsTr("%n min(s)", "", 30)
                    }
                    MenuItem {
                        text: qsTr("%n min(s)", "", 60)
                    }
                }

                onCurrentIndexChanged: SailHub.notificationUpdateInterval = currentIndex

                Component.onCompleted: currentIndex = SailHub.notificationUpdateInterval
            }
        }
    }

    onStatusChanged: if (status == PageStatus.Deactivating) SailHub.saveSettings()
}


