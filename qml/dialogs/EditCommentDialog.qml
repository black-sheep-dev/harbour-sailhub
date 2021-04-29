import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property bool edit: false
    property alias body: bodyTextArea.text
    property bool reply: false

    id: dialog
    canAccept: bodyTextArea.text.length > 0

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingSmall

        DialogHeader {
            title: {
                if (reply)
                    return edit ? qsTr("Edit Reply") : qsTr("Add Reply")
                else
                    return edit ? qsTr("Edit Comment") : qsTr("Add Comment")
            }
            acceptText: edit ? qsTr("Save") : qsTr("Add")
        }

        TextArea {
            id: bodyTextArea

            width: parent.width
            height: dialog.height / 2

            focus: true

            cursorPosition: length

            EnterKey.iconSource: "image://theme/icon-m-enter-close"
        }
    }

    onDone: {
        if (result != DialogResult.Accepted) return

        body = bodyTextArea.text
    }
}
