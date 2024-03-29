import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property bool canCreateNew: true
    property string description
    property bool editState: true
    property alias identifier: issuesModel.identifier
    property alias type: issuesModel.modelType
    property bool sorting: true
    property alias states: issuesModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/issues"

        property alias sortRole: issuesModel.sortRole
        property alias sortOrder: issuesModel.sortOrder
    }

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Issues")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: issuesModel.loading
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    refresh()
                }
            }
            MenuItem {
                visible: sorting
                text: qsTr("Sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: config.sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        qsTr("Created at"),
                                                        qsTr("Updated at"),
                                                        qsTr("Comments")
                                                    ]
                                                })

                    dialog.accepted.connect(function() {
                        config.sortOrder = dialog.order
                        config.sortRole = getSortRoleFromIndex(dialog.field)

                        refresh()
                    })
                }
            }
            MenuItem {
                visible: type !== Issue.User && canCreateNew
                text: qsTr("Create new")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().createIssue(dialog.title, dialog.body, issuesModel)
                    })
                }
            }
            MenuItem {
                visible: editState
                text: {
                    if (page.states & IssueState.Open)
                        return qsTr("Show closed issues")
                    else if (page.states & IssueState.Closed)
                        return qsTr("Show open issues")
                }

                onClicked: {
                    if (page.states & IssueState.Open)
                        page.states = IssueState.Closed
                    else if (page.states & IssueState.Closed)
                        page.states = IssueState.Open

                    refresh()
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: issuesModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No issues available")
        }

        VerticalScrollDecorator {}

        model: IssuesModel { id: issuesModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: IssueListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), {
                                          nodeId: model.nodeId
                                      })

        }

        PushUpMenu {
            busy: issuesModel.loading
            visible: issuesModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", issuesModel.totalCount - listView.count)
                onClicked: getIssues()
            }
        }
    }

    function getIssues() {
        SailHub.api().getPaginationModel(issuesModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return IssuesModel.CreatedAtRole

        case 1:
            return IssuesModel.UpdatedAtRole

        case 2:
            return IssuesModel.CommentCountRole

        default:
            return IssuesModel.UpdatedAtRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case IssuesModel.CreatedAtRole:
            return 0;

        case IssuesModel.UpdatedAtRole:
            return 1;

        case IssuesModel.CommentCountRole:
            return 2;

        default:
            return 0
        }
    }

    function refresh() {
        issuesModel.reset()
        getIssues()
    }

    Connections {
        target: SailHub.api()
        onIssueCreated: refresh()
        onIssueDeleted: refresh()
        onIssueClosed: refresh()
        onIssueReopened: refresh()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete issuesModel
}

