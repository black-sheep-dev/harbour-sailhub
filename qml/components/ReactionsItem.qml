import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

BackgroundItem {
    property int iconSize: Theme.iconSizeSmall
    property Interactable node
    property bool locked: false

    id: reactionsItem
    width: parent.width
    height: contentRow.height + 2 * Theme.paddingSmall

    Row {
        id: contentRow
        x: Theme.horizontalPageMargin
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        Image {
            visible: !locked
            id: defaultIcon
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            width: iconSize
            height: width
            source: "qrc:///emoji/default"
        }

        Flow {
            width: parent.width - defaultIcon.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingSmall

            ReactionLabel {
                id: thumbsUpLabel
                icon: "qrc:///emoji/thumbs_up"
                iconSize: reactionsItem.iconSize
                count: node.reactionThumbsUpCount
            }
            ReactionLabel {
                id: thumbsDownLabel
                icon: "qrc:///emoji/thumbs_down"
                iconSize: reactionsItem.iconSize
                count: node.reactionThumbsDownCount
            }
            ReactionLabel {
                id: laughLabel
                icon: "qrc:///emoji/laugh"
                iconSize: reactionsItem.iconSize
                count: node.reactionLaughCount
            }
            ReactionLabel {
                id: hoorayLabel
                icon: "qrc:///emoji/hooray"
                iconSize: reactionsItem.iconSize
                count: node.reactionHoorayCount
            }
            ReactionLabel {
                id: confusedLabel
                icon: "qrc:///emoji/confused"
                iconSize: reactionsItem.iconSize
                count: node.reactionConfusedCount
            }
            ReactionLabel {
                id: heartLabel
                icon: "qrc:///emoji/heart"
                iconSize: reactionsItem.iconSize
                count: node.reactionHeartCount
            }
            ReactionLabel {
                id: rocketLabel
                icon: "qrc:///emoji/rocket"
                iconSize: reactionsItem.iconSize
                count: node.reactionRocketCount
            }
            ReactionLabel {
                id: eyesLabel
                icon: "qrc:///emoji/eyes"
                iconSize: reactionsItem.iconSize
                count: node.reactionEyesCount
            }
        }
    }
}



