import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../."

ListItem {
    id: delegate
    width: parent.width
    contentHeight: infoLabel.y + infoLabel.height + Theme.paddingSmall

    Image {
        id: delegateIcon
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
        }
        source: DataHelper.getEmojiFromHtml(model.category.emojiHTML)
        width: Theme.iconSizeSmallPlus
        height: Theme.iconSizeSmallPlus
    }

    Rectangle {
        anchors {
           horizontalCenter: delegateIcon.horizontalCenter
           top: delegateIcon.bottom
           topMargin: Theme.paddingMedium
           bottom: parent.bottom
        }
        width: 4
        opacity: 0.5
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent"; }
            GradientStop { position: 0.5; color: Theme.highlightColor; }
            GradientStop { position: 1.0; color: "transparent"; }
        }
    }

    Label {
        id: categoryLabel
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeSmall
        color: pressed ? Theme.highlightColor : Theme.primaryColor
        text: model.category.name
    }

    Label {
        id: titleLabel
        anchors {
            top: categoryLabel.bottom
            topMargin: Theme.paddingMedium
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }
        wrapMode: Text.Wrap
        font.bold: true
        color: pressed ? Theme.highlightColor : Theme.primaryColor
        text: model.title
    }

    CircleImage {
        id: authorAvatar
        anchors {
            top: titleLabel.bottom
            topMargin: Theme.paddingMedium
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
        }
        width: Theme.iconSizeSmall
        height: Theme.iconSizeSmall
        source: model.author.avatarUrl
    }

    Label {
        id: authorLabel
        anchors {
            left: authorAvatar.right
            leftMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: authorAvatar.verticalCenter
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: true
        color: pressed ? Theme.highlightColor : Theme.primaryColor
        text: model.author.login
    }

    Label {
        id: infoLabel
        anchors {
            top: authorAvatar.bottom
            topMargin: Theme.paddingSmall
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeExtraSmall
        color: pressed ? Theme.highlightColor : Theme.primaryColor
        //% "started the discussion %1 ago"
        text: qsTrId("id-started-discussion").arg(StringHelper.timespan(model.createdAt))
    }


//    Column {
//        id: delegateContent
//        x: Theme.horizontalPageMargin
//        width: parent.width - 2*x
//        anchors.verticalCenter: parent.verticalCenter
//        spacing: Theme.paddingSmall

//        Row {
//            width: parent.width
//            spacing: Theme.paddingMedium

//            Image {
//                id: delegateIcon
//                anchors.top: parent.top
//                source: DataHelper.getEmojiFromHtml(model.category.emojiHTML)
//                width: Theme.iconSizeSmallPlus
//                height: Theme.iconSizeSmallPlus
//            }

//            Column {
//                width: parent.width - delegateIcon.width - parent.spacing
//                spacing: Theme.paddingSmall

//                Row {
//                    width: parent.width
//                    spacing: Theme.paddingSmall

//                    Label {
//                        anchors.verticalCenter: parent.verticalCenter
//                        width: parent.width - timeSpanLabel.width - parent.spacing
//                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                        font.pixelSize: Theme.fontSizeSmall

//                        text: model.category.name
//                    }

//                    Label {
//                        id: timeSpanLabel
//                        anchors.verticalCenter: parent.verticalCenter
//                        font.pixelSize: Theme.fontSizeSmall

//                        text: model.updatedAtTimeSpan
//                    }
//                }

//                Label {
//                    width: parent.width
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                    font.bold: true

//                    text: model.title
//                }

//                Row {
//                    width: parent.width
//                    spacing: Theme.paddingSmall

//                    CircleImage {
//                        id: authorAvatar
//                        anchors.verticalCenter: parent.verticalCenter
//                        width: Theme.iconSizeSmall
//                        height: Theme.iconSizeSmall
//                        source: model.author.avatarUrl
//                    }

//                    Label {
//                        width: parent.width - authorAvatar.width - commentIcon.width - commentsLabel.width - 3 * parent.spacing
//                        anchors.verticalCenter: commentIcon.verticalCenter
//                        font.pixelSize: Theme.fontSizeExtraSmall
//                        color: pressed ? Theme.highlightColor : Theme.primaryColor

//                        //% "started the discussion"
//                        text: model.author.login + " " + qsTrId("id-started-discussion")
//                    }

//                    Icon {
//                        id: commentIcon
//                        anchors.verticalCenter: parent.verticalCenter
//                        source: "image://theme/icon-s-chat"
//                    }

//                    Label {
//                        id: commentsLabel
//                        anchors.verticalCenter: commentIcon.verticalCenter
//                        font.pixelSize: Theme.fontSizeSmall
//                        color: pressed ? Theme.highlightColor : Theme.primaryColor

//                        text: StringHelper.count(model.comments.totalCount)
//                    }
//                }

//                Row {
//                    visible: item.locked
//                    width: parent.width
//                    spacing: Theme.paddingMedium

//                    LockReasonPill { lockReason: item.lockReason }
//                }
//            }
//        }
//    }
}
