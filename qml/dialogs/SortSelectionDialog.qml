import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    property string field
    property var fields: []
    property var fieldLabels: []
    property string direction: "ASC"
    property var directions: ["ASC", "DESC"]

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
                    model: fieldLabels

                    MenuItem { text: modelData }
                }
            }

            Component.onCompleted: currentIndex = field.length > 0 ? fields.indexOf(field) : 0
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

            Component.onCompleted: currentIndex = directions.indexOf(direction)
        }
    }

    onAccepted: {
        field = fields[fieldComboBox.currentIndex]
        direction = directions[orderComboBox.currentIndex]
    }
}
