import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    id: dialog

    allowedOrientations: Orientation.Portrait

    acceptDestination: Qt.resolvedUrl(Qt.resolvedUrl("WizardTokenPage.qml"))

    onRejected: Qt.quit()

    DialogHeader {
        id: header
        //% "Continue"
        acceptText: qsTrId("id-continue")
        //% "Quit"
        cancelText: qsTrId("id-quit")
    }

    RemorsePopup { id: resetPopup }

    Column {
        anchors.top: header.bottom
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        Image {
            id: logo
            source: "/usr/share/icons/hicolor/512x512/apps/harbour-sailhub.png"
            smooth: true
            height: parent.width / 2
            width: parent.width / 2
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        Label {
            width: parent.width

            //% "Welcome to SailHub"
            text: qsTrId("id-wizard-welcome-title")

            color: Theme.secondaryHighlightColor
            font.bold: true
            font.pixelSize: Theme.fontSizeLarge
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        Label {
            width: parent.width

            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall

            wrapMode: Text.Wrap

            //% "This app is not configured yet."
            text: qsTrId("id-wizard-info-unconfigured")
        }

        Label {
            width: parent.width

            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall

            wrapMode: Text.Wrap

            //% "The setup wizard will guide you through the configuration process."
            text: qsTrId("id-wizard-info-guide")
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        Separator {
            width: parent.width
            color: Theme.highlightBackgroundColor
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        Label {
            width: parent.width

            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall

            wrapMode: Text.Wrap

            //% "If there are errors during the setup process, you can try to reset the data from a previous installation."
            text: qsTrId("id-wizard-errors-info")
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        ButtonLayout {
            Button {
                //% "Reset"
                text: qsTrId("id-reset")
                //% "Resetting application"
                onClicked: resetPopup.execute(qsTrId("id-resetting-application"), function() {
                    SailHub.reset()
                })
            }
        }
    }
}
