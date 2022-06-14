import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: releasesModel.identifier
    property alias type: releasesModel.modelType
    property bool sorting: true
    property alias states: releasesModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/releases"

        property alias sortRole: releasesModel.sortRole
        property alias sortOrder: releasesModel.sortOrder
    }

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            id: header
            //% "Releases"
            title: qsTrId("id-releases")
            description: header.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: releasesModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    refresh()
                }
            }
            MenuItem {
                visible: sorting
                //% "Sorting"
                text: qsTrId("id-sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: config.sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        //% "Created at"
                                                        qsTrId("id-created-at"),
                                                        //% "Name"
                                                        qsTrId("id-name")
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
            running: releasesModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No releases available"
            text: qsTrId("id-no-releases-available")
        }

        VerticalScrollDecorator {}

        model: ReleasesModel { id: releasesModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: ReleaseListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("ReleasePage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: releasesModel.loading
            visible: releasesModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", releasesModel.totalCount - listView.count)
                onClicked: getReleases()
            }
        }
    }

    function getReleases() {
        SailHub.api().getPaginationModel(releasesModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return ReleasesModel.CreatedAtRole

        default:
            return ReleasesModel.NameRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case ReleasesModel.CreatedAtRole:
            return 0;

        case ReleasesModel.NameRole:
            return 1;

        default:
            return 0
        }
    }

    function refresh() {
        releasesModel.reset()
        getReleases()
    }

    Connections {
        target: SailHub.api()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete releasesModel
}

