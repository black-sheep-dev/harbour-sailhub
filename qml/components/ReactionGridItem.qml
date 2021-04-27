import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property bool selected: false

    width: Theme.itemSizeHuge
    height: Theme.itemSizeHuge

    Image {
        id: iconImage
        anchors.centerIn: parent
        width: parent.width - 2*Theme.paddingMedium
        height: parent.width - 2*Theme.paddingMedium
        sourceSize.height: height
        sourceSize.width: width

        smooth: true

        Icon {
            visible: selected
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            source: "image://theme/icon-s-installed?#00FF00"
        }
    }

    onClicked: selected = !selected
}
