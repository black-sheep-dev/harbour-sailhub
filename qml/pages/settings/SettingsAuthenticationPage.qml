import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    RemorsePopup { id: remorse }

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                text: qsTr("Reset")
                onClicked: remorse.execute(qsTr("Resetting credentials and close app"), function() {
                    SailHub.reset()
                    Qt.quit()
                })
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("Authentication Settings")
            }

            PasswordField {
                id: tokenField
                width: parent.width

                label: qsTr("Access Token")

                placeholderText: qsTr("Enter access token")
            }
        }
    }

    onStatusChanged: {
        if (status == PageStatus.Deactivating) {
            if (tokenField.text.length > 0) SailHub.accessToken = tokenField.text

            SailHub.saveSettings()
        }
    }
}

