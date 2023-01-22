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
            source: "/usr/share/harbour-sailhub/icons/icon-m-commit.svg"
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
        avatarUrl: item.commit.author.user.avatarUrl
        login: item.commit.author.user.login
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
        text: StringHelper.timespan(item.commit.authoredDate)
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
        //% "and others added a commit"
        text: qsTrId("id-event-add-commit")
    }

    BackgroundItem {
        id: commitItem
        anchors {
            top: textLabel.bottom
            left: timeLabel.left
            right: parent.right
        }

        contentHeight: Theme.itemSizeSmall

        Pill {
            id: verifiedPill
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            backgroundColor: {
                if (item.commit.signature === null || !item.commit.signature.isValid) return Theme.secondaryColor
                return SailHubStyles.colorSuccess
            }
            text: {
                //% "Unverified"
                if (item.commit.signature === null || !item.commit.signature.isValid) return qsTrId("id-unverified")
                //% "Verified"
                return qsTrId("id-verified")
            }
        }

        Label {
            anchors {
                left: verifiedPill.right
                leftMargin: Theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            font.pixelSize: Theme.fontSizeSmall
            text: item.commit.abbreviatedOid
        }
    }

    Item {
        id: spacer
        anchors.top: commitItem.bottom
        width: 1
        height: Theme.paddingLarge
    }
}
