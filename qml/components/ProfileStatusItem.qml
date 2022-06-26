import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import '..'

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
                if (profileStatus !== null)
                    return DataUtils.getEmojiUrl(profileStatus.emoji)
                else
                    return "qrc:///emoji/default"
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
                if (profileStatus !== null)
                    return MarkdownParser.parse(profileStatus.message)
                else
                    //% "Set status"
                    return qsTrId("id-set-status")
            }
        }
    }
}



