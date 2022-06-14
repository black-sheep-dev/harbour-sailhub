import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../tools"
import '..'

Page {
    property bool busy: false
    property string nodeId
    property string selectedBranch: query.result.defaultBranchRef.name

    id: page
    allowedOrientations: Orientation.All

    QueryObject {
        id: query
        query: '
query($nodeId: ID!) {
    node(id: $nodeId) {
        ... on Repository {
            id
            defaultBranchRef {
                id
                name
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
            isFork
            issues(states: [OPEN]) {
                totalCount
            }
            licenseInfo {
                spdxId
                url
            }
            lockReason
            name
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
}'
        variables: {
            "nodeId": page.nodeId
        }
    }


    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: !query.ready

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
            busy: page.busy
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: SailHub.api().request(query)
            }

            MenuItem {
                visible: query.result.viewerCanSubscribe
                text: {
                    switch (query.result.viewerSubscription) {
                    case SubscriptionState.Ignored:
                    case SubscriptionState.Unsubscribed:
                        //% "Watch"
                        return qsTrId("id-watch")

                    default:
                        //% "Unwatch"
                        return qsTrId("id-unwatch")
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectSubscriptionDialog.qml"), {
                                                    subscription: query.result.viewerSubscription
                                                })

                    dialog.accepted.connect(function() {
                        console.log(dialog.subscription)
                        SailHub.api().subscribeTo(query.result.id, dialog.subscription)
                    })
                }
            }
            StarMenuItem {
                starred: query.result.viewerHasStarred
                nodeId: query.result.id
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: query.result.name
                description: query.result.owner.login
            }

            // owner
            BackgroundItem {
                width: parent.width

                Row {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: Theme.itemSizeSmall

                    anchors.verticalCenter: parent.verticalCenter
                    spacing: Theme.paddingMedium

                    CircleImage {
                        id: avatarIcon
                        width: parent.height / 2
                        height: width
                        anchors.verticalCenter: parent.verticalCenter

                        source: query.result.owner.avatarUrl
                        fallbackItemVisible: false

                        BusyIndicator {
                            size: BusyIndicatorSize.Medium
                            anchors.centerIn: avatarIcon
                            running: avatarIcon.status === Image.Loading
                        }
                    }

                    Label {
                        width: parent.width - avatarIcon.width
                        anchors.verticalCenter: parent.verticalCenter

                        font.pixelSize: Theme.fontSizeSmall

                        text: query.result.owner.login
                    }
                }

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              nodeId: query.result.owner.id
                                          })
            }


            // title
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
                font.bold: true
                wrapMode: Text.Wrap

                text: query.result.name
            }

            // forked
            BackgroundItem {
                visible: query.result.isFork
                width: parent.width

                Label {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    wrapMode: Text.Wrap

                    //% "Forked from %1"
                    text: qsTrId("id-forked-from").arg(query.result.parent.nameWithOwner)
                }

                onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                              nodeId: query.result.parent.id
                                          })
            }

            // flags
