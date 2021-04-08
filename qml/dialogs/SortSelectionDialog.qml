import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    property alias field: fieldComboBox.currentIndex
    property var fields: []
    property alias order: orderComboBox.currentIndex

    Column {
        width: parent.width

        DialogHeader {
            title: qsTr("Select Sorting")
            acceptText: qsTr("Sort")
        }

        ComboBox {
            id: fieldComboBox
            width: parent.width
            label: qsTr("Field")

            menu: ContextMenu {
                Repeater {
                    model: fields
                    MenuItem { text: modelData }
                }
            }
        }

        ComboBox {
            id: orderComboBox
            width: parent.width
            label: qsTr("Order")

            menu: ContextMenu {
                MenuItem { text: qsTr("Ascending") }
                MenuItem { text: qsTr("Descending") }
            }
        }
    }
}
