import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

BackgroundItem {
    property ProfileStatus profileStatus

    id: profileStatusItem
    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        Image {
            id: emojiIcon
            width: Theme.iconSizeSmall
            height: width
            source: profileStatus.emojiImage
        }

        Label {
            id: textLabel
            width: parent.width - emojiIcon.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap

            color: profileStatusItem.highlighted ? Theme.highlightColor : Theme.primaryColor

            text: profileStatus.message
        }
    }
}