//            RepoFlagsItem {
//                x: Theme.horizontalPageMargin
//                width: parent.width - 2*x
//                flags: repo.flags
//                lockReason: query.result.lockReason
//            }

            // description
            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parse(query.result.description)
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // homepage
            IconLabel {
                visible: query.result.homepageUrl !== null

                icon: "image://theme/icon-m-website"
                label: query.result.homepageUrl

                onClicked: Qt.openUrlExternally(query.result.homepageUrl)
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                CounterItem {
                    width: parent.width / 3

                    title: {
                        var string = StringHelper.count(query.result.stargazerCount)
                        string += " "
                        string += query.result.stargazerCount > 1 ?
                                    //% "Stars"
                                    qsTrId("id-stars") :
                                    //% "Star"
                                    qsTrId("id-star")

                        return string;
                    }

                    icon: "image://theme/icon-m-favorite"

                    onClicked: {
                        if (query.result.stargazerCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                  //% "Stargazer"
                                                  title: qsTrId("id-stargazer"),
                                                  description: query.result.owner.login + "/" + query.result.name,
                                                  identifier: query.result.id,
                                                  userType: User.Stargazer
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 3

                    title: {
                        var string = StringHelper.count(query.result.forkCount)
                        string += " "
                        string += query.result.forkCount > 1 ?
                                    //% "Forks"
                                    qsTrId("id-forks") :
                                    //% "Fork"
                                    qsTrId("id-fork")

                        return string;
                    }
                    icon: "qrc:///icons/icon-m-fork"

                    onClicked: {
                        if (query.result.forkCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                     login: query.result.owner.login + "/" + query.result.name,
                                                                     identifier: query.result.id,
                                                                     repoType: Repo.Fork
                                                                 })
                    }
                }

                CounterItem {
                    visible: query.result.fundingLinks.length > 0
                    width: parent.width / 3

                    //% "Sponsor"
                    title: qsTrId("id-sponsor")
                    icon: "qrc:///icons/icon-m-heart"

                    onClicked: pageStack.push(Qt.resolvedUrl("FundingLinksListPage.qml"), {
                                                  identifier: query.result.id,
                                              })
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            // Related items
            RelatedValueItem {
                visible: query.result.vulnerabilityAlerts.totalCount > 0
                width: parent.width
                //% "Vulnerability Alerts"
                label: qsTrId("id-vulnerability-alerts")
                value: query.result.vulnerabilityAlerts.totalCount
                icon: "image://theme/icon-m-warning?" + Theme.errorColor
            }
            RelatedValueItem {
                visible: query.result.hasIssuesEnabled
                width: parent.width
                //% "Issues"
                label: qsTrId("id-issues")
                value: query.result.issues.totalCount
                icon: "qrc:///icons/icon-m-issue"

                onClicked: {
                    if (query.result.issues.totalCount === 0) return;
                    pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.id,
                                              type: Issue.Repo,
                                              states: IssueState.Open
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width
                //% "Pull requests"
                label: qsTrId("id-pull-requests")
                value: query.result.pullRequests.totalCount
                icon: "qrc:///icons/icon-m-pull-request"

                onClicked: {
                    if (query.result.pullRequests.totalCount === 0) return
                    pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.id,
                                              type: PullRequest.Repo,
                                              states: PullRequestState.Open
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width
                //% "Discussions"
                label: qsTrId("id-discussions")
                value: query.result.discussions.totalCount
                icon: "image://theme/icon-m-chat"

                onClicked: pageStack.push(Qt.resolvedUrl("DiscussionsListPage.qml"), {
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.id
                                          })


            }
            RelatedValueItem {
                width: parent.width
                //% "Releases"
                label: qsTrId("id-releases")
                value: query.result.releases.totalCount
                icon: "qrc:///icons/icon-m-tag"

                onClicked: {
                    if (query.result.releases.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReleasesListPage.qml"), {
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.id
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width
                //% "Watchers"
                label: qsTrId("id-watchers")
                value: query.result.watchers.totalCount
                icon: "qrc:///icons/icon-m-eye"

                onClicked: {
                    if (query.result.watchers.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              //% "Watchers"
                                              title: qsTrId("id-watchers"),
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.nodeId,
                                              userType: User.Watcher
                                          })
                }
            }   
            RelatedValueItem {
                width: parent.width
                //% "Contributors"
                label: qsTrId("id-contributors")
                value: query.result.mentionableUsers.totalCount
                icon: "image://theme/icon-m-media-artists"

                onClicked: {
                    if (query.result.mentionableUsers.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              //% "Contributors"
                                              title: qsTrId("id-contributors"),
                                              description: query.result.owner.login + "/" + query.result.name,
                                              identifier: query.result.id,
                                              userType: User.Contributor
                                          })
                }
            }

            RelatedValueItem {
                width: parent.width
                //% "License"
                label: qsTrId("id-license")
                value: query.result.licenseInfo.spdxId
                icon: "image://theme/icon-m-file-document-light"

                onClicked: pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                              branch: query.result.defaultBranch,
                                              owner: query.result.owner.login,
                                              path: "LICENSE",
                                              repo: query.result.name,
                                              repoId: query.result.id
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
                        source: "qrc:///icons/icon-m-branch"
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
                                                    branches: query.result.refs.nodes,
                                                    defaultBranch: query.result.defaultBranchRef.name
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
                                              owner: query.result.owner.login,
                                              path: "README.md",
                                              repo: query.result.name,
                                              repoId: query.result.id
                                          })
            }

            RelatedItem {
                //% "Browse code"
                title: qsTrId("id-browse-code")

                onClicked: pageStack.push(Qt.resolvedUrl("TreeListPage.qml"), {
                                              branch: selectedBranch,
                                              owner: query.result.owner.login,
                                              repoName: query.result.name,
                                              repoId: query.result.id,
                                              modelType: TreeModel.Repository
                                          })
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }
        } 
    }

    Connections {
        target: SailHub.api()
        onStarred: {
            if (nodeId !== repo.nodeId) return
            page.repo.viewerHasStarred = starred
            page.repo.stargazerCount += starred ? 1 : -1
            page.busy = false
        }
        onSubscribedTo: {
            if (nodeId !== repo.nodeId) return
            page.repo.viewerSubscription = state
            page.busy = false
        }
    }

    Component.onCompleted: { SailHub.api().request(query) }
}
