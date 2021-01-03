import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    property bool busy: false
    property bool loading: true
    property string nodeId
    property Repo repo

    id: page

    allowedOrientations: Orientation.All

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
                text: qsTr("Refresh")
                onClicked: {
                    page.loading = true
                    SailHub.api().getRepo(page.nodeId)
                }
            }
            MenuItem {
                enabled: repo.viewerCanSubscribe
                text: {
                    switch (repo.viewerSubscription) {
                    case Repo.SubscriptionIgnored:
                        return qsTr("Watch")

                    default:
                        return qsTr("Unwatch")
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectSubscriptionDialog.qml"),
                                                { subscription: repo.viewerSubscription })

                    dialog.accepted.connect(function() {
                        page.busy = true
                        SailHub.api().subscribeToRepo(repo.nodeId, dialog.subscription)
                    })
                }
            }

            MenuItem {
                text: repo.viewerHasStarred ? qsTr("Unstar") : qsTr("Star")

                onClicked: {
                    page.busy = true
                    SailHub.api().starRepo(repo.nodeId, !repo.viewerHasStarred)
                }
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: repo.name
                description: repo.owner.login
            }

            // owner
            BackgroundItem {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Image {
                        id: avatarIcon
                        width: Theme.itemSizeSmall / 2
                        height: Theme.itemSizeSmall / 2
                        anchors.verticalCenter: parent.verticalCenter

                        source: repo.owner.avatarUrl
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

            // description
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                color: Theme.highlightColor
                wrapMode: Text.Wrap

                text: repo.description
            }

            // homepage
            Item {
                visible: repo.homepageUrl.length > 0
                height: Theme.paddingSmall
                width: 1
            }

            IconLabel {
                visible: repo.homepageUrl.length > 0

                icon: "image://theme/icon-m-website"
                label: repo.homepageUrl
            }

            // private repo
            Item {
                visible: repo.isPrivate
                height: Theme.paddingSmall
                width: 1
            }

            IconLabel {
                visible: repo.isPrivate

                icon: "image://theme/icon-s-outline-secure"
                label: qsTr("Private")
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingSmall

                CounterItem {
                    width: parent.width / 3

                    title: qsTr("%n Star(s)", "0", repo.stargazerCount)
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

                    title: qsTr("%n Fork(s)", "0", repo.forkCount)
                    icon: "image://theme/icon-m-shuffle"

                    onClicked: {
                        if (repo.forkCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                     login: repo.owner.login + "/" + repo.name,
                                                                     identifier: repo.nodeId,
                                                                     repoType: Repo.Fork
                                                                 })
                    }
                }
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            // Related items
            RelatedValueItem {
                width: parent.width

                label: qsTr("Issues")
                value: repo.issueCount

                onClicked: {
                    if (repo.issueCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              states: Issue.StateOpen
                                          })
                }
            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Pull Requests")
                value: repo.pullRequestCount
            }
            RelatedValueItem {
                width: parent.width

                label: qsTr("Watchers")
                value: repo.watcherCount

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
            }

            // Readme
            /*
            SectionHeader {
                visible: repo.readme.length > 0
                text: qsTr("README")
            }

            TextArea {
                visible: repo.readme.length > 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                readOnly: true

                text: repo.readme
            }
            */
        }
    }

    Connections {
        target: SailHub.api()
        onRepoAvailable: {
            if (repo.nodeId !== page.nodeId) return
            page.repo = repo
            loading = false
        }
    }

    Connections {
        target: SailHub.api()
        onRepoStarred: {
            if (nodeId !== repo.nodeId) return
            page.repo.viewerHasStarred = starred
            page.repo.stargazerCount += starred ? 1 : -1
            page.busy = false
        }
    }

    Connections {
        target: SailHub.api()
        onSubscribedToRepo: {
            if (nodeId !== repo.nodeId) return
            page.repo.viewerSubscription = state
            page.busy = false
        }
    }

    Component.onCompleted: SailHub.api().getRepo(page.nodeId)
}


