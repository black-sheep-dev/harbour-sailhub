import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property alias description: pageHeader.description
    property alias identifier: issuesModel.identifier
    property alias type: issuesModel.modelType
    property alias states: issuesModel.state
    property alias sortRole: issuesModel.sortRole
    property alias sortOrder: issuesModel.sortOrder

    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: issuesModel.loading

            MenuItem {
                visible: type !== Issue.User
                text: qsTr("New issue")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().createIssue(dialog.title, dialog.body, issuesModel)
                    })
                }
            }

            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    refresh()
                }
            }
            MenuItem {
                text: qsTr("Sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        qsTr("Created at"),
                                                        qsTr("Updated at"),
                                                        qsTr("Comments")
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

        anchors.fill: parent

        PageHeader {
            id: pageHeader
            title: qsTr("Issues")
        }

        ComboBox {
            id: statusComboBox
            width: parent.width
            anchors.top: pageHeader.bottom

            label: qsTr("Status")

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Open")
                    onClicked: {
                        page.states = Issue.StateOpen
                        refresh()
                    }
                }
                MenuItem {
                    text: qsTr("Closed")
                    onClicked: {
                        page.states = Issue.StateClosed
                        refresh()
                    }
                }
            }
        }
        SilicaListView {
            id: listView
            width: parent.width
            anchors.top: statusComboBox.bottom
            anchors.bottom: parent.bottom
            clip: true

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

                lastItem: index == (listView.count - 1)

                onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), {
                                              nodeId: model.nodeId
                                          })

            }
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
        switch (page.sortRole) {
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
    }

    Component.onCompleted: refresh()
}

