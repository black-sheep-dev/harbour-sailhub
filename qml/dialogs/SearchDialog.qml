import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property alias searchPattern: searchPatternField.text
    property int searchType: 2

    id: dialog
    canAccept: searchPattern.length > 0

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingLarge

        DialogHeader {
            //% "Search filter"
            title: qsTrId("id-search-filter")
            //% "Search"
            acceptText: qsTrId("id-search")
        }

        TextField {
            id: searchPatternField
            width: parent.width
            focus: true
            //% "Search pattern"
            label: qsTrId("id-search-pattern")
            //% "Enter search pattern"
            placeholderText: qsTrId("id-enter-search-pattern")
        }

        SectionHeader {
            //% "Filters"
            text: qsTrId("id-filters")
        }

        ComboBox {
            id: comboBoxType
            //% "Object type"
            label: qsTrId("id-object-type")
            menu: ContextMenu {
                MenuItem {
                    //% "Discussion"
                    text: qsTrId("id-discussion")
                }
                MenuItem {
                    //% "Issue"
                    text: qsTrId("id-issue")
                }
                MenuItem {
                    //% "Repository"
                    text: qsTrId("id-repository")
                }
                MenuItem {
                    //% "User"
                    text: qsTrId("id-repository")
                }
            }

            Component.onCompleted: currentIndex = searchType
        }
    }
}
