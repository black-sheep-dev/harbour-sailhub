import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../delegates/"
import "../models/"

Page {
    // only to get node_id
    function getItemNodeId(url, callback) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if (myxhr.readyState !== 4) return
                if (settings.apiDebug) console.log(myxhr.responseText)

                callback(JSON.parse(myxhr.responseText).node_id, myxhr.status)
            }
        })(xhr)

        xhr.open("GET", url)
        xhr.setRequestHeader("Accept", "application/vnd.github+json")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.setRequestHeader("X-GitHub-Api-Version", "2022-11-28")
        xhr.setRequestHeader("Authorization", "token " + settings.accessToken)
        xhr.setRequestHeader("X-Github-Next-Global-ID", 1)
        xhr.send()
    }

    id: page
    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: notificationsModel.loading

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            //% "Loading data..."
            text: qsTrId("id-loading-data")
        }
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        spacing: Theme.paddingMedium

        header: PageHeader {
            //% "Notifications"
            title: qsTrId("id-notifications")
            description: viewerProfile.login
        }

        PullDownMenu {
            busy: notificationsModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: notificationsModel.refresh()
            }
            MenuItem {
                //% "Mark all as read"
                text: qsTrId("id-mark-all-as-read")
                onClicked: remorse.execute(qsTrId("id-mark-all-as-read"), function() { notificationsModel.setAsReadAll() })
            }
        }

        RemorsePopup { id: remorse }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No notifications available"
            text: qsTrId("id-no-notifications-available")
        }

        VerticalScrollDecorator {}

        model: notificationsModel

//        opacity: busyIndicator.running ? 0.0 : 1.0
//        Behavior on opacity { FadeAnimator {} }

        delegate: NotificationListDelegate {
            id: delegate

//            menu: ContextMenu {
//                MenuItem {
//                    visible: model.unread
//                    //% "Mark as read"
//                    text: qsTrId("Mark as read")
//                    onClicked: notificationsModel.setAsRead(index)
//                }
//            }

            onClicked: {
                switch (model.subject.type) {
                case "Issue":
                    getItemNodeId(model.subject.url, function(nodeId, status) {
                        if (status !== 200) return
                        pageStack.push(Qt.resolvedUrl("IssuePage.qml"), { nodeId: nodeId })
                    })
                    break

                case "PullRequest":
                    getItemNodeId(model.subject.url, function(nodeId, status) {
                        if (status !== 200) return
                        pageStack.push(Qt.resolvedUrl("PullRequestPage.qml"), { nodeId: nodeId })
                    })
                    break

                default:
                    break
                }
            }
        }
    }
}
