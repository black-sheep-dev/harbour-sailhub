import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

import org.nubecula.harbour.sailhub 1.0

ListItem {
    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeSmall

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: nameLabel.width + 2*Theme.paddingMedium
        height: parent.height - 2*Theme.paddingSmall

        radius: height / 2

        color: "#" + item.color
        opacity: 0.4
    }

    Label {
        id: nameLabel
        x: Theme.horizontalPageMargin + Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        font.bold: true

        color: Theme.primaryColor

        text: item.name
    }
}
