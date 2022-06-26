import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../components/menu/"
import "../delegates/"
import "../queries/issue"
import "../tools"
import "../views/"
import '..'

CommentsListPage {
    property alias issue: queryIssue.result

    property string issueBody
    property string issueState
    property string issueStateReason
    property string issueTitle

    function refreshContent() {
        Api.request(queryIssue)
    }

    id: page
    allowedOrientations: Orientation.All

    nodeType: "Issue"

    QueryObject {
        id: queryIssue
        resultNodePath: "node"
        query: '
query($nodeId: ID!) {
    node(id: $nodeId) {
        ... on Issue {
            id
            assignees {
                totalCount
            }
            author {
                avatarUrl
                login
            }
            body
            comments {
                totalCount
            }
            createdAt
            labels {
                totalCount
            }
            locked
            number
            participants {
                totalCount
            }
            reactionGroups {
                ... on ReactionGroup {
                    content
                    users {
                        totalCount
                    }
                    viewerHasReacted
                }
            }
            repository {
                id
                nameWithOwner
                viewerPermission
            }
            title
            state
            stateReason
            updatedAt
            viewerCanReact
            viewerCanSubscribe
            viewerCanUpdate
            viewerDidAuthor
            viewerSubscription
        }
    }
}'
        variables: {
            "nodeId": page.nodeId
        }

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            subscriptionMenu.subscription = issue.viewerSubscription
            issueState = issue.state
            issueStateReason = issue.stateReason
            issueBody = issue.body
            issueTitle = issue.title
        }

        onErrorChanged: notification.showErrorMessage(error)
    }

    CloseIssueMutation {
        id: closeIssueMutation
        nodeId: page.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            issueState = result.issue.state
            issueStateReason = result.issue.stateReason
        }
    }

    DeleteIssueMutation {
        id: deleteIssueMutation
        nodeId: page.nodeId

        onResultChanged: if (error === QueryObject.ErrorNone) pageStack.navigateBack()
    }

    ReopenIssueMutation {
        id: reopenIssueMutation
        nodeId: page.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return
            issueState = result.issue.state
            issueStateReason = result.issue.stateReason
        }
    }

    UpdateIssueMutation {
        id: updateIssueMutation
        nodeId: page.nodeId

        onResultChanged: {
            if (error !== QueryObject.ErrorNone) return

            issueBody = result.issue.body
            issueTitle = result.issue.title
        }
    }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: !queryIssue.ready

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

    SilicaFlickable {
        PullDownMenu {
            busy: !queryIssue.ready

            SubscriptionMenuItem {
                id: subscriptionMenu
                nodeId: issue.id
                viewerCanSubscribe: issue.viewerCanSubscribe
            }

            MenuItem {
                visible: issue.viewerCanUpdate
                //% "Delete"
                text: qsTrId("id-delete")

                //% "Deleting issue"
                onClicked: remorse.execute(qsTrId("id-deleting issue"), function() { Api.request(deleteIssueMutation) })
            }

            MenuItem {
                visible: issue.viewerCanUpdate
                //% "Edit"
                text: qsTrId("id-edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"), {
                                                    edit: true,
                                                    title: issue.title,
                                                    body: issue.body
                                                })

                    dialog.accepted.connect(function() {
                        updateIssueMutation.title = dialog.title
                        updateIssueMutation.body = dialog.body
                        Api.request(updateIssueMutation)
                    })
                }
            }

            MenuItem {
                visible: issue.viewerCanUpdate && issueState === "OPEN"
                //% "Close"
                text: qsTrId("id-close")


                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/CloseIssueDialog.qml"))

                    dialog.accepted.connect(function() {
                        closeIssueMutation.stateReason = dialog.reason
                        Api.request(closeIssueMutation)
                    })
                }
            }
            MenuItem {
                visible: issue.viewerCanUpdate && issueState === "CLOSED"
                //% "Reopen"
                text: qsTrId("id-reopen")

                //% "Reopen issue"
                onClicked: remorse.execute(qsTrId("id-reopen-issue"), function() { Api.request(reopenIssueMutation) })
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
                //% "Issue"
                title: qsTrId("id-issue")
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

                    text: issue.repository.nameWithOwner + " #" + issue.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: issueTitle
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Pill {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: issueState === "OPEN" ? "qrc:/icons/icon-m-issue" : "image://theme/icon-s-installed"
                    text: {
                        //% "Open"
                        if (issueState === "OPEN") return qsTrId("id-open")
                        //% "Closed"
                        if (issueState === "CLOSED") return qsTrId("id-closed")
                    }

                    backgroundColor: {
                        if (issueState === "OPEN") return SailHubStyles.colorStatusOpen
                        if (issueState === "CLOSED") return SailHubStyles.colorStatusClosed
                    }

                }

                Pill {
                    visible: issueStateReason.length > 0
                    anchors.verticalCenter: parent.verticalCenter
                    text: {
                        switch (issueStateReason) {
                        case "COMPLETED":
                            //% "Completed"
                            return qsTrId("id-completed")

                        case "NOT_PLANNED":
                            //% "Not planned
                            return qsTrId("id-not-planned")

                        case "REOPENED":
                            //% "Reopened
                            return qsTrId("id-reopened")

                        default:
                            return ""
                        }
                    }
               }
            }

            CommentItem {
                authorAvatar: issue.author.avatarUrl
                authorLogin: issue.author.login
                body: issueBody
                edited: issue.edited
                timeSpan: StringHelper.timespan(issue.createdAt)

            }

            SectionHeader {
                //% "Reactions"
                text: qsTrId("id-reactions")
            }

               // NEED_FIX
            ReactionsItem {
                nodeId: issue.id
                reactionGroups: issue.reactionGroups
            }

            SectionHeader {
                //% "Relations"
                text: qsTrId("id-relations")
            }

            RelatedValueItem {
                //% "Labels"
                label: qsTrId("id-labels")
                icon: "image://theme/icon-m-link"
                value: issue.labels.totalCount

                onClicked: {
                    if (issue.labels.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              //% "Labels"
                                              title: qsTrId("id-labels"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              identifier: issue.id
                                          })
                }
            }

            RelatedValueItem {
                //% "Assignees"
                label: qsTrId("id-assignees")
                icon: "image://theme/icon-m-media-artists"
                value: issue.assignees.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("AssigneesListPage.qml"), {
                                              //% "Assignees"
                                              title: qsTrId("id-assignees"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              identifier: issue.id,
                                              userType: User.IssueAssignee,
                                              repoId: issue.repository.id,
                                              permission: issue.repository.viewerPermission // NEED_FIX ???
                                          })
            }

            RelatedValueItem {
                //% "Participants"
                label: qsTrId("id-participants")
                icon: "image://theme/icon-m-media-artists"
                value: issue.participants.totalCount

                onClicked: {
                    if (issue.participants.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Participants"
                                              title: qsTrId("id-participants"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              itemsQueryType: "ISSUE_PARTICIPANTS"
                                          })
                }
            }

            SectionHeader {
                //% "Comments"
                text: qsTrId("id-comments")
            }
        }

        Column {
            id: commentsColumn
            anchors.top: headerColumn.bottom
            width: parent.width
            spacing: Theme.paddingSmall

            Repeater {
                model: itemsModel

                IssueCommentItem {
                    id: commentItem
                    comment: modelData
                    parentId: issue.id

                    menu: ContextMenu {
                        MenuItem {
                            visible: comment.viewerCanDelete
                            //% "Delete"
                            text: qsTrId("id-delete")
                            //% "Deleting comment"
                            onClicked: commentItem.remorseAction(qsTrId("id-deleting-comment"), function() {
                                deleteComment(comment.id)
                            })
                        }
                        MenuItem {
                            visible: comment.viewerCanUpdate
                            //% "Edit"
                            text: qsTrId("id-edit")
                            onClicked: updateComment(comment.id, comment.bodyText)
                        }
                        MenuItem {
                            //% "Quote reply"
                            text: qsTrId("id-quote-reply")
                            onClicked: replyToComment(comment.bodyText)
                        }
                    }
                }
            }
        }

        VerticalScrollDecorator {}

        PushUpMenu {
            busy: loading || !queryIssue.ready

            MenuItem {
                //% "Write comment"
                text: qsTrId("id-write-comment")
                onClicked: addComment()
            }

            LockableMenuItem {
                nodeId: issue.id
                locked: issue.locked
                //% "Lock conversation"
                lockText: qsTrId("id-lock-conversation")
                //% "Unlock conversation"
                unlockText: qsTrId("id-unlock-conversation")
            }

            MenuItem {
                visible: hasNextPage
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", totalCount - commentsColumn.children.length)
                onClicked: loadMore()
            }
        }
    }

    Component.onCompleted: {
        refreshContent()
        refresh()
    }
}
