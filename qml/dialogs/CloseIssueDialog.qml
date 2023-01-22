import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string reason

    id: dialog

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingLarge

        DialogHeader {
            //% "Close issue"
            title: qsTrId("id-close-issue")
            //% "Close"
            acceptText: qsTrId("id-close")
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            color: Theme.highlightColor
            wrapMode: Text.Wrap

            //% "Choose a reason why you close this issue."
            text: qsTrId("id-close-issue-reason-desc")
        }

        ComboBox {
            id: comboBoxReason
            //% "Reason"
            label: qsTrId("id-reason")
            menu: ContextMenu {
                MenuItem {
                    //% "Completed"
                    text: qsTrId("id-completed")
                }
                MenuItem {
                    //% "Not planned"
                    text: qsTrId("id-not-planned")
                }
            }
            currentIndex: 0
        }
    }

    onAccepted: reason = comboBoxReason.currentIndex === 0 ? "COMPLETED" : "NOT_PLANNED"
}
