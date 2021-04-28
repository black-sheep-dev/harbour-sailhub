import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property bool busy: false
    property string nodeId
    property Discussion discussion

    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getDiscussion(page.nodeId)
                }
            }
            MenuItem {
                visible: discussion.viewerAbilities & Viewer.CanUpdate
                text: qsTr("Edit")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditDiscussionDialog.qml"), {
                                                    edit: true,
                                                    title: discussion.title,
                                                    body: discussion.body
                                                })

                    dialog.accepted.connect(function() {
                        discussion.title = dialog.title
                        discussion.body = dialog.body
                        SailHub.api().updateDiscussion(discussion)
                    })
                }
            }

            MenuItem {
                visible: discussion.viewerAbilities & Viewer.CanDelete
                text: qsTr("Delete")

                onClicked: remorse.execute(qsTr("Deleting discussion"), function() {
                    SailHub.api().deleteDiscussion(discussion.nodeId)
                })
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: qsTr("Discussion")
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
                    source: discussion.author.avatarUrl
                    anchors.verticalCenter: parent.verticalCenter

                    fallbackItemVisible: false

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: discussion.repository + " #" + discussion.number
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: discussion.title
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Icon {
                    id: closedIcon
                    source: discussion.categoryEmoji
                }

                Label {
                    width: parent.width - closedIcon.width - parent.spacing
                    anchors.verticalCenter: closedIcon.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor

                    text: discussion.category
                }
            }

            CommentItem {
                authorAvatar: discussion.author.avatarUrl
                authorLogin: discussion.author.login
                body: discussion.body
                //edited: discussion.edited
                timeSpan: discussion.updatedAtTimeSpan
            }

            SectionHeader {
                text: qsTr("Reactions")
            }

            ReactionsItem {
                node: discussion

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/ReactionDialog.qml"), {
                                                    reactions: discussion.viewerReactions
                                                })

                    dialog.accepted.connect(function() {
                        if (discussion.viewerReactions === dialog.reactions) return;

                        SailHub.api().updateReactions(
                                    discussion.nodeId,
                                    discussion.viewerReactions,
                                    dialog.reactions)

                        discussion.updateReactionCount(dialog.reactions)
                        discussion.viewerReactions = dialog.reactions
                    })
                }
            }

            SectionHeader {
                text: qsTr("Relations")
            }

            RelatedValueItem {
                label: qsTr("Comments")
                icon: "image://theme/icon-m-chat"
                value: discussion.commentCount

//                onClicked: pageStack.push(Qt.resolvedUrl("CommentsListPage.qml"), {
//                                              description: discussion.repository + " #" + discussion.number,
//                                              identifier: discussion.nodeId,
//                                              type: Comment.Discussion
//                                          })
            }

            Item {
                width: 1
                height: Theme.paddingMedium
            }
        }
    }

    Connections {
        target: SailHub.api()
        onDiscussionAvailable: {
            if (discussion.nodeId !== page.nodeId) return

            page.discussion = discussion;
            page.busy = false;
        }
        onDiscussionDeleted: pageStack.navigateBack()
    }

    Component.onCompleted: SailHub.api().getDiscussion(page.nodeId)
}
