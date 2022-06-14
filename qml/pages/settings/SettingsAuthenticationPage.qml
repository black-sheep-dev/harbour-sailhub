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
                //% "Reset"
                text: qsTrId("id-reset")
                //% "Resetting credentials and close app"
                onClicked: remorse.execute(qsTrId("id-resseting-credentials"), function() {
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
                //% "Authentication settings"
                title: qsTrId("id-authentication-settings")
            }

            PasswordField {
                id: tokenField
                width: parent.width

                //% "Access token"
                label: qsTrId("id-access-token")

                //% "Enter access token"
                placeholderText: qsTrId("id-enter-access-token")
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

