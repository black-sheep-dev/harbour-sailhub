import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property bool selected: false

    width: Theme.itemSizeHuge
    height: width

    Image {
        id: iconImage
        anchors.centerIn: parent
        width: parent.width - 2*Theme.paddingMedium
        height: parent.width - 2*Theme.paddingMedium
        sourceSize.height: height
        sourceSize.width: width

        smooth: true
    }

    Rectangle {
        visible: selected
        anchors {
            left: parent.left
            leftMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.paddingSmall
            bottom: parent.bottom
        }

        height: 4
        color: Theme.highlightColor
    }

    onClicked: selected = !selected
}
