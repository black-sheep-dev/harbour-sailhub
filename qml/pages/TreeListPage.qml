import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property alias branch: treeModel.branch
    property string owner
    property alias path: treeModel.path
    property string repoName
    property alias repoId: treeModel.identifier

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: repoName
            description: branch + ":" + path
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: treeModel.loading
            MenuItem {
                text: qsTr("Refresh")
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
            text: qsTr("No files available")
        }

        VerticalScrollDecorator {}

        model: TreeSortFilterModel {
            id: treeSortFilterModel
            sourceModel: TreeModel {
                id: treeModel
                modelType: TreeModel.Repository
            }
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: TreeListDelegate {
            width: parent.width

            onClicked: {
                if (model.type === TreeItem.Tree) {
                    pageStack.push(Qt.resolvedUrl("TreeListPage.qml"), {
                                              branch: page.branch,
                                              owner: page.owner,
                                              path: "/" + model.path,
                                              repoName: page.repoName,
                                              repoId: page.repoId
                                          })
                } else { 
                    if (model.fileType === File.Image) {
                        pageStack.push(Qt.resolvedUrl("ImageViewerPage.qml"), {
                                                  branch: page.branch,
                                                  owner: page.owner,
                                                  path: model.path,
                                                  repo: page.repoName
                                              })
                    } else if (model.fileType === File.Text) {
                        pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                                  branch: page.branch,
                                                  owner: page.owner,
                                                  path: model.path,
                                                  repo: page.repoName,
                                                  repoId: page.repoId
                                              })
                    } else if (model.fileType === File.Markdown) {
                        pageStack.push(Qt.resolvedUrl("MarkdownViewerPage.qml"), {
                                                  branch: page.branch,
                                                  owner: page.owner,
                                                  path: model.path,
                                                  repo: page.repoName,
                                                  repoId: page.repoId
                                              })
                    }

                }
            }
        }
    }

    Connections {
        target: treeModel
        onLoadingChanged: treeSortFilterModel.sortModel()
    }

    Component.onCompleted: SailHub.api().getModel(treeModel)
}
