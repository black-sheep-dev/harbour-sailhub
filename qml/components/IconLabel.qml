import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: iconImage.source
    property alias label: textLabel.text

    id: iconLabel
    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: Theme.iconSizeSmall * 1.5
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        Image {
            id: iconImage
            width: Theme.iconSizeSmall
            height: width
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: textLabel
            width: parent.width - iconImage.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap

            color: iconLabel.highlighted ? Theme.highlightColor : Theme.primaryColor
        }
    }
}



