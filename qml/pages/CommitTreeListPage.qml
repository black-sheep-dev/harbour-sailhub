import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property alias commitId: treeModel.identifier
    property string desc


    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Changed files"
            title: qsTrId("id-changed-files")
            description: desc
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: treeModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    SailHub.api().getModel(treeModel)
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: treeModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No files available"
            text: qsTrId("id-no-files-available")
        }

        VerticalScrollDecorator {}

        model: TreeSortFilterModel {
            id: treeSortFilterModel
            sourceModel: TreeModel {
                id: treeModel
                modelType: TreeModel.Commit
            }
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }
    }

    Connections {
        target: treeModel
        onLoadingChanged: treeSortFilterModel.sortModel()
    }

    Component.onCompleted: SailHub.api().getModel(treeModel)
}
