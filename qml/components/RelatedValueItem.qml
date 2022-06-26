import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property string icon
    property alias label: textLabel.text
    property alias value: valueLabel.text
    property bool showValue: true

    width: parent.width

    Icon {
        id: valueIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        visible: icon.length > 0
        width: Theme.iconSizeMedium
        height: Theme.iconSizeMedium
        fillMode: Image.PreserveAspectFit
        source: icon
    }

    Label {
        id: textLabel
        anchors {
            left: icon.length > 0 ? valueIcon.right : parent.left
            leftMargin: icon.length > 0 ? Theme.paddingMedium : Theme.horizontalPageMargin
            right: valueLabel.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.Wrap
    }

    Label {
        id: valueLabel
        anchors {
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }

        visible: showValue

        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignRight
    }
}


