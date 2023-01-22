import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog
    allowedOrientations: Orientation.Portrait
    acceptDestination: Qt.resolvedUrl("../OverviewPage.qml")
    acceptDestinationAction: PageStackAction.Replace
    acceptDestinationReplaceTarget: null

    canAccept: tokenField.acceptableInput

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
        spacing: Theme.paddingLarge
        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Personal access token"
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

            validator: RegExpValidator {
                regExp: /^(ghp_).*[a-zA-Z0-9]$/
            }

            focus: true
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            visible: !tokenField.acceptableInput && tokenField.length > 4
            //% "This token does not appear to be a GitHub token!"
            text: qsTrId("id-no-github-token")
            color: Theme.errorColor
            font.pixelSize: Theme.fontSizeExtraSmall
        }
    }

    onAccepted: settings.accessToken = tokenField.text
}

