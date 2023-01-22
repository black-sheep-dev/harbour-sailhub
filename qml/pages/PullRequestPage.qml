import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQml.Models 2.2

import "../components/"
import "../components/menu/"
import "../delegates/"
import "../queries/"
import "../queries/pullRequest"
import "../tools/"
import "../views/"
import "../."

TimelinePage {
    property var pullRequest

    property string pullRequestBody
    property string pullRequestState
    property string pullRequestTitle

    property bool loadingContent: false

    function refreshContent() {
        loadingContent = true
        Api.request({
                        query: 'query($nodeId: ID!) {
                                node(id: $nodeId) {
                                    ... on PullRequest {
                                        id
                                        assignees {
                                            totalCount
                                        }
                                        author {
                                            avatarUrl
                                            login
                                        }
                                        body
                                        closingIssuesReferences {
                                            totalCount
                                        }
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
                                        reviewRequests {
                                            totalCount
                                        }
                                        title
                                        state
                                        updatedAt
                                        viewerCanApplySuggestion
                                        viewerCanDeleteHeadRef
                                        viewerCanDisableAutoMerge
                                        viewerCanEnableAutoMerge
                                        viewerCanReact
                                        viewerCanSubscribe
                                        viewerCanUpdate
                                        viewerDidAuthor
                                        viewerSubscription
                                    }
                                }
                            }',
                        variables: { nodeId: page.nodeId }
                    },
                    function(result, status) {
                        loadingContent = false

                        if (status !== 200) {
                            //% "Failed to load user details"
                            notify.show(qsTrId("id-failed-to-load-user-details"))
                            return
                        }

                        console.log("-----------------------------------------------------------------")
//                        console.log(result)
//                        console.log(JSON.stringify(result))
                        subscriptionMenu.subscription = result.node.viewerSubscription
                        pullRequestState = result.node.state
                        pullRequestBody = result.node.body
                        pullRequestTitle = result.node.title
                        pullRequest = result.node
                    })
    }

    id: page
    allowedOrientations: Orientation.All
    showBusyIndicator: false
    itemsPath: ["node", "timelineItems", "nodes"]
    itemsQuery: '
