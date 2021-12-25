import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property bool canCreateNew: true
    property string description
    property alias identifier: discussionsModel.identifier
    property alias type: discussionsModel.modelType
    property bool sorting: true
    property alias states: discussionsModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/discussions"

        property alias sortRole: discussionsModel.sortRole
        property alias sortOrder: discussionsModel.sortOrder
    }

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Discussions")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: discussionsModel.loading
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

            MenuItem {
                text: qsTr("Start new")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectDiscussionCategoryDialog.qml"), {
                                                    repoId: identifier
                                                })

                    dialog.accepted.connect(function() {
                        var dialogContent = pageStack.push(Qt.resolvedUrl("../dialogs/EditDiscussionDialog.qml"), {
                                                               acceptDestination: page,
                                                               acceptDestinationAction: PageStackAction.Pop,
                                                               edit: false
                                                           })
                        dialogContent.accepted.connect(function() {
                            SailHub.api().createDiscussion(dialogContent.title, dialogContent.body, dialog.selected, discussionsModel)
                        })
                    })
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: discussionsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No discussions available")
        }

        VerticalScrollDecorator {}

        model: DiscussionsModel { id: discussionsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: DiscussionListDelegate {
            id: delegate

            menu: ContextMenu {
                visible: model.viewerAbilities & Viewer.CanDelete
                MenuItem {
                    text: qsTr("Delete")
                    onClicked: delegate.remorseAction(qsTr("Deleting discussion"), function() {
                        SailHub.api().deleteDiscussion(model.nodeId)
                    })
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl("DiscussionPage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: discussionsModel.loading
            visible: discussionsModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", discussionsModel.totalCount - listView.count)
                onClicked: getDiscussions()
            }
        }
    }

    function getDiscussions() {
        SailHub.api().getPaginationModel(discussionsModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return DiscussionsModel.CreatedAtRole

        case 1:
            return DiscussionsModel.UpdatedAtRole

        default:
            return DiscussionsModel.UpdatedAtRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case DiscussionsModel.CreatedAtRole:
            return 0;

        case DiscussionsModel.UpdatedAtRole:
            return 1;

        default:
            return 1
        }
    }

    function refresh() {
        discussionsModel.reset()
        getDiscussions()
    }

    Connections {
        target: SailHub.api()
        onDiscussionCreated: refresh()
        onDiscussionDeleted: refresh()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete discussionsModel
}

