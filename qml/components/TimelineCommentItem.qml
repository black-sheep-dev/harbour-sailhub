import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../queries/"
import "../."

ListItem {
    property var reactionGroups: item.reactionGroups

    id: commentItem

    width: parent.width
    height: timelineSpacerBottom.y + timelineSpacerBottom.height + contextMenu.height
    contentHeight: timelineSpacerBottom.y + timelineSpacerBottom.height

    menu: ContextMenu {
        id: contextMenu

        MenuLabel {
            visible: item.viewerCanReact
            //% "Reactions"
            text: qsTrId("id-reactions")
        }
        MenuItem {
            visible: item.viewerCanReact
            Row {
                id: iconsRow
                width: parent.width
                height: parent.height

                Repeater {
                    model: item.reactionGroups

                    ReactionGridItem {
                        anchors.verticalCenter: parent.verticalCenter
                        width: iconsRow.width / item.reactionGroups.count
                        icon: "/usr/share/harbour-sailhub/emoji/" + content + ".svg"

                        onClicked: {
                            contextMenu.close()
                            selected ? addReaction(item.id, content, index) : removeReaction(item.id, content, index)
                        }

                        Component.onCompleted: selected = viewerHasReacted
                    }
                }
            }
        }

        MenuLabel {
            //% "Interactions"
            text: qsTrId("id-interactions")
        }
        MenuItem {
            visible: item.viewerCanDelete
            //% "Delete"
            text: qsTrId("id-delete")
            //% "Deleting comment"
            onClicked: delegate.remorseAction(qsTrId("id-deleting-comment"), function() {
                deleteComment(item.id, index)
            })
        }
        MenuItem {
            visible: item.viewerCanUpdate
            //% "Edit"
            text: qsTrId("id-edit")
            onClicked: updateComment(item.id, item.bodyText, index)
        }
        MenuItem {
            //% "Quote reply"
            text: qsTrId("id-quote-reply")
            onClicked: replyToComment(item.bodyText)
        }
    }

    Rectangle {
        id: timelineSpacerTop
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: Theme.horizontalPageMargin + SailHubStyles.spacingTimeline
        }
        width: SailHubStyles.thicknessTimeline
        height: Theme.paddingSmall
        color: SailHubStyles.colorTimeline
        opacity: SailHubStyles.opacityTimeline
    }

    Rectangle {
        id: horizantalSpacerTop
        anchors {
            top: timelineSpacerTop.bottom
        }
        width: parent.width
        height: SailHubStyles.thicknessTimeline
        color: SailHubStyles.colorTimeline
        opacity: SailHubStyles.opacityTimeline
    }

    Rectangle {
        anchors {
            top: horizantalSpacerTop.bottom
            bottom: horizantalSpacerBottom.top
        }
        width: parent.width
        color: Theme.overlayBackgroundColor
        opacity: Theme.opacityFaint
    }

    AuthorItem {
        id: authorItem
        anchors {
            top: horizantalSpacerTop.bottom
            topMargin: Theme.paddingSmall
        }

        //height: Theme.itemSizeSmall
        avatar: item.author.avatarUrl
        login: item.author.login
        subtitle: StringHelper.timespan(item.createdAt)
    }

    MarkdownLabel {
        id: bodyLabel
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            top: authorItem.bottom
        }
        text: MarkdownParser.parse(item.body)
    }

    ReactionsItem {
        id: reactionsItem
        anchors {
            top: bodyLabel.bottom
            topMargin: Theme.paddingMedium
        }
        width: parent.width
        reactionGroups: item.reactionGroups
    }

    Rectangle {
        id: horizantalSpacerBottom
        anchors {
            top: reactionsItem.bottom
            topMargin: Theme.paddingSmall
        }
        width: parent.width
        height: SailHubStyles.thicknessTimeline
        color: Theme.secondaryHighlightColor
        opacity: SailHubStyles.opacityTimeline
    }

    Rectangle {
        id: timelineSpacerBottom
        anchors {
            top: horizantalSpacerBottom.bottom
            left: parent.left
            leftMargin: Theme.horizontalPageMargin + SailHubStyles.spacingTimeline
        }
        width: SailHubStyles.thicknessTimeline
        height: Theme.paddingSmall
        color: SailHubStyles.colorTimeline
        opacity: SailHubStyles.opacityTimeline
    }
}


