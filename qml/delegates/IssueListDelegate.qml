import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../."

ListItem {

    id: delegate
    width: parent.width
    contentHeight: titleLabel.y + titleLabel.height + Theme.paddingSmall

    Icon {
        id: delegateIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            top: parent.top
            topMargin: Theme.paddingSmall
        }
        source: model.closed ?
                    "image://theme/icon-s-installed?" +  SailHubStyles.colorStatusClosed :
                    "image://theme/icon-s-high-importance?" + SailHubStyles.colorStatusOpen
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
            GradientStop { position: 0.5; color: model.closed ? SailHubStyles.colorStatusClosed : SailHubStyles.colorStatusOpen; }
            GradientStop { position: 1.0; color: "transparent"; }
        }
    }

    Label {
        id: headerLabel
        anchors {
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
            top: parent.top
            topMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }
        truncationMode: TruncationMode.Fade
        font.pixelSize: Theme.fontSizeTiny
        text: model.repository.nameWithOwner + " #" + model.number
    }

    Label {
        id: timeSpanLabel
        anchors {
            top: headerLabel.bottom
            left: headerLabel.left
            right: commentIcon.left
            rightMargin: Theme.paddingMedium
        }

        font.pixelSize: Theme.fontSizeTiny
        text: StringHelper.timespan(model.createdAt)
    }

    Label {
        id: commentsLabel
        anchors {
            verticalCenter: commentIcon.verticalCenter
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }

        font.pixelSize: Theme.fontSizeSmall
        color: pressed ? Theme.highlightColor : Theme.primaryColor
        text: model.comments.totalCount
    }

    Icon {
        id: commentIcon
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            right: commentsLabel.left
            rightMargin: Theme.paddingSmall
        }
        source: "image://theme/icon-s-chat"
    }

    CircleImage {
        id: avatarImage
        anchors {
            left: timeSpanLabel.left
            top: timeSpanLabel.bottom
            topMargin: Theme.paddingSmall
        }
        width: Theme.iconSizeSmall
        height: width
        source: model.author.avatarUrl
    }

    Label {
        anchors {
            left: avatarImage.right
            leftMargin: Theme.paddingMedium
            verticalCenter: avatarImage.verticalCenter
            right: timeSpanLabel.right
        }
        font.pixelSize: Theme.fontSizeSmall
        text: model.author.login
    }

    Label {
        id: titleLabel
        anchors {
            left: headerLabel.left
            top: avatarImage.bottom
            topMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }

        wrapMode: Text.Wrap
        font.bold: true
        text: model.title
    }
}
