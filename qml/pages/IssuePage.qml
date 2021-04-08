import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"

Page {
    property bool busy: false
    property string nodeId
    property Issue issue

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getIssue(page.nodeId)
                }
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingMedium

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: qsTr("Issue")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                height: Theme.itemSizeSmall
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    width: parent.height / 2
                    height: width
                    source: issue.author.avatarUrl
                    anchors.verticalCenter: parent.verticalCenter

                    fallbackItemVisible: false

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: issue.repository + " #" + issue.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.paddingLarge
                color: Theme.highlightColor

                text: issue.title   
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Icon {
                    id: closedIcon
                    source: (issue.states & Issue.StateClosed) ? "image://theme/icon-s-installed?00ff00" : "image://theme/icon-s-high-importance?#ff0000"
                }

                Label {
                    width: parent.width - closedIcon.width - parent.spacing
                    anchors.verticalCenter: closedIcon.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor

                    text: (issue.states & Issue.StateClosed) ? qsTr("Closed") : qsTr("Open")
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            RelatedValueItem {
                label: qsTr("Comments")
                value: issue.commentCount

                onClicked: pageStack.push(Qt.resolvedUrl("CommentsListPage.qml"), {
                                              description: issue.repository + " #" + issue.number,
                                              identifier: issue.nodeId,
                                              type: Comment.Issue
                                          })
            }
        }

    Connections {
        target: SailHub.api()
        onIssueAvailable: {
            if (issue.nodeId !== page.nodeId) return

            page.issue = issue;
            page.busy = false;
        }
    }

    Component.onCompleted: SailHub.api().getIssue(page.nodeId)
}


