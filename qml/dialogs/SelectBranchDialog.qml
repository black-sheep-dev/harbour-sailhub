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
