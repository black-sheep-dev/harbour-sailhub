import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../queries/"

ListItem {
    property int iconSize: Theme.iconSizeSmall
    property string nodeId
    property var reactionGroups
    property alias viewerCanReact: reactionsItem.enabled

    id: reactionsItem

    enabled: viewerCanReact

    contentHeight: Math.max(Theme.itemSizeSmall, reactionsRow.height + 2*Theme.paddingMedium)

    AddReactionMutation {
        id: addReactionMutation
        nodeId: reactionsItem.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            reactionGroups = result.addReaction.subject.reactionGroups
        }
    }

    RemoveReactionMutation {
        id: removeReactionMutation
        nodeId: reactionsItem.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            reactionGroups = result.removeReaction.subject.reactionGroups
        }
    }

    Item {
       id: reactionsRow
       anchors.verticalCenter: parent.verticalCenter
       x: Theme.horizontalPageMargin
       width: parent.width - 2*x
       height: Math.max(defaultIcon.height, flowLayout.height)

       Image {
           id: defaultIcon
           anchors {
               left: parent.left
               top: parent.top
           }

           width: iconSize
           height: width
           source: "qrc:///emoji/default"
       }

       Flow {
           id: flowLayout
           anchors {
               left: defaultIcon.right
               leftMargin: Theme.paddingLarge
               right: parent.right
           }

           spacing: Theme.paddingLarge

           Repeater {
               model: reactionGroups

               ReactionLabel {
                   readonly property string reaction: modelData.content
                   icon: "qrc:///emoji/" + modelData.content.toLowerCase()
                   iconSize: reactionsItem.iconSize
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
                        icon: "qrc:///emoji/" + modelData.content.toLowerCase()
                        selected: modelData.viewerHasReacted

                        onClicked: {
                            contextMenu.close()

                            if (selected) {
                                addReactionMutation.content = modelData.content
                                Api.request(addReactionMutation)
                            } else {
                                removeReactionMutation.content = modelData.content
                                Api.request(removeReactionMutation)
                            }
                        }
                    }
                }
            }
        }
    }
}



