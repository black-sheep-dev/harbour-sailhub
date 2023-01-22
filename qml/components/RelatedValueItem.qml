import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: valueIcon.source
    property alias label: textLabel.text
    property alias value: valueLabel.text
    property alias showValue: valueLabel.visible

    id: relatedItem
    width: parent.width

    Icon {
        id: valueIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        visible: parent.icon.length > 0
        width: Theme.iconSizeMedium
        height: Theme.iconSizeMedium
    }

    Label {
        id: textLabel
        anchors {
            left: valueIcon.visible ? valueIcon.right : parent.left
            leftMargin: valueIcon.visible ? Theme.paddingMedium : Theme.horizontalPageMargin
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

        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignRight
    }
}


