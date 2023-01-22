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
            source: "/usr/share/harbour-sailhub/icons/icon-m-tag.svg"
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

    Pill {
        anchors {
            left: textLabel.right
            leftMargin: Theme.paddingMedium
            verticalCenter: textLabel.verticalCenter
        }

        showIcon: false
        backgroundColor: "#" + item.label.color
        backgroundOpacity: 0.6
        text: item.label.name

        MouseArea {
            anchors.fill: parent
            onClicked: pageStack.push(Qt.resolvedUrl("../pages/LabelPage.qml"), { nodeId: item.label.id })
        }
    }

    Item {
        id: spacer
        anchors.top: textLabel.bottom
        width: 1
        height: Theme.paddingLarge
    }

    Component.onCompleted: {
        switch (type) {
        case "LabeledEvent":
            //% "added label"
            textLabel.text = qsTrId("id-event-labeled")
            break

        case "UnlabeledEvent":
            //% "removed label"
            textLabel.text = qsTrId("id-event-unlabeled")
            break

        default:
            //% "did something"
            textLabel.text = qsTrId("id-did-something")
            break
        }
    }
}
