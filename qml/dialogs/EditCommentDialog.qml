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
                    return edit ?
                                //% "Edit reply"
                                qsTrId("id-edit-reply") :
                                //% "Add reply"
                                qsTrId("id-add-reply")
                else
                    return edit ?
                                //% "Edit comment"
                                qsTrId("id-edit-comment") :
                                //% "Add comment"
                                qsTrId("id-add-comment")
            }
            acceptText: edit ?
                            //% "Save"
                            qsTrId("id-save") :
                            //% "Add"
                            qsTrId("id-add")
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
