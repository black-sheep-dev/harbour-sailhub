import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property string avatar
    property string title
    property string subtitle

    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeLarge

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * x
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter

        CircleImage {
            id: avatarIcon
            width: parent.height - 2 * Theme.paddingSmall
            source: avatar
            anchors.verticalCenter: parent.verticalCenter

            fallbackItemVisible: false
        }

        Item {
            width: Theme.paddingMedium
            height: 1
        }

        Column {
            width: parent.width - avatarIcon.width - Theme.paddingMedium
            anchors.verticalCenter: avatarIcon.verticalCenter

            Label {
                width: parent.width
                text: title
                color: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
                font.pixelSize: Theme.fontSizeMedium
            }
            Label {
                text: subtitle

                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
