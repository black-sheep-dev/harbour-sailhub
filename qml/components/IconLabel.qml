import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property alias label: textLabel.text

    id: iconLabel
    width: parent.width
    height: textLabel.height + 2*Theme.paddingSmall

    Image {
        id: iconImage
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        width: Theme.iconSizeSmall
        height: width
    }

    Label {
        id: textLabel
        anchors {
            left: iconImage.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.Wrap

        color: iconLabel.highlighted ? Theme.highlightColor : Theme.primaryColor
    }
}
