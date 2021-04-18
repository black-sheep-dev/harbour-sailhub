import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias label: textLabel.text
    property real labelSize: 0.4
    property alias value: valueLabel.text

    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height

        Label {
            id: textLabel
            width: parent.width * labelSize
            anchors.verticalCenter: parent.verticalCenter

            color: Theme.highlightColor
        }

        Label {
            id: valueLabel
            width: parent.width * (1.0 - labelSize)
            anchors.verticalCenter: parent.verticalCenter

            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignRight
        }
    }
}


