import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property bool selected: false

    width: Theme.itemSizeHuge
    height: Theme.itemSizeHuge

    Image {
        id: iconImage
        anchors.fill: parent
        sourceSize.height: parent.height
        sourceSize.width: parent.width

        smooth: true

        Icon {
            visible: selected
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            source: "image://theme/icon-s-installed"
        }
    }

    onClicked: selected = !selected
}
