import QtQuick 2.0
import Sailfish.Silica 1.0

import '..'

LinkedLabel {
    id: bodyLabel
    width: parent.width

    font.pixelSize: Theme.fontSizeSmall
    color: Theme.primaryColor
    textFormat: Text.RichText

    onLinkActivated: linkHelper.openLink(link)
}
