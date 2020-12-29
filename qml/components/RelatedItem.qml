import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property bool showIcon: true
    property string title

    width: parent.width
    height: Theme.itemSizeSmall

    Label {
        id: titleLabel
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x - openRelatedIcon.width
        anchors.verticalCenter: parent.verticalCenter

        color: Theme.highlightColor

        text: title
    }

    Image {
        visible: showIcon
        id: openRelatedIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: titleLabel.right
        source: "image://theme/icon-m-right"
    }
}
