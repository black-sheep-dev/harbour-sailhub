import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias showIcon: openRelatedIcon.visible
    property alias title: titleLabel.text

    width: parent.width
    height: Theme.itemSizeSmall

    Label {
        id: titleLabel
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x - openRelatedIcon.width
        anchors.verticalCenter: parent.verticalCenter
    }

    Icon {
        id: openRelatedIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: titleLabel.right
        source: "image://theme/icon-m-right"
    }
}
