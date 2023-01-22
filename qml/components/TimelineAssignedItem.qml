import QtQuick 2.0
import Sailfish.Silica 1.0

import "."
import "../."

Item {
    readonly property bool isSelfAssigned: item.actor.login === item.assignee.login

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
            source: "image://theme/icon-m-media-artists"
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
            //leftMargin: Theme.paddingSmall
            top: timeLabel.bottom
            topMargin: Theme.paddingMedium
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeSmall
    }

    TimelineUserItem {
        visible: !isSelfAssigned
        id: assigneeItem
        anchors {
            left: iconRect.right
            leftMargin: Theme.paddingMedium
            top: isSelfAssigned ? parent.top : textLabel.bottom
            right: parent.right
        }
        avatarUrl: item.assignee.avatarUrl
        login: item.assignee.login
    }

    Item {
        id: spacer
        anchors.top: isSelfAssigned ? textLabel.bottom : assigneeItem.bottom
        width: 1
        height: Theme.paddingLarge
    }

    Component.onCompleted: {
        switch (type) {
        case "AssignedEvent":
            if (isSelfAssigned) {
                //% "self-assigned"
                textLabel.text = qsTrId("id-event-self-assigned")
            } else {
                //% "assigned"
                textLabel.text = qsTrId("id-event-assigned")
            }
            break

        case "UnassignedEvent":
            if (isSelfAssigned) {
                //% "removed his assignment"
                textLabel.text = qsTrId("id-event-self-unassigned")
            } else {
                //% "removed assignment for"
                textLabel.text = qsTrId("id-event-unassigned")
            }
            break

        default:
            //% "did something"
            textLabel.text = qsTrId("id-did-something")
            break
        }
    }
}
