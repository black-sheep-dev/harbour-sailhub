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
            source: "/usr/share/harbour-sailhub/icons/icon-m-bookmarked.svg"
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

        text: {
            if (type === "ConnectedEvent") {
                switch (item.subject["__typename"]) {
                case "Issue":
                    //% "linked this to an issue"
                    return qsTrId("id-event-linked-to-issue")

                case "PullRequest":
                    //% "linked this to a pull request"
                    return qsTrId("id-event-linked-to-pull-request")
                }
            } else if (type === "DisconnectedEvent") {
                switch (item.subject["__typename"]) {
                case "Issue":
                    //% "unlinked this from an issue"
                    return qsTrId("id-event-unlinked-from-issue")

                case "PullRequest":
                    //% "unlinked this from a pull request"
                    return qsTrId("id-event-unlinked-from-pull-request")
                }
            }
        }
    }

    BackgroundItem {
        id: contentItem
        height: itemStatusPill.y + itemStatusPill.height + Theme.paddingSmall
        anchors {
            left: timeLabel.left
            top: textLabel.bottom
            topMargin: Theme.paddingMedium
            right: parent.right
        }

        Label {
            id: itemLabel
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: Theme.paddingSmall
            }
            wrapMode: Text.Wrap
            font {
                pixelSize: Theme.fontSizeSmall
            }
            text: "<strong>" + item.subject.title + "</strong> #" + item.subject.number
        }

        Pill {
            id: itemStatusPill
            anchors {
                left: parent.left
                top: itemLabel.bottom
                topMargin: Theme.paddingMedium
            }
            //icon: item.subject === "OPEN" ? "/usr/share/harbour-sailhub/icons/icon-m-pull-request.svg" : "image://theme/icon-s-installed"
            text: {
                switch (item.subject.state) {
                case "OPEN":
                    //% "Open"
                    return qsTrId("id-open")
                case "MERGED":
                    //% "Merged"
                    return qsTrId("id-merged")
                case "CLOSED":
                    //% "Closed"
                    return qsTrId("id-closed")
                default:
                    //% "Not defined"
                    return qsTrId("id-not-defined")

                }
            }

            backgroundColor: {
                switch (item.subject.state) {
                case "OPEN":
                    return SailHubStyles.colorStatusOpen
                case "MERGED":
                    return SailHubStyles.colorStatusMerged
                case "CLOSED":
                    return SailHubStyles.colorStatusClosed
                default:
                    return Theme.secondaryHighlightColor
                }
            }
        }

        onClicked: {
            switch (item.subject["__typename"]) {
            case "Issue":
                pageStack.push(Qt.resolvedUrl("../pages/IssuePage.qml"),  { nodeId: item.subject.id })
                break

            case "PullRequest":
                pageStack.push(Qt.resolvedUrl("../pages/PullRequestPage.qml"),  { nodeId: item.subject.id })
                break

            default:
                break
            }
        }
    }

    Item {
        id: spacer
        anchors.top: contentItem.bottom
        width: 1
        height: Theme.paddingLarge
    }
}
