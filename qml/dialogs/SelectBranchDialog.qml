import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string selected
    property string defaultBranch
    property var branches


    DialogHeader {
        id: header
        //% "Choose branch"
        title: qsTrId("id-choose-branch")
        //% "Select"
        acceptText: qsTrId("id-select")
    }

    SilicaListView {
        id: listView
        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: parent.bottom
        }
        model: branches

        delegate: ListItem {
            width: parent.width

            contentHeight: Theme.itemSizeMedium

            Row {
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x 
                spacing: Theme.paddingMedium

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - selectedIcon.width
                    //% "Default"
                    text: modelData.name === defaultBranch ? (modelData.name + " (" + qsTrId("id-default") + ")") : modelData.name
                }

                Image {
                    id: selectedIcon
                    visible: selected === modelData.name
                    source: "image://theme/icon-m-acknowledge"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: selected = modelData.name
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No branches available"
            text: qsTrId("id-no-branches-available")
        }

        VerticalScrollDecorator {}
    }
}
