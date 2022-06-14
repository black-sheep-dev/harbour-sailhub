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
                text: request.viewerSubscription === SubscriptionState.Subscribed ?
                          //% "Unsubscribe"
                          qsTrId("id-unsubscribe") :
                          //% "Subscribe"
                          qsTrId("id-subscribe")

                onClicked: {
                    if (request.viewerSubscription === SubscriptionState.Subscribed)
                        SailHub.api().subscribeTo(request.nodeId, SubscriptionState.Unsubscribed)
                    else
                        SailHub.api().subscribeTo(request.nodeId, SubscriptionState.Subscribed)
                }
            }
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate
                //% "Edit"
                text: qsTrId("id-edit")
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
                visible: request.viewerAbilities & Viewer.CanUpdate && request.state === PullRequest.StateOpen
                //% "Close"
                text: qsTrId("id-close")

                //% "Closing pull request"
                onClicked: remorse.execute(qsTrId("id-closing-pull-request"), function() {
                    SailHub.api().closePullRequest(request.nodeId)
                })
            }
            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate && request.state === PullRequest.StateClosed
                //% "Reopen"
                text: qsTrId("id-reopen")

                //% "Reopen pull request"
                onClicked: remorse.execute(qsTrId("id-reopen-pull-request"), function() {
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
                //% "Pull request"
                title: qsTrId("id-pull-request")
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
                    icon: request.state === PullRequestState.Merged ? "qrc:/icons/icon-m-merged" : "qrc:/icons/icon-m-pull-request"
                    text: {
                        //% "Open"
                        if (request.state === PullRequestState.Open) return qsTrId("id-open")
                        //% "Merged"
                        if (request.state === PullRequestState.Merged) return qsTrId("id-merged")
                        //% "Closed"
                        if (request.state === PullRequestState.Closed) return qsTrId("id-closed")
                    }

                    backgroundColor: {
                        if (request.state === PullRequestState.Open) return SailHubStyles.colorStatusOpen
                        if (request.state === PullRequestState.Merged) return SailHubStyles.colorStatusMerged
                        if (request.state === PullRequestState.Closed) return SailHubStyles.colorStatusClosed
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
                //% "Reactions"
                text: qsTrId("id-reactions")
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
                //% "Changes"
                text: qsTrId("id-changes")
            }

            FilesChangedItem {
                width: parent.width

                additions: request.additions
                deletions: request.deletions
                files:  request.changedFiles
            }

            RelatedValueItem {
                //% "Commits"
                label: qsTrId("id-commits")
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
                //% "Relations"
                text: qsTrId("id-relations")
            }

            RelatedValueItem {
                //% "Labels"
                label: qsTrId("id-labels")
                icon: "image://theme/icon-m-link"
                value: request.labelCount

                onClicked: {
                    if (request.labelCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              //% "Labels"
                                              title: qsTrId("id-labels"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              type: LabelEntity.PullRequest
                                          })
                }
            }

            RelatedValueItem {
                //% "Assignees"
                label: qsTrId("id-assignees")
                icon: "image://theme/icon-m-media-artists"
                value: request.assigneeCount

                onClicked: pageStack.push(Qt.resolvedUrl("AssigneesListPage.qml"), {
                                              //% "Assignees"
                                              title: qsTrId("id-assignees"),
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
                //% "Participants"
                label: qsTrId("id-participants")
                icon: "image://theme/icon-m-media-artists"
                value: request.participantCount

                onClicked: {
                    if (request.participantCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              //% "Participants"
                                              title: qsTrId("id-participants"),
                                              description: request.repository + " #" + request.number,
                                              identifier: request.nodeId,
                                              userType: User.PullRequestParticipant
                                          })
                }
            }

            SectionHeader {
                //% "Comments"
                text: qsTrId("Comments")
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
                //% "Write comment"
                text: qsTrId("id-write-comment")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addComment(dialog.body, commentsModel.identifier)
                    })
                }
            }

            MenuItem {
                visible: request.viewerAbilities & Viewer.CanUpdate
                text: request.locked ?
                          //% "Unlock"
                          qsTrId("id-unlock") :
                          //% "Lock"
                          qsTrId("id-lock")
                onClicked: remorse.execute(request.locked ?
                                               //% "Unlocking"
                                               qsTrId("id-unlocking") :
                                               //% "Locking"
                                               qsTrId("id-locking"),
                                           function() {
                    if (request.locked) {
                        SailHub.api().unlock(request.nodeId)
                    } else {
                        SailHub.api().lock(request.nodeId)
                    }
                })
            }

            MenuItem {
                visible: commentsModel.hasNextPage
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", commentsModel.totalCount - commentsColumn.children.length)
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
        onPullRequestClosed: if (nodeId === request.nodeId) request.state = closed ? PullRequest.StateClosed : PullRequest.StateOpen
        onPullRequestReopened: if (nodeId === request.nodeId) request.state = reopened ? PullRequest.StateOpen : PullRequest.StateClosed
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
