import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeLarge

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        CircleImage {
            id: avatarIcon
            width: parent.height - 2 * Theme.paddingSmall
            source: model.avatarUrl
            anchors.verticalCenter: parent.verticalCenter

            fallbackItemVisible: false

            BusyIndicator {
                size: BusyIndicatorSize.Medium
                anchors.centerIn: avatarIcon
                running: avatarIcon.status === Image.Loading
            }
        }

        Column {
            width: parent.width - avatarIcon.width - Theme.paddingMedium
            anchors.verticalCenter: avatarIcon.verticalCenter
            spacing: Theme.paddingSmall

            Label {
                width: parent.width
                color: pressed ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                font.bold: true
                wrapMode: Text.Wrap

                text: model.name.length > 0 ? model.name : login
            }
            Label {
                color: pressed ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.Wrap

                text: model.login
            }
        }
    }
}
