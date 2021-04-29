import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: contentRow.height + 2*Theme.paddingMedium

    Row {
        id: contentRow
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        CircleImage {
            id: avatarIcon
            width: Theme.iconSizeLarge
            source: model.avatarUrl + "?size=" + width
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
