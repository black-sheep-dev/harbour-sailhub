import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property alias title: titleField.text
    property alias body: bodyTextArea.text

    id: dialog
    canAccept: titleField.text.length > 0

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingSmall

        DialogHeader {
            title: qsTr("Choose")
            acceptText: edit ? qsTr("Save") : qsTr("Create")
        }

        TextField {
            id: titleField
            width: parent.width

            label: qsTr("Title")
            focus: true

            placeholderText: qsTr("Enter title")

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: edit ? "image://theme/icon-m-enter-close" : "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                if (edit) {
                    focus = false
                } else {
                    bodyTextArea.focus = true
                }
            }
        }

        TextArea {
            id: bodyTextArea

            width: parent.width
            height: dialog.height / 2

            EnterKey.iconSource: "image://theme/icon-m-enter-close"
            EnterKey.onClicked: focus = false
        }
    }

    onDone: {
        if (result != DialogResult.Accepted) return

        title = titleField.text
        body = bodyTextArea.text
    }
}

