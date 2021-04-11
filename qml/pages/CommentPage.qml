import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

Page {
    property Comment comment
    property alias description: pageHeader.description

    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            visible: comment.viewerAbilities & (Viewer.CanDelete | Viewer.CanUpdate)
            MenuItem {
                visible: comment.viewerAbilities & Viewer.CanUpdate
                text: qsTr("Edit")

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditCommentDialog.qml"), {
                                                    edit: true,
                                                    body: comment.body
                                                })

                    dialog.accepted.connect(function() {
                        comment.body = dialog.body
                        SailHub.api().updateComment(comment)
                    })
                }
            }
            MenuItem {
                visible: comment.viewerAbilities & Viewer.CanDelete
                text: qsTr("Delete")

                onClicked: remorse.execute(qsTr("Deleting comment"), function() {
                    SailHub.api().deleteComment(comment.nodeId)
                })
            }
        }

        anchors.fill: parent
        contentHeight: contentColumn.height

        RemorsePopup { id: remorse }

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                id: pageHeader
                title: qsTr("Comment")
            }

            CommentItem {
                authorAvatar: comment.author.avatarUrl
                authorLogin: comment.author.login
                body: comment.body
                edited: comment.edited
                timeSpan: comment.createdAtTimeSpan
            }
        }
    }

    Connections {
        target: SailHub.api()
        onCommentDeleted: pageStack.navigateBack()
    }
}