query(
    $nodeId: ID!,
    $itemCount: Int = 20,
    $itemCursor: String = null) {
    node(id: $nodeId) {
        ... on PullRequest {
            id
            timelineItems(
                first: $itemCount
                after: $itemCursor
            ) {
                nodes {
                    __typename
                    ... on AddedToProjectEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on AssignedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        assignee {
                            ... on User {
                                avatarUrl
                                login
                            }
                        }
                    }
                    ... on AutoMergeDisabledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        reason
                    }
                    ... on AutoMergeEnabledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on AutoRebaseEnabledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on AutoSquashEnabledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on AutomaticBaseChangeFailedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on AutomaticBaseChangeSucceededEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on BaseRefChangedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        currentRefName
                        previousRefName
                    }
                    ... on BaseRefDeletedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        baseRefName
                        createdAt
                    }
                    ... on BaseRefForcePushedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on ClosedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        stateReason
                    }
                    ... on CommentDeletedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        deletedCommentAuthor {
                            avatarUrl
                            login
                        }
                    }
                    ... on ConnectedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        subject {
                            __typename
                            ... on Issue {
                                id
                                title
                                number
                                state
                            }
                            ... on PullRequest {
                                id
                                title
                                number
                                state
                            }
                        }
                    }
                    ... on ConvertedNoteToIssueEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on ConvertedToDiscussionEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        discussion {
                            title
                            number
                        }
                    }
                    ... on CrossReferencedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        source {
                            __typename
                            ... on Issue {
                                id
                                number
                                state
                                title
                            }
                            ... on PullRequest {
                                id
                                number
                                state
                                title
                            }
                        }
                    }
                    ... on DemilestonedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        milestoneTitle
                    }
                    ... on DeployedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on DeploymentEnvironmentChangedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on DisconnectedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        subject {
                            __typename
                            ... on Issue {
                                id
                                title
                                number
                                state
                            }
                            ... on PullRequest {
                                id
                                title
                                number
                                state
                            }
                        }
                    }
                    ... on HeadRefDeletedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        headRefName
                    }
                    ... on HeadRefForcePushedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        afterCommit {
                            abbreviatedOid
                        }
                        beforeCommit {
                            abbreviatedOid
                        }
                        createdAt
                        ref {
                            name
                            prefix
                        }
                    }
                    ... on HeadRefRestoredEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on IssueComment {
                        id
                        author {
                            avatarUrl
                            login
                        }
                        body
                        bodyText
                        createdAt
                        lastEditedAt
                        reactionGroups {
                            ... on ReactionGroup {
                                content
                                users {
                                    totalCount
                                }
                                viewerHasReacted
                            }
                        }
                        viewerCanDelete
                        viewerCanReact
                        viewerCanUpdate
                        viewerDidAuthor
                    }
                    ... on LabeledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        label {
                            id
                            color
                            name
                        }
                    }
                    ... on LockedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        lockReason
                    }
                    ... on MarkedAsDuplicateEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        canonical {
                            __typename
                            ... on Issue {
                                id
                            }
                            ... on PullRequest {
                                id
                            }
                        }
                    }
                    ... on MentionedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on MergedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        commit {
                            id
                            abbreviatedOid
                        }
                        mergeRefName
                    }

                    ... on MilestonedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        milestoneTitle
                    }
                    ... on MovedColumnsInProjectEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on PinnedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on PullRequestCommit {
                        commit {
                            id
                            abbreviatedOid
                            author {
                                user {
                                    avatarUrl
                                    login
                                }
                            }
                            authoredDate
                            messageHeadline
                            pushedDate
                            signature {
                                isValid
                                state
                            }
                        }
                    }
                    ... on PullRequestCommitCommentThread {
                        path
                    }
                    ... on PullRequestReview {
                        author {
                            avatarUrl
                            login
                        }
                        body
                        createdAt
                        reactionGroups {
                            ... on ReactionGroup {
                                content
                                users {
                                    totalCount
                                }
                                viewerHasReacted
                            }
                        }
                        state
                        submittedAt
                        viewerCanDelete
                        viewerCanReact
                        viewerCanUpdate
                        viewerCannotUpdateReasons
                        viewerDidAuthor
                    }
                    ... on PullRequestReviewThread {
                        line
                    }
                    ... on PullRequestRevisionMarker {
                        lastSeenCommit {
                            id
                        }
                        createdAt
                    }
                    ... on ReadyForReviewEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on ReferencedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on RemovedFromProjectEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on RenamedTitleEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        currentTitle
                        previousTitle
                    }
                    ... on ReopenedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        stateReason
                    }
                    ... on ReviewDismissedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        dismissalMessage
                    }
                    ... on ReviewRequestRemovedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        requestedReviewer {
                            ... on User {
                                id
                                avatarUrl
                                login
                            }
                        }
                    }
                    ... on ReviewRequestedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        requestedReviewer {
                            ... on User {
                                id
                                avatarUrl
                                login
                            }
                        }
                    }
                    ... on SubscribedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on TransferredEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        fromRepository {
                            id
                            name
                        }
                    }
                    ... on UnassignedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        assignee {
                            ... on User {
                                avatarUrl
                                login
                            }
                        }
                    }
                    ... on UnlabeledEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        label {
                            id
                            color
                            name
                        }
                    }
                    ... on UnlockedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on UnmarkedAsDuplicateEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        canonical {
                            __typename
                            ... on Issue {
                                id
                            }
                            ... on PullRequest {
                                id
                            }
                        }
                    }
                    ... on UnpinnedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on UnsubscribedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                    }
                    ... on UserBlockedEvent {
                        actor {
                            avatarUrl
                            login
                        }
                        createdAt
                        blockDuration
                        subject {
                            avatarUrl
                            login
                        }
                    }
                }
                totalCount
                pageInfo {
                    hasNextPage
                    endCursor
                }
            }
        }
    }
}'


    // Issue mutations
    ClosePullRequestMutation {
        id: closePullRequestMutation
        nodeId: page.nodeId
        onResultChanged: {
            pullRequestState = result.closePullRequest.pullRequest.state
            refresh()
        }
    }

    ReopenPullRequestMutation {
        id: reopenPullRequestMutation
        nodeId: page.nodeId
        onResultChanged: {
            pullRequestState = result.reopenPullRequest.pullRequest.state
            refresh()
        }
    }

    UpdatePullRequestMutation {
        id: updatePullRequestMutation
        nodeId: page.nodeId

        onResultChanged: {
            pullRequestBody = result.updatePullRequest.pullRequest.body
            pullRequestTitle = result.updatePullRequest.title
            refresh()
        }
    }

    SilicaFlickable {
        PullDownMenu {
            busy: loading

            SubscriptionMenuItem {
                id: subscriptionMenu
                nodeId: pullRequest.id
                viewerCanSubscribe: pullRequest.viewerCanSubscribe
            }

            MenuItem {
                visible: pullRequest.viewerCanUpdate
                //% "Edit"
                text: qsTrId("id-edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditPullRequestDialog.qml"), {
                                                    edit: true,
                                                    title: pullRequest.title,
                                                    body: pullRequest.body
                                                })

                    dialog.accepted.connect(function() {
                        updatePullRequestMutation.title = dialog.title
                        updatePullRequestMutation.body = dialog.body
                        updatePullRequestMutation.execute()
                    })
                }
            }

            MenuItem {
                visible: pullRequest.viewerCanUpdate && pullRequestState === "OPEN"
                //% "Close"
                text: qsTrId("id-close")

                //% "Close pull request"
                onClicked: remorse.execute(qsTrId("id-close-pull-request"), function() { closePullRequestMutation.execute() })
            }
            MenuItem {
                visible: pullRequest.viewerCanUpdate && pullRequestState === "CLOSED"
                //% "Reopen"
                text: qsTrId("id-reopen")

                //% "Reopen pull request"
                onClicked: remorse.execute(qsTrId("id-reopen-pull-request"), function() { reopenPullRequestMutation.execute() })
            }
        }

        id: flickable
        anchors.fill: parent
        contentHeight: headerColumn.height + timelineColumn.height

        onAtYEndChanged: if (atYEnd) loadMore()

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: loadingContent ? 0.1 : 1.0
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
                    source: pullRequest.author.avatarUrl
                    anchors.verticalCenter: parent.verticalCenter
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: pullRequest.repository.nameWithOwner + " #" + pullRequest.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: pullRequestTitle
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Pill {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: pullRequestState === "OPEN" ? "/usr/share/harbour-sailhub/icons/icon-m-pull-request.svg" : "image://theme/icon-s-installed"
                    text: {
                        switch (pullRequestState) {
                        case "OPEN":
                            //% "Open"
                            return qsTrId("id-open")
                        case "MERGED":
                            //% "Merged"
                            return qsTrId("id-merged")
                        case "CLOSED":
                            //% "Closed"
                            return qsTrId("id-closed")
                        default:
                            //% "Not defined"
                            return qsTrId("id-not-defined")

                        }
                    }

                    backgroundColor: {
                        switch (pullRequestState) {
                        case "OPEN":
                            return SailHubStyles.colorStatusOpen
                        case "MERGED":
                            return SailHubStyles.colorStatusMerged
                        case "CLOSED":
                            return SailHubStyles.colorStatusClosed
                        default:
                            return Theme.secondaryHighlightColor
                        }
                    }
                }
            }

            CommentItem {
                authorAvatar: pullRequest.author.avatarUrl
                authorLogin: pullRequest.author.login
                //% "No description provided."
                body: pullRequestBody.length > 0 ? pullRequestBody : qsTrId("id-no-description-provided")
                edited: pullRequest.edited
                timeSpan: StringHelper.timespan(pullRequest.createdAt)
            }

            SectionHeader {
                //% "Reactions"
                text: qsTrId("id-reactions")
            }

            ReactionsInteractiveItem {
                enabled: pullRequest.viewerCanReact
                nodeId: pullRequest.id
                reactionGroups: pullRequest.reactionGroups
            }

            SectionHeader {
                //% "Relations"
                text: qsTrId("id-relations")
            }

            RelatedValueItem {
                //% "Reviewers"
                label: qsTrId("id-reviewers")
                icon: "image://theme/icon-m-media-artists"
                value: pullRequest.reviewRequests.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Reviewers"
                                              title: qsTrId("id-reviewers"),
                                              description: pullRequest.repository.nameWithOwner + " #" + pullRequest.number,
                                              itemsQueryType: "PULL_REQUEST_REVIEWERS"
                                          })
            }

            RelatedValueItem {
                //% "Assignees"
                label: qsTrId("id-assignees")
                icon: "image://theme/icon-m-media-artists"
                value: pullRequest.assignees.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Assignees"
                                              title: qsTrId("id-assignees"),
                                              description: pullRequest.repository.nameWithOwner + " #" + pullRequest.number,
                                              itemsQueryType: "PULL_REQUEST_ASSIGNEES"
                                          })
            }

            RelatedValueItem {
                //% "Labels"
                label: qsTrId("id-labels")
                icon: "image://theme/icon-m-link"
                value: pullRequest.labels.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              //% "Labels"
                                              title: qsTrId("id-labels"),
                                              description: pullRequest.repository.nameWithOwner + " #" + pullRequest.number,
                                              nodeId: pullRequest.id,
                                              nodeType: "PullRequest",
                                              repoId: pullRequest.repository.id,
                                              viewerCanAssign: pullRequest.viewerCanUpdate
                                          })
            }

            RelatedValueItem {
                //% "Closing issues"
                label: qsTrId("id-closing-issues")
                icon: "/usr/share/harbour-sailhub/icons/icon-m-issue.svg"
                value: pullRequest.closingIssuesReferences.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                              //% "Closing issues"
                                              title: qsTrId("id-closing-issues"),
                                              description: pullRequest.repository.nameWithOwner + " #" + pullRequest.number,
                                              nodeId: pullRequest.id,
                                              nodeType: "PullRequest",
                                              itemsQueryType: "CLOSING_ISSUES_REFERENCES"
                                          })
            }

            RelatedValueItem {
                //% "Participants"
                label: qsTrId("id-participants")
                icon: "image://theme/icon-m-media-artists"
                value: pullRequest.participants.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Participants"
                                              title: qsTrId("id-participants"),
                                              description: pullRequest.repository.nameWithOwner + " #" + pullRequest.number,
                                              itemsQueryType: "PULL_REQUEST_PARTICIPANTS"
                                          })
            }

            SectionHeader {
                //% "Timeline"
                text: qsTrId("id-timeline")
            }
        }

        Rectangle {
            id: timelineSeparator
            anchors.top: headerColumn.bottom
            width: parent.width
            height: SailHubStyles.thicknessTimeline
            color: SailHubStyles.colorTimeline
            opacity: SailHubStyles.opacityTimeline
        }

        Column {
            id: timelineColumn
            anchors.top: timelineSeparator.bottom
            width: parent.width

            Repeater {
                model: itemsModel
                delegate: Loader {
                    property var item: itemsModel.get(index)
                    property var parentId: pullRequest.id
                    property var type: __typename

                    width: parent.width
                    height: childrenRect.height
                    sourceComponent: {
                        switch(__typename) {  
                        case "IssueComment":
                            return timelineCommentItem

                        case "PullRequestCommit":
                            return timelinePullRequestCommitItem

                        case "LabeledEvent":
                        case "UnlabeledEvent":
                            return timelineLabelItem

                        case "AssignedEvent":
                        case "UnassignedEvent":
                            return timelineAssignedItem

                        case "CrossReferencedEvent":
                            return timelineCrossReferencedItem

                        case "RenamedTitleEvent":
                            return timelineChangedTitleItem

                        case "ConnectedEvent":
                        case "DisconnectedEvent":
                            return timelineConnectedItem

                        case "ReviewRequestedEvent":
                        case "ReviewRequestRemovedEvent":
                            return timelineRequestedReviewItem

                        case "MentionEvent":
                        case "SubscribedEvent":
                        case "UnsubscribedEvent":
                            return

                        default:
                            return timelineStandardItem
                        }
                    }
                }
            }
        }

        Component {
            id: timelineAssignedItem
            TimelineAssignedItem { }
        }

        Component {
            id: timelineChangedTitleItem
            TimelineChangedTitleItem { }
        }

        Component {
            id: timelineConnectedItem
            TimelineConnectedItem { }
        }

        Component {
            id: timelineCommentItem
            TimelineCommentItem { }
        }

        Component {
            id: timelineCrossReferencedItem
            TimelineCrossReferencedItem { }
        }

        Component {
            id: timelineStandardItem
            TimelineStandardItem { }
        }

        Component {
            id: timelineLabelItem
            TimelineLabelItem { }
        }

        Component {
            id: timelinePullRequestCommitItem
            TimelinePullRequestCommitItem { }
        }

        Component {
            id: timelineRequestedReviewItem
            TimelineRequestedReviewItem { }
        }

        VerticalScrollDecorator {}

        PushUpMenu {
            busy: loading

            MenuItem {
                //% "Write comment"
                text: qsTrId("id-write-comment")
                onClicked: addComment()
            }

            LockableMenuItem {
                nodeId: pullRequest.id
                locked: pullRequest.locked
                //% "Lock conversation"
                lockText: qsTrId("id-lock-conversation")
                //% "Unlock conversation"
                unlockText: qsTrId("id-unlock-conversation")
            }
        }
    }

    Component.onCompleted: {
        refreshContent()
        refresh()
    }
}
