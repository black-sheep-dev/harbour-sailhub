import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property string identifier
    property int type: PullRequest.Repo
    property int states: PullRequest.StateOpen
    property int sortRole: PullRequestsModel.UpdatedAtRole
    property int sortOrder: Qt.DescendingOrder

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
                onClicked: refresh()
            }
            MenuItem {
                text: qsTr("Sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        qsTr("Created at"),
                                                        qsTr("Updated at")
                                                    ]
                                                })

                    dialog.accepted.connect(function() {
                        sortOrder = dialog.order
                        sortRole = getSortRoleFromIndex(dialog.field)

                        refresh()
                    })
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
            sortRole: PullRequestsModel.UpdatedAtRole
            sortOrder: Qt.DescendingOrder
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
                onClicked: getPullRequests()
            }
        }
    }

    function getPullRequests() {
        SailHub.api().getPaginationModel(pullRequestsModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return PullRequestsModel.CreatedAtRole

        case 1:
            return PullRequestsModel.UpdatedAtRole

        default:
            return PullRequestsModel.UpdatedAtRole
        }
    }

    function getSortFieldIndex() {
        switch (page.sortRole) {
        case PullRequestsModel.CreatedAtRole:
            return 0;

        case PullRequestsModel.UpdatedAtRole:
            return 1;

        default:
            return 0
        }
    }

    function refresh() {
        pullRequestsModel.reset()
        getPullRequests()
    }

    Component.onCompleted: refresh()
}

