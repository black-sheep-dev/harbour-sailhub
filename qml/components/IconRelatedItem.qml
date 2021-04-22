import QtQuick 2.0

import Sailfish.Silica 1.0

BackgroundItem {
    property alias icon: itemIcon.source
    property bool showNextIcon: true
    property alias title: titleLabel.text

    width: parent.width
    height: Theme.itemSizeSmall

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height
        spacing: Theme.paddingMedium

        Icon {
            id: itemIcon
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }

        Label {
            id: titleLabel
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - itemIcon.width - openNextIcon.width - 2 * parent.spacing
        }

        Icon {
            visible: showNextIcon
            id: openNextIcon
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-right"
        }
    }
}
