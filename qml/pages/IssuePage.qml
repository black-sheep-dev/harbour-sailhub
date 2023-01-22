import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQml.Models 2.2

import "../components/"
import "../components/menu/"
import "../delegates/"
import "../queries/"
import "../queries/issue"
import "../tools/"
import "../views/"
import "../."

TimelinePage {
    property var issue

    property string issueBody
    property string issueState
    property string issueStateReason
    property string issueTitle

    function refreshContent() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!) {
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
                            }',
                        variables: { nodeId: page.nodeId }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to load user details"
                            notify.show(qsTrId("id-failed-to-load-user-details"))
                            return
                        }

                        console.log("-----------------------------------------------------------------")
//                        console.log(result)
//                        console.log(JSON.stringify(result))
                        subscriptionMenu.subscription = result.node.viewerSubscription
                        issueState = result.node.state
                        if (result.node.stateReason !== null) issueStateReason = result.node.stateReason
                        issueBody = result.node.body
                        issueTitle = result.node.title

                        issue = result.node
                    })
    }

    id: page
    allowedOrientations: Orientation.All

    itemsPath: ["node", "timelineItems", "nodes"]

    itemsQuery: '
query(
    $nodeId: ID!,
    $itemCount: Int = 20,
    $itemCursor: String = null) {
    node(id: $nodeId) {
        ... on Issue {
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
    CloseIssueMutation {
        id: closeIssueMutation
        nodeId: page.nodeId
        onResultChanged: {
            issueState = result.issue.state
            issueStateReason = result.issue.stateReason
            refresh()
        }
    }

    DeleteIssueMutation {
        id: deleteIssueMutation
        nodeId: page.nodeId
        onResultChanged: pageStack.navigateBack()
    }

    ReopenIssueMutation {
        id: reopenIssueMutation
        nodeId: page.nodeId
        onResultChanged: {
            issueState = result.issue.state
            issueStateReason = result.issue.stateReason
            refresh()
        }
    }

    UpdateIssueMutation {
        id: updateIssueMutation
        nodeId: page.nodeId

        onResultChanged: {
            issueBody = result.issue.body
            issueTitle = result.issue.title
        }
    }

    SilicaFlickable {
        PullDownMenu {
            busy: loading

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
                onClicked: remorse.execute(qsTrId("id-deleting-issue"), function() { deleteIssueMutation.execute() })
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
                        updateIssueMutation.execute()
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
                        closeIssueMutation.execute()
                    })
                }
            }
            MenuItem {
                visible: issue.viewerCanUpdate && issueState === "CLOSED"
                //% "Reopen"
                text: qsTrId("id-reopen")

                //% "Reopen issue"
                onClicked: remorse.execute(qsTrId("id-reopen-issue"), function() { reopenIssueMutation.execute() })
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
                    icon: issueState === "OPEN" ? "/usr/share/harbour-sailhub/icons/icon-m-issue.svg" : "image://theme/icon-s-installed"
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
                            //% "Not planned"
                            return qsTrId("id-not-planned")

                        case "REOPENED":
                            //% "Reopened"
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

            ReactionsInteractiveItem {
                enabled: issue.viewerCanReact
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

                onClicked: pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
                                              //% "Labels"
                                              title: qsTrId("id-labels"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              nodeId: issue.id,
                                              nodeType: "Issue",
                                              repoId: issue.repository.id,
                                              viewerCanAssign: issue.viewerCanUpdate
                                          })
            }

            RelatedValueItem {
                //% "Assignees"
                label: qsTrId("id-assignees")
                icon: "image://theme/icon-m-media-artists"
                value: issue.assignees.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Assignees"
                                              title: qsTrId("id-assignees"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              itemsQueryType: "ISSUE_ASSIGNEES"
                                          })
            }

            RelatedValueItem {
                //% "Participants"
                label: qsTrId("id-participants")
                icon: "image://theme/icon-m-media-artists"
                value: issue.participants.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Participants"
                                              title: qsTrId("id-participants"),
                                              description: issue.repository.nameWithOwner + " #" + issue.number,
                                              itemsQueryType: "ISSUE_PARTICIPANTS"
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
                    property var parentId: issue.id
                    property var type: __typename

                    width: parent.width
                    height: childrenRect.height
                    sourceComponent: {
                        switch(__typename) {
                        case "IssueComment":
                            return timelineCommentItem

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

        VerticalScrollDecorator {}

        PushUpMenu {
            busy: loading

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
        }
    }

    Component.onCompleted: {
        refreshContent()
        refresh()
    }
}
