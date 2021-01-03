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
        contentHeight: contentColumn.height

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: qsTr("Issue")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    width: Theme.itemSizeSmall
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
                    font.pixelSize: Theme.fontSizeLarge
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: issue.author.login
                }
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap

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
                    color: pressed ? Theme.highlightColor : Theme.primaryColor

                    text: (issue.states & Issue.StateClosed) ? qsTr("Closed") : qsTr("Open")
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            RelatedValueItem {
                width: parent.width

                icon: "image://theme/icon-s-chat"
                label: qsTr("Comments")
                value: issue.commentCount
            }
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


