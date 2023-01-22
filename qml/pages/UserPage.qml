import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../queries/"
import "../tools/"
import "../."

Page {
    property string nodeId
    property string login
    property bool loading: true

    property var user
    property bool viewerIsFollowing: false

    id: page
    allowedOrientations: Orientation.All

    function getQueryVariables() {
        var obj = new Object
        if (login.length > 0) {
            obj["userLogin"] = page.login
        } else {
            obj["nodeId"] = page.nodeId
        }

        return obj
    }

    function refresh() {
        loading = true
        Api.request({
                        query: 'query(' + (login.length > 0 ? "$userLogin: String!" : "$nodeId: ID!") + ') {
                                    ' + (login.length > 0 ? "user(login: $userLogin)" : "node(id: $nodeId)") + ' {
                                        ... on User {
                                            id
                                            avatarUrl
                                            bio
                                            company
                                            contributionsCollection {
                                                contributionCalendar {
                                                    totalContributions
                                                }
                                            }
                                            followers {
                                                totalCount
                                            }
                                            following {
                                                totalCount
                                            }
                                            gists (privacy: ALL) {
                                                totalCount
                                            }
                                            location
                                            login
                                            isViewer
                                            name
                                            organizations {
                                                totalCount
                                            }
                                            repositories {
                                                totalCount
                                            }
                                            starredRepositories {
                                                totalCount
                                            }
                                            status {
                                                emoji
                                                message
                                            }
                                            twitterUsername
                                            viewerCanFollow
                                            viewerIsFollowing
                                            websiteUrl
                                        }
                                    }
                                }',
                        variables: getQueryVariables()
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to load user details"
                            notify.show(qsTrId("id-failed-to-load-user-details"))
                            return
                        }

                        if (result.hasOwnProperty("user")) {
                            user = result.user
                            viewerIsFollowing = result.user.viewerIsFollowing
                            nodeId = result.user.id
                        } else if (result.hasOwnProperty("node")) {
                            user = result.node
                            viewerIsFollowing = result.node.viewerIsFollowing
                            nodeId = result.node.id
                        }
                    })
    }

    FollowUserMutation {
        id: followUserMutation
        nodeId: user.id
        onResultChanged: viewerIsFollowing = result.followUser.user.viewerIsFollowing
    }

    UnfollowUserMutation {
        id: unfollowUserMutation
        nodeId: user.id
        onResultChanged: viewerIsFollowing = result.unfollowUser.user.viewerIsFollowing
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

    ViewPlaceholder {
        enabled: user === null && query.ready
        //% "User unavailable"
        text: qsTrId("id-user-unavailable")
    }

    SilicaFlickable {
        PullDownMenu {
            busy: loading

            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
            MenuItem {
                visible: user.viewerCanFollow
                text: viewerIsFollowing ?
                          //% "Unfollow"
                          qsTrId("id-unfollow") :
                          //% "Follow"
                          qsTrId("id-follow")

                onClicked: viewerIsFollowing ? unfollowUserMutation.execute() : followUserMutation.execute()
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        opacity: loading ? 0 : 1
        Behavior on opacity { FadeAnimation {} }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                //% "Profile"
                title: qsTrId("id-profile")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    height: Theme.itemSizeMedium
                    width: height
                    source: user.avatarUrl
                }

                Column {
                    width: parent.width - avatarIcon.width - Theme.paddingMedium
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    Label {
                        visible: user.name.length > 0

                        font.pixelSize: Theme.fontSizeLarge
                        color: Theme.highlightColor

                        text: user.name
                    }

                    Label {
                        font.pixelSize: Theme.fontSizeMedium
                        color: Theme.highlightColor

                        text: user.login
                    }
                }
            }

            Row {
                visible: user.status !== null
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Image {
                    id: emojiIcon
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeSmall
                    height: width
                    sourceSize.width: width
                    sourceSize.height: width

                    source: DataUtils.getEmojiUrl(user.status.emoji)
                }

                Label {
                    id: textLabel
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - emojiIcon.width - parent.spacing
                    wrapMode: Text.Wrap
                    textFormat: Text.RichText

                    text: MarkdownParser.parse(user.status.message)
                }
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            MarkdownLabel {
                visible: user.bio.length > 0

                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parse(user.bio)
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // Info
            IconLabel {
                visible: user.twitterUsername !== null && user.twitterUsername.length > 0

                icon: "image://theme/icon-m-message"
                label: user.twitterUsername

                onClicked: Qt.openUrlExternally("https:/twitter.com/" + user.twitterUsername)
            }

            IconLabel {
                enabled: false
                visible: user.company !== null && user.company.length > 0

                icon: "image://theme/icon-m-company"
                label: user.company
            }

            IconLabel {
                enabled: false
                visible: user.location !== null && user.location.length > 0

                icon: "image://theme/icon-m-location"
                label: user.location
            }

            IconLabel {
                visible: user.websiteUrl !== null && user.websiteUrl.length > 0

                icon: "image://theme/icon-m-website"
                label: user.websiteUrl

                onClicked: Qt.openUrlExternally(user.websiteUrl)
            }

            Item {
                height: Theme.paddingMedium
                width: 1
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingSmall

                CounterItem {
                    width: parent.width / 2

                    //% "%n follower(s)"
                    title: qsTrId("id-followers-count", user.followers.totalCount)
                    icon: "image://theme/icon-m-users"

                    onClicked: {
                        if (user.followers.totalCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                   nodeId: nodeId,
                                                   itemsQueryType: "FOLLOWERS",
                                                   //% "Followers"
                                                   title: qsTrId("id-followers"),
                                                   description: user.login
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 2

                    //% "%n following(s)"
                    title: qsTrId("id-following-count", user.following.totalCount)
                    icon: "image://theme/icon-m-message-forward"

                    onClicked: {
                        if (user.following.totalCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                   nodeId: nodeId,
                                                   itemsQueryType: "FOLLOWING",
                                                   //% "Following"
                                                   title: qsTrId("id-following"),
                                                   description: user.login
                                              })
                    }
                }
            }

            // related items
            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            RelatedValueItem {
                //% "Repositories"
                label: qsTrId("id-repositories")
                value: user.repositories.totalCount
                icon: "image://theme/icon-m-file-archive-folder"
                onClicked: {
                    if (user.repositories.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                  nodeId: nodeId,
                                                                  itemsQueryType: "USER_REPOS",
                                                                  //% "Repositories"
                                                                  title: qsTrId("id-repositories"),
                                                                  description: user.login
                                                              })
                }
            }
            RelatedValueItem {
                //% "Gists"
                label: qsTrId("id-gists")
                value: user.gists.totalCount
                icon: "image://theme/icon-m-file-note-dark"
                onClicked: {
                    if (user.gists.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("GistsListPage.qml"), {
                                                                  nodeId: nodeId,
                                                                  description: user.login
                                                              })
                }
            }
            RelatedValueItem {
                //% "Organizations"
                label: qsTrId("id-organizations")
                value: user.organizations.totalCount
                icon: "image://theme/icon-m-company"
                onClicked: {
                    if (user.organizations.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("OrganizationsListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "USER_ORGANIZATIONS",
                                               //% "Organizations"
                                               title: qsTrId("id-organizations"),
                                               description: user.login
                                          })
                }
            }
            RelatedValueItem {
                //% "Starred"
                label: qsTrId("id-starred")
                value: user.starredRepositories.totalCount
                icon: "image://theme/icon-m-favorite"
                onClicked: {
                    if (user.starredRepositories.totalCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                  nodeId: nodeId,
                                                                  itemsQueryType: "STARRED_REPOS",
                                                                  //% "Starred repositories"
                                                                  title: qsTrId("id-starred-repositories"),
                                                                  description: user.login
                                                              })
                }
            }

            SectionHeader {
                //% "Contributions in the last 12 month"
                text: qsTrId("id-contributions-last-twelve-month")
            }

            RelatedValueItem {
                //% "Contributions"
                label: qsTrId("id-contributions")
                value: user.contributionsCollection.contributionCalendar.totalContributions
                icon: "image://theme/icon-m-health"
            }
        }
    }

    Component.onCompleted: refresh()
}


