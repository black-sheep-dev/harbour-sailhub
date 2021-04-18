import QtQuick 2.0

import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: itemIcon.source
    property bool showNextIcon: true
    property alias title: titleLabel.text

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
