import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property string label
    property real labelSize: 0.4
    property string value

    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height

        Label {
            width: parent.width * labelSize
            anchors.verticalCenter: parent.verticalCenter

            color: Theme.highlightColor
            text: label
        }

        Label {
            width: parent.width * (1.0 - labelSize)
            anchors.verticalCenter: parent.verticalCenter

            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignRight

            text: value
        }
    }
}


