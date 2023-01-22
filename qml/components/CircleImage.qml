import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Image {
    id: circleImage
    width: Theme.itemSizeSmall
    height: Theme.itemSizeSmall
    sourceSize.width: width
    sourceSize.height: height

    asynchronous: true
    cache: true

    layer.enabled:true
    layer.effect: OpacityMask {
        maskSource: Item {
            width: circleImage.width
            height: circleImage.height
            Rectangle {
                anchors.centerIn: parent
                width: circleImage.width
                height: circleImage.height
                radius: Math.min(width, height)
            }
        }
    }

    Rectangle {
        id: overlay
        visible: parent.status !== Image.Ready || parent.status === Image.Error
        anchors.fill: parent
        color: Theme.backgroundGlowColor
        opacity: Theme.opacityOverlay
        radius: width / 2

        Icon {
            anchors.centerIn: parent
            width: parent.width * 0.4
            height: height
            opacity: 0.4
            source: "image://theme/icon-m-media-artists"
        }

        SequentialAnimation {
            running: parent.status !== Image.Ready
            loops: Animation.Infinite
            ColorAnimation {
                target: overlay
                property: "color"
                duration: 1500
                from: Theme.backgroundGlowColor
                to: Theme.secondaryHighlightColor
            }
            ColorAnimation {
                target: overlay
                property: "color"
                duration: 1500
                to: Theme.backgroundGlowColor
                from: Theme.secondaryHighlightColor
            }
        }
    }
}
