import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property bool edit: false
    property alias title: titleField.text
    property alias body: bodyTextArea.text

    id: dialog
    canAccept: titleField.text.length > 0

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingSmall

        DialogHeader {
            title: edit ?
                       //% "Edit discussion"
                       qsTrId("id-edit-discussion") :
                       //% "Create discussion"
                       qsTrId("id-create-discussion")
            acceptText: edit ?
                            //% "Save"
                            qsTrId("id-save") :
                            //% "Create"
                            qsTrId("id-create")
        }

        TextField {
            id: titleField
            width: parent.width

            //% "Title"
            label: qsTrId("id-title")
            focus: true

            //% "Enter title"
            placeholderText: qsTrId("id-enter-title")

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: edit ? "image://theme/icon-m-enter-close" : "image://theme/icon-m-enter-next"
            EnterKey.onClicked: {
                if (edit) {
                    focus = false
                } else {

                }
            }
        }

        TextArea {
            id: bodyTextArea

            width: parent.width
            height: dialog.height / 2

            cursorPosition: length

            //EnterKey.iconSource: "image://theme/icon-m-enter-close"
        }
    }

    onDone: {
        if (result != DialogResult.Accepted) return

        title = titleField.text
        body = bodyTextArea.text
    }
}
