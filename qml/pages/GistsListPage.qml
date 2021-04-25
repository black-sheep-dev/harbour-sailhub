import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: gistsModel.identifier
    property alias type: gistsModel.modelType
    property bool sorting: true
    property alias states: gistsModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/gists"

        property alias sortRole: gistsModel.sortRole
        property alias sortOrder: gistsModel.sortOrder
    }

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Gists")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: gistsModel.loading
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
                                                        qsTr("Pushed at")
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
            running: gistsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No gists available")
        }

        VerticalScrollDecorator {}

        model: GistsModel { id: gistsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: GistListDelegate {
            id: delegate

            lastItem: index == (listView.count - 1)

//            onClicked: pageStack.push(Qt.resolvedUrl("GistPage.qml"), {
//                                          nodeId: model.nodeId
//                                      })

        }

        PushUpMenu {
            busy: gistsModel.loading
            visible: gistsModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", gistsModel.totalCount - listView.count)
                onClicked: getGists()
            }
        }
    }

    function getGists() {
        SailHub.api().getPaginationModel(gistsModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return GistsModel.CreatedAtRole

        case 1:
            return GistsModel.UpdatedAtRole

        case 2:
            return GistsModel.PushedAtRole

        default:
            return GistsModel.UpdatedAtRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case GistsModel.CreatedAtRole:
            return 0;

        case GistsModel.UpdatedAtRole:
            return 1;

        case GistsModel.PushedAtRole:
            return 2;

        default:
            return 0
        }
    }

    function refresh() {
        gistsModel.reset()
        getGists()
    }

    Component.onCompleted: refresh()
}

