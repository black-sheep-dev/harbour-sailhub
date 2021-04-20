import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string branch: "master"
    property string owner
    property string path: "/"
    property string repoName
    property string repoId

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
                    SailHub.api().getRepoTree(repoId, branch, path, treeModel)
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
            sourceModel: TreeModel { id: treeModel }
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: ListItem {
            width: parent.width

            contentHeight: Theme.itemSizeMedium

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                anchors.verticalCenter: parent.verticalCenter
                spacing: Theme.paddingMedium

                Icon {
                    id: itemIcon
                    anchors.verticalCenter: parent.verticalCenter
                    source: {
                        if (model.type === TreeItem.Tree) {
                            return "image://theme/icon-m-file-folder"
                        } else {
                            switch (model.fileType) {
                            case File.Image:
                                return "image://theme/icon-m-file-image"

                            case File.Text:
                                return "image://theme/icon-m-file-document-light"

                            default:
                                return "image://theme/icon-m-file-other-light"
                            }
                        }
                    }
                }

                Label {
                    width: parent.width - itemIcon.width - parent.spacing
                    anchors.verticalCenter: parent.verticalCenter

                    text: model.name
                }
            }

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

    Component.onCompleted: SailHub.api().getRepoTree(repoId, branch, path, treeModel)
}
