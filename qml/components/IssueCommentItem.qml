import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import ".."

ListItem {
    id: commentItem
    property var comment
    property string parentId

    width: parent.width
    contentHeight: authorItem.height + bodyLabel.height + reactionsItem.height + Theme.paddingLarge

    AuthorItem {
        id: authorItem
        anchors {
            top: parent.top
        }

        //height: Theme.itemSizeSmall
        avatar: comment.author.avatarUrl
        login: comment.author.login
        subtitle: StringHelper.timespan(comment.createdAt)
    }

    Rectangle {
        id: decoRect
        anchors {
           top: authorItem.bottom
           topMargin: Theme.paddingSmall
           bottom: reactionsItem.top
           left: parent.left
           leftMargin: Theme.paddingLarge + Theme.paddingSmall
        }
        width: 4
        gradient: Gradient {
            GradientStop { position: 0.0; color: Theme.highlightColor; }
            GradientStop { position: 1.0; color: "transparent"; }
        }
    }

    MarkdownLabel {
        id: bodyLabel
        anchors {
            left: decoRect.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            top: authorItem.bottom
        }
        text: MarkdownParser.parse(comment.body)
    }

    ReactionsItem {
        id: reactionsItem
        anchors {
            top: bodyLabel.bottom
            topMargin: Theme.paddingLarge
        }
        width: parent.width

        nodeId: comment.id
        reactionGroups: comment.reactionGroups
        viewerCanReact: comment.viewerCanReact
    }
}


