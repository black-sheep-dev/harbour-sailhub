import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    id: dialog
    allowedOrientations: Orientation.Portrait
    acceptDestination: Qt.resolvedUrl("WizardFinalPage.qml")

    DialogHeader {
        id: header
        //% "Continue"
        acceptText: qsTrId("id-continue")
        //% "Back"
        cancelText: qsTrId("id-back")
    }

    Column {
        anchors.top: header.bottom
        width: parent.width
        spacing: Theme.paddingMedium

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Personal Access Token"
            text: qsTrId("id-personal-access-token")

            color: Theme.secondaryHighlightColor
            font.pixelSize: Theme.fontSizeLarge
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            wrapMode: Text.WordWrap
            font.pixelSize: Theme.fontSizeSmall

            //% "You need to provide a personal access token to connect to GitHub."
            text: qsTrId("")
                  + "\n"
                    //% "This token can be created in developer settings on GitHub."
                  + qsTrId("id-wizard-token-desc-b")
                  + " "
                    //% "For a detailed description please refer the README in project repository!"
                  + qsTrId("id-wizard-token-desc-c")

            color: Theme.highlightColor
        }

        Item {
            width: 1
            height: Theme.paddingLarge
        }

        PasswordField {
            id: tokenField
            width: parent.width

            //% "Access token"
            label: qsTrId("id-access-token")
            //% "Enter access token"
            placeholderText: qsTrId("id-enter-access-token")

            onTextChanged: checkInput()

            focus: true
        }
    }

    function checkInput() { canAccept = tokenField.text.length > 0 }

    onAccepted: {
        SailHub.accessToken = tokenField.text
        SailHub.saveSettings()
        SailHub.initialize()
    }

    Component.onCompleted: checkInput()
}

