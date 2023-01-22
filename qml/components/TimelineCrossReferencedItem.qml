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
            source: "image://theme/icon-m-shortcut"
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

    BackgroundItem {
        id: sourceItem
        anchors {
            top: textLabel.bottom
            left: timeLabel.left
            right: parent.right
        }

        contentHeight: Theme.itemSizeSmall

        Label {
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            wrapMode: Text.Wrap

            text: item.source.title + " #" + item.source.number
        }

        onClicked: {
            switch (item.source["__typename"]) {
            case "Issue":
                pageStack.push(Qt.resolvedUrl("../pages/IssuePage.qml"), { nodeId: item.source.id })
                break

            case "PullRequest":
                pageStack.push(Qt.resolvedUrl("../pages/PullRequestPage.qml"), { nodeId: item.source.id })
                break

            default:
                break
            }
        }
    }

    Item {
        id: spacer
        anchors.top: sourceItem.bottom
        width: 1
        height: Theme.paddingLarge
    }

    Component.onCompleted: {
        switch (item.source["__typename"]) {
        case "Issue":
            //% "mentioned this issue"
            textLabel.text = qsTrId("id-event-mentioned-issue")
            break

        case "PullRequest":
            //% "mentioned this pull request"
            textLabel.text = qsTrId("id-event-mentioned-pull-request")
            break

        default:
            break
        }
    }
}
