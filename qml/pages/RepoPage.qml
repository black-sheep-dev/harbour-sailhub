import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../components/menu"
import "../queries/"
import "../tools"
import "../."

Page {
    property string nodeId
    property string selectedBranch: repo.defaultBranchRef.name
    property bool loading
    property var repo

    id: page
    allowedOrientations: Orientation.All

    function refresh() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!) {
                                    node(id: $nodeId) {
                                        ... on Repository {
                                            id
                                            defaultBranchRef {
                                                id
                                                name
                                                target {
                                                    ... on Commit {
                                                        history(first: 1) {
                                                            edges {
                                                                node {
                                                                    ... on Commit {
                                                                        abbreviatedOid
                                                                        additions
                                                                        author {
                                                                            user {
                                                                                id
                                                                                avatarUrl
                                                                                login
                                                                                name
                                                                            }
                                                                        }
                                                                        changedFiles
                                                                        committedDate
                                                                        deletions
                                                                        messageHeadline
                                                                        pushedDate
                                                                        signature {
                                                                            signer {
                                                                                avatarUrl
                                                                                name
                                                                            }
                                                                            state
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            description
                                            discussions {
                                                totalCount
                                            }
                                            forkCount
                                            fundingLinks {
                                                platform
                                            }
                                            hasIssuesEnabled
                                            homepageUrl
                                            isArchived
                                            isDisabled
                                            isEmpty
                                            isFork
                                            isInOrganization
                                            isLocked
                                            isMirror
                                            isPrivate
                                            isTemplate
                                            issues(states: [OPEN]) {
                                                totalCount
                                            }
                                            languages(first: 50) {
                                                edges {
                                                    size
                                                }
                                                nodes {
                                                    color
                                                    name
                                                }
                                                totalCount
                                                totalSize
                                            }
                                            licenseInfo {
                                                spdxId
                                                url
                                            }
                                            lockReason
                                            name
                                            nameWithOwner
                                            mentionableUsers {
                                                totalCount
                                            }
                                            owner {
                                                id
                                                login
                                                avatarUrl
                                            }
                                            parent {
                                                id
                                                nameWithOwner
                                            }
                                            pullRequests(states: [OPEN]) {
                                                totalCount
                                            }
                                            refs(first: 100, refPrefix: \"refs/heads/\") {
                                                totalCount
                                                nodes {
                                                    id
                                                    name
                                                }
                                            }
                                            releases {
                                                totalCount
                                            }
                                            stargazerCount
                                            viewerCanSubscribe
                                            viewerHasStarred
                                            viewerSubscription
                                            vulnerabilityAlerts {
                                                totalCount
                                            }
                                            watchers {
                                                totalCount
                                            }
                                        }
                                    }
                                }',
                        variables: { nodeId: page.nodeId }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to load repository data"
                            notify.show(qsTrId("id-failed-to-load-repo-data"))
                            return
                        }

                        repo = result.node
                    })
    }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: loading

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
            busy: loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }

            SubscriptionMenuItem {
                id: subscriptionMenu
                nodeId: repo.id
                viewerCanSubscribe: repo.viewerCanSubscribe
            }

            StarMenuItem {
                starred: repo.viewerHasStarred
                nodeId: page.nodeId
                onStargazerCountChanged: stargazerCountItem.count = stargazerCount
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        opacity: loading ? 0.0 : 1.0
        Behavior on opacity { FadeAnimation {} }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            opacity: busyIndicator.running ? 0 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: repo.name
                description: repo.owner.login
            }

            // owner
            BackgroundItem {
                width: parent.width

                CircleImage {
                    id: avatarIcon
                    anchors {
                        left: parent.left
                        leftMargin: Theme.horizontalPageMargin
                        verticalCenter: parent.verticalCenter
                    }
                    width: parent.height * 0.75
                    height: width
                    source: repo.owner.avatarUrl
                }

                Label {
                    anchors {
                        left: avatarIcon.right
                        leftMargin: Theme.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }

                    text: repo.owner.login
                }

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), { nodeId: repo.owner.id })
            }


            // title
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                color: Theme.highlightColor
                font {
                    pixelSize: Theme.fontSizeExtraLarge
                    bold: true
                }
                wrapMode: Text.Wrap

                text: repo.name
            }

            // forked
            BackgroundItem {
                visible: repo.isFork
                width: parent.width

                Label {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    wrapMode: Text.Wrap

                    //% "Forked from %1"
                    text: qsTrId("id-forked-from").arg(repo.parent.nameWithOwner)
                }

                onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                              nodeId: repo.parent.id
                                          })
            }

            // flags
            RepoFlagsItem {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                isArchived: repo.isArchived
                isDisabled: repo.isDisabled
                isEmpty: repo.isEmpty
                isFork: repo.isFork
                isInOrganization:  repo.isInOrganization
                isLocked: repo.isLocked
                isMirror: repo.isMirror
                isPrivate: repo.isPrivate
                isTemplate: repo.isTemplate
                lockReason: model.lockReason === undefined ? "" : model.lockReason
            }

            // description
            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                text: MarkdownParser.parse(repo.description)
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // homepage
            IconLabel {
                visible: repo.homepageUrl !== null && repo.homepageUrl.length > 0
                icon: "image://theme/icon-m-website"
                label: repo.homepageUrl
                onClicked: Qt.openUrlExternally(repo.homepageUrl)
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                CounterItem {
                    property int count: repo.stargazerCount

                    id: stargazerCountItem
                    width: parent.width / 3
                    //% "%n star(s)"
                    title: qsTrId("id-stars-count", StringHelper.count(count))
                    icon: "image://theme/icon-m-favorite"
                    onClicked: {
                        if (count === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                   nodeId: nodeId,
                                                   itemsQueryType: "STARGAZERS",
                                                   //% "Stargazer"
                                                   title: qsTrId("id-stargazer"),
                                                   description: repo.nameWithOwner
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 3
                    //% "%n fork(s)"
                    title: qsTrId("id-forks-count", StringHelper.count(repo.forkCount))
                    icon: "/usr/share/harbour-sailhub/icons/icon-m-fork.svg"
                    onClicked: {
                        if (repo.forkCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                   nodeId: nodeId,
                                                                   itemsQueryType: "FORKS",
                                                                   //% "Forks"
                                                                   title: qsTrId("id-forks"),
                                                                   description: repo.nameWithOwner
                                                                 })
                    }
                }

                CounterItem {
                    visible: repo.fundingLinks.length > 0
                    width: parent.width / 3
                    //% "Sponsor"
                    title: qsTrId("id-sponsor")
                    icon: "/usr/share/harbour-sailhub/icons/icon-m-heart.svg"
                    onClicked: pageStack.push(Qt.resolvedUrl("FundingLinksListPage.qml"), {
                                                  nodeId: nodeId,
                                                  description: repo.nameWithOwner
                                              })
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }     

            // Related items
            RelatedValueItem {
                visible: repo.vulnerabilityAlerts.totalCount > 0
                width: parent.width
                //% "Vulnerability Alerts"
                label: qsTrId("id-vulnerability-alerts")
                value: repo.vulnerabilityAlerts.totalCount
                icon: "image://theme/icon-m-warning?" + Theme.errorColor
            }
            RelatedValueItem {
                visible: repo.hasIssuesEnabled
                width: parent.width
                //% "Issues"
                label: qsTrId("id-issues")
                value: repo.issues.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-issue.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "REPOSITORY_ISSUES",
                                               canEditFilter: true,
                                               description: repo.nameWithOwner
                                          })
            }
            RelatedValueItem {
                width: parent.width
                //% "Pull requests"
                label: qsTrId("id-pull-requests")
                value: repo.pullRequests.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-pull-request.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                              nodeId: nodeId,
                                              description: repo.nameWithOwner,
                                              itemsQueryType: "REPOSITORY"
                                          })
            }
            RelatedValueItem {
                width: parent.width
                //% "Discussions"
                label: qsTrId("id-discussions")
                value: repo.discussions.totalCount
                icon: "image://theme/icon-m-chat"
                onClicked: pageStack.push(Qt.resolvedUrl("DiscussionsListPage.qml"), {
                                              nodeId: nodeId,
                                              description: repo.owner.nameWithOwner
                                          })


            }
            RelatedValueItem {
                width: parent.width
                //% "Releases"
                label: qsTrId("id-releases")
                value: repo.releases.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-tag.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("ReleasesListPage.qml"), {
                                               nodeId: nodeId,
                                               description: repo.nameWithOwner
                                          })
            }
            RelatedValueItem {
                width: parent.width
                //% "Watchers"
                label: qsTrId("id-watchers")
                value: repo.watchers.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-eye.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "WATCHERS",
                                               //% "Watchers"
                                               title: qsTrId("id-watchers"),
                                               description: repo.nameWithOwner
                                          })
            }   
            RelatedValueItem {
                width: parent.width
                //% "Contributors"
                label: qsTrId("id-contributors")
                value: repo.mentionableUsers.totalCount
                icon: "image://theme/icon-m-media-artists"
                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "MENTIONABLE_USERS",
                                               //% "Contributors"
                                               title: qsTrId("id-contributors"),
                                               description: repo.nameWithOwner
                                          })
            }

            RelatedValueItem {
                width: parent.width
                //% "License"
                label: qsTrId("id-license")
                value: repo.licenseInfo.spdxId
                icon: "image://theme/icon-m-file-document-light"
                onClicked: pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                              branch: selectedBranch,
                                              owner: repo.owner.login,
                                              path: "LICENSE",
                                              repo: repo.name,
                                              repoId: repo.id
                                          })

            }

            SectionHeader {
                //% "Content"
                text: qsTrId("id-content")
            }

            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium

                Row {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing: Theme.paddingMedium

                    Icon {
                        id: iconBranch
                        anchors.verticalCenter: parent.verticalCenter
                        width: Theme.iconSizeMedium
                        height: Theme.iconSizeMedium
                        fillMode: Image.PreserveAspectFit
                        source: "/usr/share/harbour-sailhub/icons/icon-m-branch.svg"
                    }

                    Label {
                        anchors.verticalCenter: iconBranch.verticalCenter
                        width: parent.width - iconBranch.width - editIcon.width - 2 * parent.spacing
                        text: selectedBranch
                    }

                    Icon {
                        id: editIcon
                        anchors.verticalCenter: parent.verticalCenter
                        source: "image://theme/icon-m-shuffle"
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectBranchDialog.qml"),
                                                {
                                                    selected: selectedBranch,
                                                    branches: repo.refs.nodes,
                                                    defaultBranch: repo.defaultBranchRef.name
                                                })

                    dialog.accepted.connect(function() {
                        selectedBranch = dialog.selected
                    })
                }
            }

            RelatedItem {
                //% "README"
                title: qsTrId("id-readme")

                onClicked: pageStack.push(Qt.resolvedUrl("MarkdownViewerPage.qml"), {
                                              branch: selectedBranch,
                                              owner: repo.owner.login,
                                              path: "README.md",
                                              repo: repo.name,
                                              repoId: repo.id
                                          })
            }

            RelatedItem {
                //% "Browse code"
                title: qsTrId("id-browse-code")

                onClicked: pageStack.push(Qt.resolvedUrl("TreeListPage.qml"), {
                                              branch: selectedBranch,
                                              owner: repo.owner.login,
                                              repoName: repo.name,
                                              repoId: repo.id
                                          })
            }

            // Show used languages
            SectionHeader {
                //% "Languages"
                text: qsTrId("id-languages")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                height: Theme.paddingMedium

                Repeater {
                    model: repo.languages.nodes

                    Rectangle {
                        height: parent.height
                        width: Math.round((repo.languages.edges[index].size / repo.languages.totalSize) * parent.width)
                        color: modelData.color
                    }
                }
            }

            Flow {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingLarge

                Repeater {
                    model: repo.languages.nodes

                    LanguageItem {
                        name: modelData.name + " " + Math.round((repo.languages.edges[index].size / repo.languages.totalSize) * 100) + "%"
                        color: modelData.color === undefined ? "" : modelData.color
                    }
                }
            }

            // Show last commit details

            SectionHeader {
                //% "Last commit"
                text: qsTrId("id-last-commit") + " (" + repo.defaultBranchRef.name + ")"
            }

            CommitInfoItem { commit: repo.defaultBranchRef.target.history.edges[0].node }

            Item {
                width: parent.width
                height: Theme.paddingSmall
            }
        } 
    }

    Component.onCompleted: refresh()
}
