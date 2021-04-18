import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property string icon
    property alias label: textLabel.text
    property real labelSize: 0.4
    property alias value: valueLabel.text

    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height
        spacing: Theme.paddingSmall

        Icon {
            id: valueIcon
            visible: icon.length > 0
            anchors.verticalCenter: parent.verticalCenter
            source: icon
        }

        Label {
            id: textLabel
            width: {
                if (icon.length === 0)
                    return (parent.width - parent.spacing) * labelSize
                else
                    return (parent.width - valueIcon.width - 2 * parent.spacing) * labelSize
            }

            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: valueLabel
            width: {
                if (icon.length === 0)
                    return (parent.width - parent.spacing) * (1.0 - labelSize)
                else
                    return (parent.width - valueIcon.width - 2 * parent.spacing) * (1.0 - labelSize)
            }
            anchors.verticalCenter: parent.verticalCenter

            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignRight
        }
    }
}


