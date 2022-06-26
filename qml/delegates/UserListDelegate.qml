import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: Math.max(avatarIcon.height, contentColumn.height) + 2*Theme.paddingMedium

    CircleImage {
        id: avatarIcon
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }

        width: Theme.iconSizeLarge
        source: item.avatarUrl + "?size=" + width


        fallbackItemVisible: false

        BusyIndicator {
            size: BusyIndicatorSize.Medium
            anchors.centerIn: avatarIcon
            running: avatarIcon.status === Image.Loading
        }
    }

    Column {
        id: contentColumn
        anchors {
            left: avatarIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        spacing: Theme.paddingSmall

        Label {
            width: parent.width
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeMedium
            font.bold: true
            wrapMode: Text.Wrap

            text: (item.name.length > 0 || item.name !==  null) ? item.name : item.login
        }
        Label {
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.Wrap

            text: item.login
        }
    }
}
