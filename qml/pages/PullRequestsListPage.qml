import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: pullRequestsModel.identifier
    property alias type: pullRequestsModel.modelType
    property alias states: pullRequestsModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/pull-requests"

        property alias sortRole: pullRequestsModel.sortRole
        property alias sortOrder: pullRequestsModel.sortOrder
    }

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
                text: {
                    if (page.states & PullRequestState.Open)
                        return qsTr("Show closed pull requests")
                    else if (page.states & PullRequestState.Closed)
                        return qsTr("Show open pull requests")
                }

                onClicked: {
                    if (page.states & PullRequestState.Open)
                        page.states = PullRequestState.Closed | PullRequestState.Merged
                    else if (page.states & PullRequestState.Closed)
                        page.states = PullRequestState.Open

                    refresh()
                }
            }
            MenuItem {
                text: qsTr("Refresh")
                onClicked: refresh()
            }
            MenuItem {
                text: qsTr("Sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: config.sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        qsTr("Created at"),
                                                        qsTr("Updated at")
                                                    ]
                                                })

                    dialog.accepted.connect(function() {
                        config.sortOrder = dialog.order
                        config.sortRole = getSortRoleFromIndex(dialog.field)

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

        model: PullRequestsModel{ id: pullRequestsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: PullRequestListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("PullRequestPage.qml"), {
                                          nodeId: model.nodeId
                                      })

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
        switch (config.sortRole) {
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
    Component.onDestruction: delete pullRequestsModel
}

