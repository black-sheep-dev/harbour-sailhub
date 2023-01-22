import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string reason
    Column {
        width: parent.width
        spacing: Theme.paddingLarge

        DialogHeader {
            //% "Choose lock reason"
            title: qsTrId("id-choose-lock-reason")
            //% "Select"
            acceptText: qsTrId("id-select")
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            wrapMode: Text.Wrap
            color: Theme.highlightColor

            //% "Choose a reason why you are locking this one."
            text: qsTrId("id-choose-lock-reason-desc")
        }

        ComboBox {
            id: comboBox
            width: parent.width
            //% "Reason"
            label: qsTrId("id-reason")

            menu: ContextMenu {
                MenuItem {
                    //% "None"
                    text: qsTrId("id-none")
                }
                MenuItem {
                    //% "Off topic"
                    text: qsTrId("id-off-topic")
                }
                MenuItem {
                    //% "Resolved"
                    text: qsTrId("id-resolved")
                }
                MenuItem {
                    //% "Spam"
                    text: qsTrId("id-spam")
                }
                MenuItem {
                    //% "Too heated"
                    text: qsTrId("id-too-heated")
                }
            }
        }
    }

    onAccepted: {
        switch (comboBox.currentIndex) {
        case 1:
            reason = "OFF_TOPIC"
            return

        case 2:
            reason = "RESOLVED"
            return

        case 3:
            reason = "SPAM"
            return

        case 4:
            reason = "TOO_HEATED"
            return

        default:
            break
        }
    }
}
