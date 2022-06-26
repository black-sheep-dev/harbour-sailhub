import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import '..'

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingMedium

    Column {
        id: delegateContent
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Image {
                id: delegateIcon
                anchors.top: parent.top
                source: DataUtils.getEmojiFromHtml(item.category.emojiHTML)
                width: Theme.iconSizeSmallPlus
                height: Theme.iconSizeSmallPlus
            }

            Column {
                width: parent.width - delegateIcon.width - parent.spacing
                spacing: Theme.paddingSmall

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - timeSpanLabel.width - parent.spacing
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.pixelSize: Theme.fontSizeSmall

                        text: item.category.name
                    }

                    Label {
                        id: timeSpanLabel
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall

                        text: item.updatedAtTimeSpan
                    }
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.bold: true

                    text: item.title
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    CircleImage {
                        id: authorAvatar
                        anchors.verticalCenter: parent.verticalCenter
                        width: Theme.iconSizeSmall
                        fallbackItemVisible: false

                        source: item.author.avatarUrl
                    }

                    Label {
                        width: parent.width - authorAvatar.width - commentIcon.width - commentsLabel.width - 3 * parent.spacing
                        anchors.verticalCenter: commentIcon.verticalCenter
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: pressed ? Theme.highlightColor : Theme.primaryColor

                        //% "started the discussion"
                        text: item.author.login + " " + qsTrId("id-started-discussion")
                    }       

                    Icon {
                        id: commentIcon
                        anchors.verticalCenter: parent.verticalCenter
                        source: "image://theme/icon-s-chat"
                    }

                    Label {
                        id: commentsLabel
                        anchors.verticalCenter: commentIcon.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall
                        color: pressed ? Theme.highlightColor : Theme.primaryColor

                        text: StringHelper.count(item.comments.totalCount)
                    }
                }

//                Row {
//                    visible: item.locked
//                    width: parent.width
//                    spacing: Theme.paddingMedium

//                    LockReasonPill { lockReason: item.lockReason }
//                }
            }
        }
    }
}
