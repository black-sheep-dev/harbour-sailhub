import QtQuick 2.0
import Sailfish.Silica 1.0

import '../.'

BackgroundItem {
    property bool isViewer: false
    property var profileStatus

    id: profileStatusItem
    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingLarge

        Image {
            id: emojiIcon
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeSmall
            height: width
            sourceSize.width: width
            sourceSize.height: width

            source: {
                if (profileStatus !== undefined)
                    return DataUtils.getEmojiUrl(profileStatus.emoji)
                else
                    return "/usr/share/harbour-sailhub/emoji/default.svg"
            }
        }

        Label {
            id: textLabel
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - emojiIcon.width - parent.spacing
            wrapMode: Text.Wrap
            textFormat: Text.RichText

            color: profileStatusItem.highlighted ? Theme.highlightColor : Theme.primaryColor

            text: {
                if (profileStatus !== undefined)
                    return MarkdownParser.parse(profileStatus.message)
                else
                    //% "Set status"
                    return qsTrId("id-set-status")
            }
        }
    }
}



