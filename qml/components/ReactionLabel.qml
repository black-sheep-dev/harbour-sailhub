import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias icon: iconImage.source
    property int iconSize: Theme.iconSizeSmall
    property alias count: countLabel.text
    property bool viewerHasReacted: false

    id: iconLabel

    visible: count > 0
    height: iconSize
    width: iconRect.width + countLabel.width

    Rectangle {
        id: iconRect
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        width: iconLabel.height
        height: width
        radius: 0.5 * width

        color: viewerHasReacted ? Theme.secondaryColor : "transparent"

        Image {
            id: iconImage
            anchors.centerIn: parent
            width: iconLabel.height
            height: width
        }
    }

    Label {
        id: countLabel
        anchors {
            left: iconRect.right
            leftMargin: Theme.paddingSmall
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: Theme.fontSizeSmall
    }
}



