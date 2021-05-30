import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../tools"
import '..'

Page {
    property bool busy: false
    property bool loading: true
    property string nodeId
    property Repo repo
    property string selectedBranch: repo.defaultBranch

    id: page
    allowedOrientations: Orientation.All

    MarkdownParser { id: markdownParser }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: page.loading
    }

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                visible: repo.viewerAbilities & Viewer.CanSubscribe
                text: {
                    switch (repo.viewerSubscription) {
                    case SubscriptionState.Ignored:
                    case SubscriptionState.Unsubscribed:
                        return qsTr("Watch")

                    default:
                        return qsTr("Unwatch")
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectSubscriptionDialog.qml"), {
                                                    subscription: repo.viewerSubscription
                                                })

                    dialog.accepted.connect(function() {
                        console.log(dialog.subscription)
                        SailHub.api().subscribeTo(repo.nodeId, dialog.subscription)
                    })
                }
            }
            StarMenuItem {
                starred: repo.viewerHasStarred
                nodeId: repo.nodeId
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
                title: repo.name
                description: repo.owner.login
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

                        source: repo.owner.avatarUrl
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

                        text: repo.owner.login
                    }
                }

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), {
                                              nodeId: repo.owner.nodeId
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

                text: repo.name
            }

            // forked
            BackgroundItem {
                visible: repo.flags & Repo.IsFork
                width: parent.width

                Label {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    wrapMode: Text.Wrap

                    text: qsTr("Forked from %1").arg(repo.parentName)
                }

                onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                              nodeId: repo.parentId
                                          })
            }

            // flags
            RepoFlagsItem {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                flags: repo.flags
                lockReason: repo.lockReason
            }

            // description
            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: markdownParser.parse(repo.description)
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // homepage

            IconLabel {
                visible: repo.homepageUrl.length > 0

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
                    width: parent.width / 3

                    title: {
                        var string = StringHelper.count(repo.stargazerCount)
                        string += " "
                        string += repo.stargazerCount > 1 ? qsTr("Stars") : qsTr("Star")

                        return string;
                    }

                    icon: "image://theme/icon-m-favorite"

                    onClicked: {
                        if (repo.stargazerCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                  title: qsTr("Stargazer"),
                                                  description: repo.owner.login + "/" + repo.name,
                                                  identifier: repo.nodeId,
                                                  userType: User.Stargazer
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 3

                    title: {
                        var string = StringHelper.count(repo.forkCount)
                        string += " "
                        string += repo.forkCount > 1 ? qsTr("Forks") : qsTr("Fork")

                        return string;
                    }
                    icon: "qrc:///icons/icon-m-fork"

                    onClicked: {
                        if (repo.forkCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                     login: repo.owner.login + "/" + repo.name,
                                                                     identifier: repo.nodeId,
                                                                     repoType: Repo.Fork
                                                                 })
                    }
                }

                CounterItem {
                    visible: repo.hasFundingLinks
                    width: parent.width / 3

                    title: qsTr("Sponsor")
                    icon: "qrc:///icons/icon-m-heart"

                    onClicked: pageStack.push(Qt.resolvedUrl("FundingLinksListPage.qml"), {
                                                  identifier: repo.nodeId,
                                              })
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            // Related items
            RelatedValueItem {
                visible: repo.vulnerabilityAlertCount > 0
                width: parent.width

                label: qsTr("Vulnerability Alerts")
                value: repo.vulnerabilityAlertCount
                icon: "image://theme/icon-m-warning?" + Theme.errorColor
            }
            RelatedValueItem {
                visible: repo.features & Repo.FeatureIssues
                width: parent.width

                label: qsTr("Issues")
                value: repo.issueCount
                icon: "qrc:///icons/icon-m-issue"

                onClicked: {
                    if (repo.issueCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              type: Issue.Repo,
                                              states: IssueState.Open
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Pull Requests")
                value: repo.pullRequestCount
                icon: "qrc:///icons/icon-m-pull-request"

                onClicked: {
                    pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              type: PullRequest.Repo,
                                              states: PullRequestState.Open
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Discussions")
                value: repo.discussionCount
                icon: "image://theme/icon-m-chat"

                onClicked: pageStack.push(Qt.resolvedUrl("DiscussionsListPage.qml"), {
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId
                                          })


            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Releases")
                value: repo.releaseCount
                icon: "qrc:///icons/icon-m-tag"

                onClicked: {
                    if (repo.releaseCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReleasesListPage.qml"), {
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId
                                          })
                }
            }
//            RelatedValueItem {
//                visible: repo.viewerAbilities & Viewer.CanAdminister
//                label: qsTr("Labels")
//                icon: "image://theme/icon-m-link"
//                value: repo.labelCount

//                onClicked: {
//                    if (repo.labelCount === 0) return;

//                    pageStack.push(Qt.resolvedUrl("LabelsListPage.qml"), {
//                                              title: qsTr("Labels"),
//                                              description: repo.owner.login + "/" + repo.name,
//                                              identifier: repo.nodeId,
//                                              type: LabelEntity.Repository
//                                          })
//                }
//            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Watchers")
                value: repo.watcherCount
                icon: "qrc:///icons/icon-m-eye"

                onClicked: {
                    if (repo.watcherCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Watchers"),
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              userType: User.Watcher
                                          })
                }
            }   
            RelatedValueItem {
                width: parent.width

                label: qsTr("Contributors")
                value: repo.contributorCount
                icon: "image://theme/icon-m-media-artists"

                onClicked: {
                    if (repo.contributorCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Contributors"),
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              userType: User.Contributor
                                          })
                }
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("License")
                value: repo.license.name
                icon: "image://theme/icon-m-file-document-light"

                onClicked: pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                              branch: repo.defaultBranch,
                                              owner: repo.owner.login,
                                              path: "LICENSE",
                                              repo: repo.name,
                                              repoId: repo.nodeId
                                          })

            }

            SectionHeader {
                text: qsTr("Content")
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
                                                    branches: repo.branches,
                                                    defaultBranch: repo.defaultBranch
                                                })

                    dialog.accepted.connect(function() {
                        selectedBranch = dialog.selected
                    })
                }
            }

            RelatedItem {
                title: qsTr("README")

                onClicked: pageStack.push(Qt.resolvedUrl("MarkdownViewerPage.qml"), {
                                              branch: selectedBranch,
                                              owner: repo.owner.login,
                                              path: "README.md",
                                              repo: repo.name,
                                              repoId: repo.nodeId
                                          })
            }

            RelatedItem {
                title: qsTr("Browse code")

                onClicked: pageStack.push(Qt.resolvedUrl("TreeListPage.qml"), {
                                              branch: selectedBranch,
                                              owner: repo.owner.login,
                                              repoName: repo.name,
                                              repoId: repo.nodeId,
                                              modelType: TreeModel.Repository
                                          })
            }

//            RelatedValueItem {
//                label: qsTr("Commits")
//                icon: "qrc:/icons/icon-m-commit"
//                value: StringHelper.count(request.commitCount)

//                onClicked: {
//                    pageStack.push(Qt.resolvedUrl("CommitsListPage.qml"), {
//                                              identifier: repo.nodeId,
//                                              type: Commit.Repository
//                                          })
//                }
//            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }
        } 
    }

    Connections {
        target: SailHub.api()
        onRepoAvailable: {
            if (repo.nodeId !== page.nodeId) return
            page.repo = repo
            loading = false
        }
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

    Component.onCompleted: SailHub.api().getRepo(page.nodeId)
}


