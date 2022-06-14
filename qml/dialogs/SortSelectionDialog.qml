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
            //% "Select sorting"
            title: qsTrId("id-select-sorting")
            //% "Sort"
            acceptText: qsTrId("id-sort")
        }

        ComboBox {
            id: fieldComboBox
            width: parent.width
            //% "Field"
            label: qsTrId("id-field")

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
            //% "Order"
            label: qsTrId("id-order")

            menu: ContextMenu {
                //% "Ascending"
                MenuItem { text: qsTrId("id-ascending") }
                //% "Descending"
                MenuItem { text: qsTrId("id-descending") }
            }
        }
    }
}
