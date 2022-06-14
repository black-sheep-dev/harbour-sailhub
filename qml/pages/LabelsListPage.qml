import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: labelsModel.identifier
    property alias type: labelsModel.modelType
    property alias states: labelsModel.state

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/labels"

        property alias sortRole: labelsModel.sortRole
        property alias sortOrder: labelsModel.sortOrder
    }

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Labels"
            title: qsTrId("id-labels")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: labelsModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    refresh()
                }
            }
            MenuItem {
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
            running: labelsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No labels available"
            text: qsTrId("id-no-labels-available")
        }

        VerticalScrollDecorator {}

        model: LabelsModel { id: labelsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: LabelListDelegate { id: delegate }

        PushUpMenu {
            busy: labelsModel.loading
            visible: labelsModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", labelsModel.totalCount - listView.count)
                onClicked: getLabels()
            }
        }
    }

    function getLabels() {
        SailHub.api().getPaginationModel(labelsModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return LabelsModel.CreatedAtRole

        default:
            return LabelsModel.NameRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case LabelsModel.CreatedAtRole:
            return 0;

        case LabelsModel.NameRole:
            return 1;

        default:
            return 0
        }
    }

    function refresh() {
        labelsModel.reset()
        getLabels()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete labelsModel
}

