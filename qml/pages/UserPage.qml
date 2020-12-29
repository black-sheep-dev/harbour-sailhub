import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    property bool loading: true
    property bool own: false
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
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.loading = true
                    SailHub.api().getUser(page.login)
                }
            }

            MenuItem {
                visible: page.own
                text: qsTr("Follow")
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

                Image {
                    id: avatarIcon
                    height: Theme.itemSizeMedium
                    width: height

                    source: user.avatarUrl

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
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

            Item {
                height: Theme.paddingSmall
                width: 1
            }

            // bio
            Label {
                visible: user.bio.length > 0

                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.WordWrap

                color: Theme.highlightColor

                text: user.bio
            }

            // Info
            IconLabel {
                visible: user.twitterUsername.length > 0

                icon: "image://theme/icon-m-message"
                label: user.twitterUsername
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
                                                  identifier: page.login,
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
                                                  identifier: page.login,
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
                                                                  identifier: login,
                                                                  repoType: Repo.User
                                                              })
                }
            }
            RelatedValueItem {
                label: qsTr("Organizations")
                value: user.organizations
            }
            RelatedValueItem {
                label: qsTr("Starred")
                value: user.starredRepositories
            }
        }
    }

    Connections {
        target: SailHub.api()
        onUserAvailable: {
            if (page.login !== user.login) return

            page.user = user
            loading = false
        }
    }

    Component.onCompleted: SailHub.api().getUser(page.login)
}


