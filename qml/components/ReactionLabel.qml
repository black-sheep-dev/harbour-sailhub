import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias icon: iconImage.source
    property int iconSize: Theme.iconSizeSmall
    property alias count: countLabel.text

    id: iconLabel

    visible: count > 0
    height: iconSize
    width: contentRow.width

    Row {
        id: contentRow
        height: parent.height
        spacing: Theme.paddingSmall

        Image {
            id: iconImage
            width: iconLabel.height
            height: width
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: countLabel
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Theme.fontSizeSmall
        }
    }
}



