import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias backgroundColor: background.color
    property real backgroundOpacity: 0.2
    property alias color: textLabel.color
    property alias text: textLabel.text
    property alias icon: pillIcon.source
    property alias showIcon: pillIcon.visible


    id: iconLabel
    width: background.width
    height: Theme.fontSizeTiny * 2

    Rectangle {
        id: background
        width: contentRow.width + parent.height
        height: parent.height
        radius: parent.height / 2
        opacity: backgroundOpacity
    }

    Row {
        id: contentRow
        anchors.centerIn: background
        spacing: Theme.paddingSmall

        Image {
            id: pillIcon
            visible: source.length > 0
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeExtraSmall
            height: Theme.iconSizeExtraSmall
        }

        Label {
            id: textLabel
            anchors.verticalCenter: parent.verticalCenter
            font {
                pixelSize: Theme.fontSizeTiny
                bold: true
            }
        }
    }
}



