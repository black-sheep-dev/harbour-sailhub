import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property int iconSize: Theme.iconSizeSmall
    property alias reactionGroups: repeater.model

    id: reactionsItem

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
            id: repeater

            ReactionLabel {
                icon: "/usr/share/harbour-sailhub/emoji/" + content + ".svg"
                iconSize: reactionsItem.iconSize
                count: users.totalCount
            }
        }
    }
}



