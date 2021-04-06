import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    property string icon
    property string label

    x: Theme.horizontalPageMargin
    width: parent.width - 2*x
    height: Theme.iconSizeSmall * 1.5
    spacing: Theme.paddingSmall

    Image {
        id: iconImage
        width: Theme.iconSizeSmall
        height: width
        anchors.verticalCenter: parent.verticalCenter

        source: icon
    }

    LinkedLabel {
        width: parent.width - iconImage.width - parent.spacing
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.Wrap

        color: Theme.highlightColor
        linkColor: Theme.secondaryHighlightColor

        plainText: label

        onLinkActivated: Qt.openUrlExternally(link)
    }
}

