import QtQuick 2.0
import Sailfish.Silica 1.0

import "."
import "../."

Item {
    x: Theme.horizontalPageMargin
    width: parent.width - 2*x
    height: spacer.y + spacer.height

    Rectangle {
        id: decoRect
        anchors {
            left: parent.left
            leftMargin: SailHubStyles.spacingTimeline
            top: parent.top
            bottom: parent.bottom
        }
        width: SailHubStyles.thicknessTimeline
        color: SailHubStyles.colorTimeline
        opacity: SailHubStyles.opacityTimeline
    }

    Rectangle {
        id: iconRect
        anchors {
            verticalCenter: userItem.verticalCenter
            left: parent.left
        }
        width: Theme.iconSizeSmall + 2*Theme.paddingSmall
        height: width
        radius: width * 0.5

        color: SailHubStyles.colorEventDefault

        Icon {
            id: iconImage
            anchors.centerIn: parent
            width: Theme.iconSizeSmall
            height: width
            smooth: true
            source: "image://theme/icon-m-edit"
        }
    }

    TimelineUserItem {
        id: userItem
        anchors {
            left: iconRect.right
            leftMargin: Theme.paddingMedium
            top: parent.top
            right: parent.right
        }
        avatarUrl: item.actor.avatarUrl
        login: item.actor.login
    }

    Label {
        id: timeLabel
        anchors {
            left: userItem.left
            leftMargin: Theme.paddingSmall
            top: userItem.bottom
            right: parent.right
        }
        font.pixelSize: Theme.fontSizeTiny
        text: StringHelper.timespan(item.createdAt)
    }

    Label {
        id: textLabel
        anchors {
            left: timeLabel.left
            top: timeLabel.bottom
            topMargin: Theme.paddingMedium
            right: parent.right    
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeSmall
        //% "changed title"
        text: qsTrId("id-event-changed-title")
    }

    Label {
        id: oldTitleLabel
        anchors {
            left: timeLabel.left
            top: textLabel.bottom
            topMargin: Theme.paddingMedium
            right: parent.right
        }
        wrapMode: Text.Wrap
        font {
            pixelSize: Theme.fontSizeSmall
            strikeout: true
        }
        text: item.previousTitle
    }

    Label {
        id: newTitleLabel
        anchors {
            left: timeLabel.left
            top: oldTitleLabel.bottom
            topMargin: Theme.paddingMedium
            right: parent.right
        }
        wrapMode: Text.Wrap
        font {
            pixelSize: Theme.fontSizeSmall
            bold: true
        }
        text: item.currentTitle
    }

    Item {
        id: spacer
        anchors.top: newTitleLabel.bottom
        width: 1
        height: Theme.paddingLarge
    }
}
