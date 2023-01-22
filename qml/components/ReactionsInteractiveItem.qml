import QtQuick 2.0
import Sailfish.Silica 1.0

import "../queries"

ListItem {
    property int iconSize: Theme.iconSizeSmall
    property string nodeId
    property var reactionGroups

    id: reactionItems

    AddReactionMutation {
        id: addReactionMutation
        nodeId: reactionItems.nodeId
        onResultChanged: reactionItems.reactionGroups = result.addReaction.subject.reactionGroups
    }

    RemoveReactionMutation {
        id: removeReactionMutation
        nodeId: reactionItems.nodeId
        onResultChanged: reactionItems.reactionGroups = result.removeReaction.subject.reactionGroups
    }

    Item {
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: Math.max(flowLayout.height, defaultIcon.height) + 2*Theme.paddingSmall

        Image {
            id: defaultIcon
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }

            width: iconSize
            height: width
            source: "/usr/share/harbour-sailhub/emoji/default.svg"
        }

        Flow {
            id: flowLayout
            anchors {
                left: defaultIcon.right
                leftMargin: Theme.paddingLarge
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            spacing: Theme.paddingLarge

            Repeater {
                model: reactionItems.reactionGroups

                ReactionLabel {
                    icon: "/usr/share/harbour-sailhub/emoji/" + modelData.content + ".svg"
                    iconSize: reactionItems.iconSize
                    count: modelData.users.totalCount
                }
            }
        }
    }

    menu: ContextMenu {
        id: contextMenu

        MenuItem {
            Row {
                id: iconsRow
                width: parent.width
                height: parent.height

                Repeater {
                    model: reactionGroups

                    ReactionGridItem {
                        anchors.verticalCenter: parent.verticalCenter
                        width: iconsRow.width / reactionGroups.length
                        icon: "/usr/share/harbour-sailhub/emoji/" + modelData.content + ".svg"

                        onClicked: {
                            contextMenu.close()
                            if (selected) {
                                addReactionMutation.content = modelData.content
                                addReactionMutation.execute()
                            } else {
                                removeReactionMutation.content = modelData.content
                                removeReactionMutation.execute()
                            }
                        }

                        Component.onCompleted: selected = modelData.viewerHasReacted
                    }
                }
            }
        }
    }
}



