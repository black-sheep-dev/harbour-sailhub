import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property alias title: counterLabel.text

    height: Theme.itemSizeExtraSmall / 2

    Image {
        id: iconImage
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: height
    }

    Label {
        id: counterLabel
        anchors {
            left: iconImage.right
            leftMargin: Theme.paddingSmall
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        color: Theme.primaryColor
        font.pixelSize: Theme.fontSizeExtraSmall
    }
}
