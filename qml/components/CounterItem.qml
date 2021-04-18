import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property alias title: counterLabel.text

    height: Theme.itemSizeExtraSmall / 2

    Row {
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Image {
            id: iconImage
            height: parent.height
            width: height

            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: counterLabel
            anchors.verticalCenter: parent.verticalCenter
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
        }
    }
}
