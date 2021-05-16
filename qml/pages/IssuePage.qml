import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property bool busy: false
    property string nodeId
    property Issue issue

    id: page
    allowedOrientations: Orientation.All

    // model
    CommentsModel {
        id: commentsModel
        identifier: issue.nodeId
        modelType: Comment.Issue
    }

    Connections {
        target: commentsModel
        onCommentsAdded: {
            page.busy = false
            updateComments(lastIndex, count)
        }
    }

    function updateComments(index, count) {
        for (var i=index; i < (index + count); i++) {
            var comment = commentsModel.commentAt(i)

            if (comment === undefined) continue

            var component = Qt.createComponent("../components/IssueCommentItem.qml")

            if (component.status !== Component.Ready)
                console.log("NOT READY")

            var obj = component.createObject(commentsColumn, {comment: comment, parentId: issue.nodeId})
        }
    }

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy

            SubscriptionMenuItem {
                visible: issue.viewerAbilities & Viewer.CanSubscribe
                subscription: issue.viewerSubscription
                nodeId: issue.nodeId
            }
            MenuItem {
                visible: issue.viewerAbilities & Viewer.CanUpdate
                text: qsTr("Edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"), {
                                                    edit: true,
                                                    title: issue.title,
                                                    body: issue.body
                                                })

                    dialog.accepted.connect(function() {
                        issue.title = dialog.title
                        issue.body = dialog.body
                        SailHub.api().updateIssue(issue)
                    })
                }
            }
            MenuItem {
                visible: issue.viewerAbilities & Viewer.CanUpdate
                text: qsTr("Delete")

                onClicked: remorse.execute(qsTr("Deleting issue"), function() {
                    SailHub.api().deleteIssue(issue.nodeId)
                })
            }
            MenuItem {
                visible: issue.viewerAbilities & Viewer.CanUpdate && issue.states & Issue.StateOpen
                text: qsTr("Close")

                onClicked: remorse.execute(qsTr("Closing issue"), function() {
                    SailHub.api().closeIssue(issue.nodeId)
                })
            }
            MenuItem {
                visible: issue.viewerAbilities & Viewer.CanUpdate && issue.states & Issue.StateClosed
                text: qsTr("Reopen")

                onClicked: remorse.execute(qsTr("Reopen issue"), function() {
                    SailHub.api().reopenIssue(issue.nodeId)
                })
            }
        }

        id: flickable
        anchors.fill: parent
        contentHeight: headerColumn.height + commentsColumn.height

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
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
                font.pixelSize: Theme.fontSizeLarge
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

            CommentItem {
                authorAvatar: issue.author.avatarUrl
                authorLogin: issue.author.login
                body: issue.body
                edited: issue.edited
                timeSpan: issue.createdAtTimeSpan
            }

            SectionHeader {
                text: qsTr("Reactions")
            }

            ReactionsItem {
                node: issue

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"), {
                                                    reactions: issue.viewerReactions
                                                })

                    dialog.accepted.connect(function() {
                        if (issue.viewerReactions === dialog.reactions) return;

                        SailHub.api().updateReactions(
                                    issue.nodeId,
                                    issue.viewerReactions,
                                    dialog.reactions)

                        issue.updateReactionCount(dialog.reactions)
                        issue.viewerReactions = dialog.reactions
                    })
                }
            }

            SectionHeader {
                text: qsTr("Relations")
            }

            RelatedValueItem {
                label: qsTr("Labels")
                icon: "image://theme/icon-m-link"
                value: issue.labelCount

                onClicked: {
                    if (issue.labelCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              title: qsTr("Labels"),
                                              description: issue.repository + " #" + issue.number,
                                              identifier: issue.nodeId,
                                              type: LabelEntity.Issue
                                          })
                }
            }

            RelatedValueItem {
                label: qsTr("Assignees")
                icon: "image://theme/icon-m-media-artists"
                value: issue.assigneeCount

                onClicked: pageStack.push(Qt.resolvedUrl("AssigneesListPage.qml"), {
                                              title: qsTr("Assignees"),
                                              description: issue.repository + " #" + issue.number,
                                              identifier: issue.nodeId,
                                              userType: User.IssueAssignee,
                                              repoId: issue.repositoryId,
                                              permission: issue.repositoryPermission
                                          })
            }

            RelatedValueItem {
                label: qsTr("Participants")
                icon: "image://theme/icon-m-media-artists"
                value: issue.participantCount

                onClicked: {
                    if (issue.participantCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Participants"),
                                              description: issue.repository + " #" + issue.number,
                                              identifier: issue.nodeId,
                                              userType: User.IssueParticipant
                                          })
                }
            }

            SectionHeader {
                text: qsTr("Comments")
            }
        }

        Column {
            id: commentsColumn
            anchors.top: headerColumn.bottom
            width: parent.width
            spacing: Theme.paddingSmall
        }

        VerticalScrollDecorator {}

        PushUpMenu {
            busy: commentsModel.loading

            MenuItem {
                text: qsTr("Write comment")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addComment(dialog.body, commentsModel.identifier)
                    })
                }
            }

            MenuItem {
                visible: commentsModel.hasNextPage
                text: qsTr("Load more (%n to go)", "", commentsModel.totalCount - commentsColumn.children.length)
                onClicked: getComments()
            }
        }
    }

    Connections {
        target: SailHub.api()
        onIssueAvailable: {
            if (issue.nodeId !== page.nodeId) return

            page.issue = issue;
            refresh()
        }
        onIssueClosed: pageStack.navigateBack()
        onIssueDeleted: pageStack.navigateBack()
        onIssueReopened: issue.setStates(Issue.StateOpen)
        onCommentAdded: refresh()
        onCommentDeleted: refresh()
    }

    function getComments() {
        page.busy = true;
        SailHub.api().getPaginationModel(commentsModel)
    }

    function refresh() {
        commentsModel.reset()
        for(var i = commentsColumn.children.length; i > 0; i--) {
            commentsColumn.children[i-1].destroy()
        }
        getComments()
    }

    Component.onCompleted: SailHub.api().getIssue(page.nodeId)
}
