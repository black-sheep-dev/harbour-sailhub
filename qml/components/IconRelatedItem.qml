import QtQuick 2.0

import Sailfish.Silica 1.0

BackgroundItem {
    property string icon
    property bool showNextIcon: true
    property string title

    width: parent.width
    height: Theme.itemSizeSmall

    Item {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height

        Icon {
            id: itemIcon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: icon
        }

        Item {
            id: spacerItem
            anchors.left: itemIcon.right
            width: Theme.paddingMedium
            height: 1
        }

        Label {
            id: titleLabel
            anchors.left: spacerItem.right
            anchors.right: openNextIcon.left
            anchors.verticalCenter: parent.verticalCenter

            text: title
        }

        Icon {
            visible: showNextIcon
            id: openNextIcon
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            source: "image://theme/icon-m-right"
        }
    }
}
