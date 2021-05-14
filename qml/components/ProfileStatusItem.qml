import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../tools"

BackgroundItem {
    property ProfileStatus profileStatus

    id: profileStatusItem
    width: parent.width

    MarkdownParser {
        id: markdownParser
    }

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        Image {
            id: emojiIcon
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeSmall
            height: width
            sourceSize.width: width
            sourceSize.height: width

            source: {
                if (profileStatus.message.length > 0)
                    return profileStatus.emojiImage
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
                if (profileStatus.message.length > 0)
                    return markdownParser.parse(profileStatus.message)
                else
                    return qsTr("Set status")
            }
        }
    }
}



