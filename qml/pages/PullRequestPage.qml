import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"

Page {
    property bool busy: false
    property string nodeId
    property PullRequest request

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getPullRequest(page.nodeId)
                }
            }
//            MenuItem {
//                visible: issue.viewerCanUpdate
//                text: qsTr("Edit Pull Request")
//                onClicked: {
//                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"), {
//                                                    edit: true,
//                                                    title: issue.title,
//                                                    body: issue.body
//                                                })

//                    dialog.accepted.connect(function() {
//                        issue.title = dialog.title
//                        issue.body = dialog.body
//                        SailHub.api().updateIssue(issue)
//                    })
//                }
//            }
//            MenuItem {
//                visible: request.viewerAbilities & Viewer.CanUpdate
//                text: qsTr("Close")

//                onClicked: remorse.execute(qsTr("Closing request"), function() {
//                    SailHub.api().closeIssue(issue.nodeId)
//                })
//            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingMedium

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: qsTr("Pull Request")
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
                    source: request.author.avatarUrl
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

                    text: request.repository + " #" + request.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: request.title
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Icon {
                    id: closedIcon
                    source: (request.states & request.StateClosed) ? "image://theme/icon-s-installed?00ff00" : "image://theme/icon-s-high-importance?#ff0000"
                }

                Label {
                    width: parent.width - closedIcon.width - parent.spacing
                    anchors.verticalCenter: closedIcon.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor

                    text: (request.states & PullRequest.StateClosed) ? qsTr("Closed") : qsTr("Open")
                }
            }

            CommentItem {
                authorAvatar: request.author.avatarUrl
                authorLogin: request.author.login
                body: request.body
                edited: request.edited
                timeSpan: request.createdAtTimeSpan
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            RelatedValueItem {
                label: qsTr("Comments")
                icon: "image://theme/icon-m-chat"
                value: request.commentCount

                onClicked: pageStack.push(Qt.resolvedUrl("CommentsListPage.qml"), {
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              type: Comment.PullRequest
                                          })
            }

            RelatedValueItem {
                label: qsTr("Labels")
                icon: "image://theme/icon-m-link"
                value: request.labelCount

                onClicked: {
                    if (request.labelCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              title: qsTr("Labels"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              type: LabelEntity.PullRequest
                                          })
                }
            }

            RelatedValueItem {
                label: qsTr("Assignees")
                icon: "image://theme/icon-m-media-artists"
                value: request.assigneeCount

                onClicked: {
                    if (request.assigneeCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Assignees"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              userType: User.PullRequestAssignee
                                          })
                }
            }

            RelatedValueItem {
                label: qsTr("Participants")
                icon: "image://theme/icon-m-media-artists"
                value: request.participantCount

                onClicked: {
                    if (request.participantCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Participants"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              userType: User.PullRequestParticipant
                                          })
                }
            }
        }
    }

    Connections {
        target: SailHub.api()
        onPullRequestAvailable: {
            if (request.nodeId !== page.nodeId) return

            page.request = request;
            page.busy = false;
        }
    }

    Component.onCompleted: SailHub.api().getPullRequest(page.nodeId)
}
