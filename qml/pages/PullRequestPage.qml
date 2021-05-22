import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools/"
import '..'

Page {
    property bool busy: false
    property string nodeId
    property PullRequest request

    id: page
    allowedOrientations: Orientation.All

    // model
    CommentsModel {
        id: commentsModel
        identifier: request.nodeId
        modelType: Comment.PullRequest
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

            var obj = component.createObject(commentsColumn, {comment: comment, parentId: request.nodeId})
        }
    }

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy 
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanSubscribe
                text: request.viewerSubscription === SubscriptionState.Subscribed ? qsTr("Unsubscribe") : qsTr("Subscribe")

                onClicked: {
                    if (request.viewerSubscription === SubscriptionState.Subscribed)
                        SailHub.api().subscribeTo(request.nodeId, SubscriptionState.Unsubscribed)
                    else
                        SailHub.api().subscribeTo(request.nodeId, SubscriptionState.Subscribed)
                }
            }
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate
                text: qsTr("Edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"), {
                                                    edit: true,
                                                    title: request.title,
                                                    body: request.body
                                                })

                    dialog.accepted.connect(function() {
                        request.title = dialog.title
                        request.body = dialog.body
                        SailHub.api().updatePullRequest(request)
                    })
                }
            }
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate && request.states & PullRequest.StateOpen
                text: qsTr("Close")

                onClicked: remorse.execute(qsTr("Closing pull request"), function() {
                    SailHub.api().closePullRequest(request.nodeId)
                })
            }
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate && request.states & PullRequest.StateClosed
                text: qsTr("Reopen")

                onClicked: remorse.execute(qsTr("Reopen pull request"), function() {
                    SailHub.api().reopenPullRequest(request.nodeId)
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

                Pill {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: request.states === PullRequest.StateMerged ? "qrc:/icons/icon-m-merged" : "qrc:/icons/icon-m-pull-request"
                    text: {
                        if (request.states === PullRequest.StateOpen) return qsTr("Open")
                        if (request.states === PullRequest.StateMerged) return qsTr("Merged")
                        if (request.states === PullRequest.StateClosed) return qsTr("Closed")
                    }

                    backgroundColor: {
                        if (request.states === PullRequest.StateOpen) return SailHubStyles.colorStatusOpen
                        if (request.states === PullRequest.StateMerged) return SailHubStyles.colorStatusMerged
                        if (request.states === PullRequest.StateClosed) return SailHubStyles.colorStatusClosed
                    }

                }

                Pill {
                    anchors.verticalCenter: parent.verticalCenter
                    text: request.baseRefName
                }

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeSmall
                    height: width
                    source: "image://theme/icon-m-forward"

                }

                Pill {
                    anchors.verticalCenter: parent.verticalCenter
                    text: request.headRefName
                }
            }

            CommentItem {
                authorAvatar: request.author.avatarUrl
                authorLogin: request.author.login
                body: request.body
                edited: request.edited
                timeSpan: request.createdAtTimeSpan
            }

            SectionHeader {
                text: qsTr("Reactions")
            }

            ReactionsItem {
                node: request
                locked: request.locked

                onClicked: {
                    if (request.locked) return
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"), {
                                                    reactions: request.viewerReactions
                                                })

                    dialog.accepted.connect(function() {
                        if (request.viewerReactions === dialog.reactions) return;

                        SailHub.api().updateReactions(
                                    request.nodeId,
                                    request.viewerReactions,
                                    dialog.reactions)

                        request.updateReactionCount(dialog.reactions)
                        request.viewerReactions = dialog.reactions
                    })
                }
            }

            SectionHeader {
                text: qsTr("Changes")
            }

            FilesChangedItem {
                width: parent.width

                additions: request.additions
                deletions: request.deletions
                files:  request.changedFiles
            }

            RelatedValueItem {
                label: qsTr("Commits")
                icon: "qrc:/icons/icon-m-commit"
                value: request.commitCount

                onClicked: {
                    if (request.commitCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("CommitsListPage.qml"), {
                                              identifier: request.nodeId,
                                              type: Commit.PullRequest
                                          })
                }
            }

            SectionHeader {
                text: qsTr("Relations")
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

                onClicked: pageStack.push(Qt.resolvedUrl("AssigneesListPage.qml"), {
                                              title: qsTr("Assignees"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              userType: User.PullRequestAssignee,
                                              repoId: request.repositoryId,
                                              permission: request.repositoryPermission
                                          })
            }

//            RelatedValueItem {
//                label: qsTr("Reviewers")
//                icon: "image://theme/icon-m-media-artists"
//                value: request.participantCount

//                onClicked: {
//                    if (request.participantCount === 0) return;

//                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
//                                              title: qsTr("Reviewers"),
//                                              description: request.repository + " #" + request.number,
//                                              identifier: request.nodeId,
//                                              userType: User.PullRequestReviewers
//                                          })
//                }
//            }

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
                enabled: !discussion.locked
                text: qsTr("Write comment")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addComment(dialog.body, commentsModel.identifier)
                    })
                }
            }

            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate
                text: request.locked ? qsTr("Unlock") : qsTr("Lock")
                onClicked: remorse.execute(request.locked ? qsTr("Unlocking") : qsTr("Locking"), function() {
                    if (request.locked) {
                        SailHub.api().unlock(request.nodeId)
                    } else {
                        SailHub.api().lock(request.nodeId)
                    }
                })
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
        onPullRequestAvailable: {
            if (request.nodeId !== page.nodeId) return

            page.request = request;
            refresh()
        }
        onPullRequestClosed: if (nodeId === request.nodeId) request.states = closed ? PullRequest.StateClosed : PullRequest.StateOpen
        onPullRequestReopened: if (nodeId === request.nodeId) request.states = reopened ? PullRequest.StateOpen : PullRequest.StateClosed
        onSubscribedTo: if (nodeId === request.nodeId) request.viewerSubscription = state
        onCommentAdded: refresh()
        onCommentDeleted: refresh()
        onLocked: if (nodeId === request.nodeId) request.locked = locked
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

    Component.onCompleted: SailHub.api().getPullRequest(page.nodeId)
}
