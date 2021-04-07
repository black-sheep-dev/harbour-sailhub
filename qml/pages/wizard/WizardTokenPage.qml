import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    id: dialog
    allowedOrientations: Orientation.Portrait
    acceptDestination: Qt.resolvedUrl("WizardFinalPage.qml")

    DialogHeader {
        id: header
        acceptText: qsTr("Continue")
        cancelText: qsTr("Back")
    }

    Column {
        anchors.top: header.bottom
        width: parent.width
        spacing: Theme.paddingMedium

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Personal Access Token")

            color: Theme.secondaryHighlightColor
            font.pixelSize: Theme.fontSizeLarge
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            wrapMode: Text.WordWrap
            font.pixelSize: Theme.fontSizeSmall

            text: qsTr("You need to provide a personal access token to connect to GitHub.")
                  + "\n"
                  + qsTr("This token can be created in developer settings on GitHub.")
                  + " "
                  + qsTr("For a detailed description please refer the README in project repository!")

            color: Theme.highlightColor
        }

        Item {
            width: 1
            height: Theme.paddingLarge
        }

        PasswordField {
            id: tokenField
            width: parent.width

            label: qsTr("Access Token")
            placeholderText: qsTr("Enter access token")

            onTextChanged: checkInput()
        }
    }

    function checkInput() { canAccept = tokenField.text.length > 0 }

    onAccepted: {
        SailHub.accessToken = tokenField.text
        SailHub.initialize()
    }

    Component.onCompleted: checkInput()
}

