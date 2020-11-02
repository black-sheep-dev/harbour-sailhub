import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../components/"

Page {
    property User user

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                enabled: user !== undefined
                text: qsTr("Follow")
                onClicked: SailHub.followUser(user.login)
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingSmall

            PageHeader {
                title: user.name
            }

            CircleImage {
                id: avatar
                width: parent.width / 4
                source: user.avatarUrl
                anchors.horizontalCenter: parent.horizontalCenter

                fallbackItemVisible: false
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            Separator {
                width: parent.width
                color: Theme.highlightBackgroundColor
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            // login
            Row {
                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Username")
                }

                Label {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    text: user.login
                }
            }

            // company
            Row {
                visible: user.company.length > 0

                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Company")
                }

                Label {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    text: user.company
                }
            }

            // location
            Row {
                visible: user.location.length > 0

                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Location")
                }

                Label {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    text: user.location
                }
            }

            // blog
            Row {
                visible: user.blog.length > 0

                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Blog")
                }

                LinkedLabel {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    linkColor: Theme.secondaryHighlightColor
                    plainText: user.blog
                }
            }

            // email
            Row {
                visible: user.email.length > 0

                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Email")
                }

                LinkedLabel {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    linkColor: Theme.secondaryHighlightColor
                    plainText: user.email
                }
            }

            // twitter
            Row {
                visible: user.twitterUsername.length > 0

                width: parent.width

                Label {
                    width: parent.width * 0.4

                    color: Theme.highlightColor

                    text: qsTr("Twitter")
                }

                Label {
                    width: parent.width * 0.6
                    wrapMode: Text.Wrap

                    text: user.twitterUsername
                }
            }

            // SOCIAL
            SectionHeader {
                text: qsTr("Social")
            }

            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium

                Label {
                    anchors.left: parent.left
                    anchors.right: followersIconOpen.left
                    anchors.verticalCenter: parent.verticalCenter

                    color: Theme.highlightColor

                    text: qsTr("Has %n follower(s)", "0", user.followers)
                }

                Image {
                    visible: user.followers > 0
                    id: followersIconOpen
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    source: "image://theme/icon-m-right"
                }

                onClicked: {
                    if (user.followers === 0)
                        return;

                    SailHub.getFollowers(user.login)
                }

                Connections {
                    target: SailHub
                    onFollowersAvailable: pageStack.push(Qt.resolvedUrl("UsersBasicListPage.qml"), {
                                                             title: qsTr("Followers"),
                                                             userModel: model
                                                         })
                }
            }

            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeSmall

                Label {
                    anchors.left: parent.left
                    anchors.right: followingIconOpen.left
                    anchors.verticalCenter: parent.verticalCenter

                    color: Theme.highlightColor

                    text: qsTr("Follows %n user(s)", "0", user.following)
                }

                Image {
                    visible: user.following > 0
                    id: followingIconOpen
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    source: "image://theme/icon-m-right"
                }

                onClicked: {
                    if (user.followers === 0)
                        return;

                    SailHub.getFollowers(user.login)
                }

                Connections {
                    target: SailHub
                    onFollowingAvailable: pageStack.push(Qt.resolvedUrl("UsersBasicListPage.qml"), {
                                                             title: qsTr("Following Users"),
                                                             userModel: model
                                                         })
                }
            }
        }
    }
}

