import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../tools/"
import ".."

Page {
    property bool busy: false
    property bool loading: false
    property string nodeId
    property string login
    property User user

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
            visible: !user.isViewer
            busy: page.busy

            MenuItem {
                text: user.viewerIsFollowing ? qsTr("Unfollow") : qsTr("Follow")

                onClicked: {
                    page.busy = true
                    SailHub.api().followUser(user.nodeId, !user.viewerIsFollowing)
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
                title: qsTr("Profile")
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

                    fallbackItemVisible: false

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status === Image.Loading
                    }
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
                visible: user.statusMessage.length > 0
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

                    source: user.statusEmoji
                }

                Label {
                    id: textLabel
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - emojiIcon.width - parent.spacing
                    wrapMode: Text.Wrap
                    textFormat: Text.RichText

                    text: MarkdownParser.parse(user.statusMessage)
                }
            }

            Label {
                visible: user.statusMessage.length > 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parseRaw(user.status)
            }

            MarkdownLabel {
                visible: user.bio.length > 0

                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parse(user.bio)
            }

            // Info
            IconLabel {
                visible: user.twitterUsername.length > 0

                icon: "image://theme/icon-m-message"
                label: user.twitterUsername

                onClicked: Qt.openUrlExternally("https:/twitter.com/" + user.twitterUsername)
            }

            IconLabel {
                visible: user.location.length > 0

                icon: "image://theme/icon-m-location"
                label: user.location
            }

            IconLabel {
                visible: user.websiteUrl.length > 0

                icon: "image://theme/icon-m-website"
                label: user.websiteUrl

                onClicked: Qt.openUrlExternally(user.websiteUrl)
            }

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingSmall

                CounterItem {
                    width: parent.width / 3

                    title: qsTr("%n follower(s)", "0", user.followers)
                    icon: "image://theme/icon-m-users"

                    onClicked: {
                        if (user.followers === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                  identifier: user.nodeId,
                                                  userType: User.Follower
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 3

                    title: qsTr("%n following(s)", "0", user.following)
                    icon: "image://theme/icon-m-message-forward"

                    onClicked: {
                        if (user.following === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                  identifier: user.nodeId,
                                                  userType: User.Following
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
                label: qsTr("Repositories")
                value: user.repositories

                onClicked: {
                    if (user.repositories === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                  identifier: user.nodeId,
                                                                  repoType: Repo.User
                                                              })
                }
            }
            RelatedValueItem {
                label: qsTr("Gists")
                value: user.gistCount

                onClicked: {
                    if (user.gistCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("GistsListPage.qml"), {
                                                                  identifier: user.nodeId
                                                              })
                }
            }
            RelatedValueItem {
                label: qsTr("Organizations")
                value: user.organizations

                onClicked: {
                    if (user.organizations === 0) return;

                    pageStack.push(Qt.resolvedUrl("OrganizationsListPage.qml"), {
                                                                  title: user.login,
                                                                  identifier: user.nodeId,
                                                                  organizationType: Organization.IsMember
                                                              })
                }
            }
            RelatedValueItem {
                label: qsTr("Starred")
                value: user.starredRepositories

                onClicked: {
                    if (user.starredRepositories === 0) return;

                    pageStack.push(Qt.resolvedUrl("ReposListPage.qml"), {
                                                                  identifier: user.nodeId,
                                                                  repoType: Repo.Starred
                                                              })
                }
            }
        }
    }

    Connections {
        target: SailHub.api()
        onUserAvailable: {
            if (page.login.length > 0) {
                if (page.login !== user.login) return
            } else {
                if ( page.nodeId !== user.nodeId) return
            }

            page.user = user
            page.loading = false
        }

        onUserFollowed: {
            if (nodeId !== user.nodeId) return
            page.user.viewerIsFollowing = following
            page.user.followers += following ? 1 : -1
            page.busy = false
        }

        onProfileChanged: page.busy = false
    }

    Component.onCompleted: {
        if (page.nodeId.length > 0) {
            page.loading = true
            SailHub.api().getUser(page.nodeId)
        } else if (page.login.length > 0) {
            page.loading = true
            SailHub.api().getUserByLogin(page.login)
        } else {
            page.nodeId = user.nodeId
        }
    }
}


