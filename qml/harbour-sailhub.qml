import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import Nemo.Notifications 1.0
import Nemo.KeepAlive 1.2

import "."
import "models"
import "pages"
import "objects"

ApplicationWindow {
    ConfigurationGroup {
        id: settings
        path: "/apps/harbour-sailhub/app"
        synchronous: true

        property string accessToken
        property bool apiDebug: false
        property bool notify: true
        property int paginationCount: 20
        property string notifiedMessages: "[]"

        onAccessTokenChanged: Api.accessToken = accessToken
        onApiDebugChanged: Api.debug = apiDebug

        Component.onCompleted: {
            Api.accessToken = accessToken
            Api.debug = apiDebug
            notificationsModel.notifiedMessages = JSON.parse(notifiedMessages)
        }
    }

    BackgroundJob {
        enabled: settings.notify
        frequency: BackgroundJob.TwoAndHalfMinutes

        onTriggered: {
            notificationsModel.refresh()
            finished()
        }
    }

    Notification {
        function show(message, icn) {
            replacesId = 0
            previewSummary = ""
            previewBody = message
            icon = icn || ""
            publish()
        }
        function showNotification(data) {
            const sum
            switch (data.reason) {
            case "assign":
                if (data.subject.type === "Issue") {
                    //% "Your where assigned to an issue"
                    sum = qsTrId("id-notification-summary-assign-issue")
                } else if (data.subject.type === "PullRequest") {
                    //% "Your where assigned to a pull request"
                    sum = qsTrId("id-notification-summary-assign-pullrequest")
                }
                break

            case "author":
                //% "You created the thread"
                sum = qsTrId("id-notification-summary-author-thread")
                break

            case "comment":
                //% "You commented on the thread"
                sum = qsTrId("id-notification-summary-commented-thread")
                break

            case "ci_activity":
                //% "A GitHub Actions workflow run that you triggered was completed"
                sum = qsTrId("id-notification-summary-ci-activity")
                break

            case "invitation":
                //% "You accepted an invitation to contribute to the repository"
                sum = qsTrId("id-notification-summary-invitation")
                break

            case "manual":
                if (data.subject.type === "Issue") {
                    //% "You subscribed to the thread via an issue"
                    sum = qsTrId("id-notification-summary-manual-issue")
                } else if (data.subject.type === "PullRequest") {
                    //% "You subscribed to the thread via a pull request"
                    sum = qsTrId("id-notification-summary-manual-pullrequest")
                }
                break

            case "mention":
                //% "You were specifically @mentioned"
                sum = qsTrId("id-notification-summary-mention")
                break

            case "review_requested":
                //% "You, or a team you're a member of, were requested to review a pull request"
                sum = qsTrId("id-notification-summary-review-request")
                break

            case "security_alert":
                //% "GitHub discovered a security vulnerability in your repository"
                sum = qsTrId("id-notification-summary-security-alert")
                break

            case "state_changed":
                //% "You changed the thread state"
                sum = qsTrId("id-notification-summary-state-changed")
                break

            case "subscribed":
                //% "A repository you are watching has new activity"
                sum = qsTrId("id-notification-summary-subscribed")
                break

            case "team_mention":
                //% "Your team was mentioned"
                sum = qsTrId("id-notification-summary-team-mention")
                break

            default:
                //% "An unkown event happend"
                sum = qsTrId("id-notification-summary-unknown")
                break

            }

            replacesId = data.id
            //% "SailHub"
            appName = qsTrId("id-app-name")
            appIcon = "image://theme/harbour-sailhub"
            summary = sum
            body = data.subject.title + " #" + data.subject.url.substring(data.subject.url.lastIndexOf("/") + 1)
            previewSummary = sum
            previewBody = data.subject.title + " #" + data.subject.url.substring(data.subject.url.lastIndexOf("/") + 1)
            publish()
        }

        id: notification
        appName: "SailHub"
        expireTimeout: 3000
    }

    // Viewer Profile
    ViewerProfile { id: viewerProfile }

    // Notifications Model
    NotificationsModel {
        id: notificationsModel
        onNotifiedMessagesChanged: settings.notifiedMessages = JSON.stringify(notifiedMessages)
        Component.onCompleted: refresh()
    }

    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    Component.onCompleted: {
        Api.debug = true
        if (settings.accessToken.length > 0) {
            pageStack.push(Qt.resolvedUrl("pages/OverviewPage.qml"))
        } else {
            pageStack.push(Qt.resolvedUrl("pages/wizard/WizardIntroPage.qml"))
        }
    }
}
