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

    BackgroundItem {
        id: textBackgroundItem
        enabled: false
        anchors {
            top: timeLabel.bottom
            topMargin: Theme.paddingMedium
            left: timeLabel.left
            right: parent.right
        }

        height: textLabel.height + 2*Theme.paddingSmall

        Label {
            id: textLabel
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            wrapMode: Text.Wrap
            font.pixelSize: Theme.fontSizeSmall
            textFormat: Text.RichText
            //% "abroved these changes"
            text: qsTrId("id-event-abroved-these-changes")
        }

        onClicked: {
            switch (type) {

            default:
                //% "Not implemented yet"
                notification.show(qsTrId("id-not-implemented-yet"))
                break
            }
        }
    }
    Item {
        id: spacer
        anchors.top: textBackgroundItem.bottom
        width: 1
        height: Theme.paddingLarge
    }

    Component.onCompleted: {
        switch (type) {
        case "ClosedEvent":
            if (item.stateReason === "COMPLETED") {
                iconRect.color = SailHubStyles.colorEventClosed
                iconImage.source = "image://theme/icon-m-accept"
                //% "closed this issue"
                textLabel.text = qsTrId("id-event-closed-this-issue")
            } else if (item.stateReason === "NOT_PLANNED") {
                iconImage.source = "image://theme/icon-m-dismiss"
                //% "closed this issue as not planned"
                textLabel.text = qsTrId("id-event-closed-this-issue-not-planned")
            } else {
                iconImage.source = "image://theme/icon-m-accept"
                //% "closed this issue"
                textLabel.text = qsTrId("id-event-closed-this-issue")
            }
            break

        case "HeadRefForcePushedEvent":
            iconImage.source = "image://theme/icon-m-capslock"
            //: force-pushed the BRANCH from COMMIT_ID to COMMIT_ID
            //% "force-pushed the <italic>%1</italic> from <strong>%2</strong> to <strong>%3</strong>"
            textLabel.text = qsTrId("id-event-head-ref-forced-push").arg(item.ref.name).arg(item.beforeCommit.abbreviatedOid).arg(item.afterCommit.abbreviatedOid)
            break

        case "HeadRefDeletedEvent":
            iconImage.source = "/usr/share/harbour-sailhub/icons/icon-m-branch.svg"
            //% "deleted the %1 branch"
            textLabel.text = qsTrId("id-event-head-ref-deleted").arg(item.headRefName)
            break

        case "LockedEvent":
            iconImage.source = "image://theme/icon-m-device-lock"
            //% "locked and limited conversation to collaborators"
            textLabel.text = qsTrId("id-event-locked-conversation")
            break

        case "MergedEvent":
            iconImage.source = "image://theme/icon-m-mark-unread"
            //: merged commit COMMIT_ID into BRANCH
            //% "merged commit %1 into %2"
            textLabel.text = qsTrId("id-event-merged-commit-into").arg(item.commit.abbreviatedOid, item.mergeRefName)
            break

        case "PinnedEvent":
            iconImage.source = "/usr/share/harbour-sailhub/icons/icon-m-merged.svg"
            //% "pinned this one"
            textLabel.text = qsTrId("id-event-pinned")
            break

        case "PullRequestReview":
            userItem.avatarUrl = item.author.avatarUrl
            userItem.login = item.author.login
            iconRect.color = SailHubStyles.colorSuccess
            iconImage.source = "image://theme/icon-m-accept"
            //% "abroved these changes"
            textLabel.text = qsTrId("id-event-abroved-these-changes")
            break

        case "ReopenedEvent":
            iconRect.color = SailHubStyles.colorEventReopened
            iconImage.source = "image://theme/icon-m-sync"
            //% "reopened this one"
            textLabel.text = qsTrId("id-event-reopened-this-issue")
            break

        case "UnlockedEvent":
            iconImage.source = "image://theme/icon-m-keys"
            //% "unlocked this conversation"
            textLabel.text = qsTrId("id-event-unlocked-conversation")
            break

        case "UnpinnedEvent":
            iconImage.source = "image://theme/icon-m-mark-unread"
            //% "unpinned this one"
            textLabel.text = qsTrId("id-event-unpinned")
            break 

        default:
            iconImage.source = "image://theme/icon-m-warning"
            //% "did something that is not implemented"
            textLabel.text = qsTrId("id-event-did-something") + ": " + type
            break
        }
    }
}
