import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingMedium

    Row {
        id: delegateContent
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        Image {
            id: delegateIcon
            anchors.verticalCenter: parent.verticalCenter
            source: model.emoji
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - delegateIcon.width - parent.spacing

            Label {
                width: parent.width - timeSpanLabel.width - parent.spacing
                wrapMode: Text.Wrap
                font.bold: true

                text: model.name
            }

            Label {
                id: timeSpanLabel
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.Wrap

                text: model.description
            }
        }
    }
}
