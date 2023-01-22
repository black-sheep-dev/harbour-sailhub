import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeSmall

    Rectangle {
        id: backgroundRect
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: nameLabel.width + 2*Theme.paddingLarge
        height: parent.height - 2*Theme.paddingSmall

        radius: height / 2

        color: "#" + model.color
        opacity: 0.6
    }

    Label {
        id: nameLabel
        x: Theme.horizontalPageMargin + Theme.paddingMedium
        anchors {
            horizontalCenter: backgroundRect.horizontalCenter
            verticalCenter: backgroundRect.verticalCenter
        }
        font.bold: true

        color: Theme.primaryColor

        text: model.name
    }
}
