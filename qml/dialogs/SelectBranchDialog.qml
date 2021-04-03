import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string selected
    property string defaultBranch
    property var branches


    DialogHeader {
        id: header
        title: qsTr("Choose Branch")
        acceptText: qsTr("Select")
    }

    SilicaListView {
        id: listView
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        model: branches

        delegate: ListItem {
            width: parent.width

            contentHeight: Theme.itemSizeMedium

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                anchors.verticalCenter: parent.verticalCenter
                spacing: Theme.paddingMedium

                Label {
                    width: parent.width - parent.spacing - selectedIcon.width
                    anchors.verticalCenter: parent.verticalCenter

                    text: modelData === defaultBranch ? (modelData + " (" + qsTr("default") + ")") : modelData
                }

                Image {
                    id: selectedIcon

                    visible: selected === modelData

                    source: "image://theme/icon-m-acknowledge"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: selected = modelData
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No branches available")
        }

        VerticalScrollDecorator {}
    }
}
