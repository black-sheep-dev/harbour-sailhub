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
        }
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeSmall
    }

    TimelineUserItem {
        id: reviewerItem
        anchors {
            left: iconRect.right
            leftMargin: Theme.paddingMedium
            top: textLabel.bottom
            right: parent.right
        }
        avatarUrl: item.requestedReviewer.avatarUrl
        login: item.requestedReviewer.login
    }

    Item {
        id: spacer
        anchors.top: reviewerItem.bottom
        width: 1
        height: Theme.paddingLarge
    }

    Component.onCompleted: {
        switch (type) {
        case "ReviewRequestedEvent":
            iconImage.source = "image://theme/icon-splus-show-password"
            //% "request a review from"
            textLabel.text = qsTrId("id-event-request-review-from")
            break

        case "ReviewRequestRemovedEvent":
            iconImage.source = "image://theme/icon-m-cancel"
            //% "removed a review request from"
            textLabel.text = qsTrId("id-event-request-review-removed-from")
            break

        default:
            break
        }
    }
}
