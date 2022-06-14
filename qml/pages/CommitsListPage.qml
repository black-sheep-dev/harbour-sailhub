import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property bool canCreateNew: true
    property alias identifier: commitsModel.identifier
    property alias type: commitsModel.modelType

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Commits"
            title: qsTrId("id-commits")
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: commitsModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
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
            running: commitsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No commits available"
            text: qsTrId("id-no-commits-available")
        }

        VerticalScrollDecorator {}

        model: CommitsModel { id: commitsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: CommitListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("CommitPage.qml"), {
                                          nodeId: model.nodeId
                                      })

        }

        PushUpMenu {
            busy: commitsModel.loading
            visible: commitsModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", commitsModel.totalCount - listView.count)
                onClicked: getCommits()
            }
        }
    }

    function getCommits() {
        SailHub.api().getPaginationModel(commitsModel)
    }

    function refresh() {
        commitsModel.reset()
        getCommits()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete commitsModel
}

