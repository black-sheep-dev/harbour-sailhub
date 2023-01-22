import QtQuick 2.0
import Sailfish.Silica 1.0

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
        height: width
        source: model.avatarUrl + "?size=" + width
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
            font {
                pixelSize: Theme.fontSizeMedium
                bold: true
            }
            wrapMode: Text.Wrap

            text: (model.name.length > 0 || model.name !==  null) ? model.name : model.login
        }
        Label {
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.Wrap
            text: model.login
        }
    }
}
