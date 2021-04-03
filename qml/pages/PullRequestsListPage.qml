import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property string identifier
    property int type: PullRequest.Repo
    property int states: PullRequest.StateOpen

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Pull Requests")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: pullRequestsModel.loading
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    pullRequestsModel.reset()
                    SailHub.api().getPullRequests(pullRequestsModel)
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: pullRequestsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No pull requests available")
        }

        VerticalScrollDecorator {}

        model: PullRequestsModel{
            id: pullRequestsModel
            identifier: page.identifier
            modelType: page.type
            state: page.state
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: PullRequestListDelegate {
            id: delegate

            lastItem: index == (listView.count - 1)

//            onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), {
//                                          nodeId: model.nodeId
//                                      })

        }

        PushUpMenu {
            busy: pullRequestsModel.loading
            visible: pullRequestsModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", pullRequestsModel.totalCount - listView.count)
                onClicked: SailHub.api().getPullRequests(pullRequestsModel)
            }
        }
    }

    Component.onCompleted: SailHub.api().getPullRequests(pullRequestsModel)
}

