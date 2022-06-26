import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias color: colorRect.color
    property alias name: nameLabel.text
    property int fontSize: Theme.fontSizeSmall

    visible: name.length > 0
    height: nameLabel.height
    width: colorRect.width + nameLabel.width + Theme.paddingMedium

    Rectangle {
        id: colorRect
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        height: parent.height * 0.5
        width: height

        radius: parent.height * 0.25
    }

    Label {
        id: nameLabel
        anchors {
            verticalCenter: parent.verticalCenter
            left: colorRect.right
            leftMargin: Theme.paddingMedium
        }
        font.pixelSize: fontSize
    }
}
