import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property string icon
    property string title

    height: Theme.itemSizeExtraSmall / 2

    Row {
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Image {
            height: parent.height
            width: height

            anchors.verticalCenter: parent.verticalCenter
            source: icon
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            text: title
        }
    }
}
