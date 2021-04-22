import QtQuick 2.0
import Sailfish.Silica 1.0

LinkedLabel {
    id: bodyLabel
    width: parent.width

    font.pixelSize: Theme.fontSizeSmall
    color: Theme.primaryColor
    textFormat: Text.RichText

    onLinkActivated: Qt.openUrlExternally(link)
}
