import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: commentsModel.identifier
    property alias type: commentsModel.modelType

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Comments")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: commentsModel.loading

            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    refresh()
                }
            }

            MenuItem {
                text: qsTr("New comment")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().addComment(dialog.body, commentsModel.identifier)
                    })
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: commentsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No comments available")
        }

        VerticalScrollDecorator {}

        model: CommentsModel { id: commentsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: CommentListDelegate {
            id: delegate

            menu: ContextMenu {
                visible: model.viewerAbilities & Viewer.CanDelete
                MenuItem {
                    text: qsTr("Quote reply")
                    onClicked: {
                        const text = ">"+ model.body + "\n\n";
                        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                        edit: false,
                                                        body: text
                                                    })

                        dialog.accepted.connect(function() {
                            SailHub.api().addComment(dialog.body, commentsModel.identifier)
                        })
                    }
                }
                MenuItem {
                    text: qsTr("Delete")
                    onClicked: remorse.execute(delegate, qsTr("Deleting comment"), function() {
                        SailHub.api().deleteComment(model.nodeId)
                        commentsModel.deleteComment(model.index)
                    })
                }
            }

            RemorseItem { id: remorse }

            lastItem: index == (listView.count - 1)

            onClicked: pageStack.push(Qt.resolvedUrl("CommentPage.qml"), {
                                          subjectId: commentsModel.identifier,
                                          comment: commentsModel.commentAt(model.index),
                                          description: page.description
                                      })
        }

        PushUpMenu {
            busy: commentsModel.loading
            visible: commentsModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", commentsModel.totalCount - listView.count)
                onClicked: getComments()
            }
        }
    }

    function getComments() {
        SailHub.api().getPaginationModel(commentsModel)
    }

    function refresh() {
        commentsModel.reset()
        getComments()
    }

    Connections {
        target: SailHub.api()
        onCommentAdded: refresh()
        onCommentDeleted: refresh()
    }

    Component.onCompleted: refresh()
}

