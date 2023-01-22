import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."

Item {
    property int count: 0

    height: stargazerLabel.height
    width: starIcon.width + stargazerLabel.width + Theme.paddingMedium

    Icon {
        id: starIcon
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }

        source: "image://theme/icon-s-new?" + (count > 0 ? SailHubStyles.colorStarred : Theme.primaryColor)
    }

    Label {
        id: stargazerLabel
        anchors {
            verticalCenter: parent.verticalCenter
            left: starIcon.right
            leftMargin: Theme.paddingMedium
        }
        font.pixelSize: Theme.fontSizeSmall
        color: Theme.primaryColor

        text: StringHelper.count(count)
    }
}
