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

            lastItem: index == (listView.count - 1)

//            onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), {
//                                          nodeId: model.nodeId
//                                      })

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
        onIssueCreated: refresh()
    }

    Component.onCompleted: refresh()
}

