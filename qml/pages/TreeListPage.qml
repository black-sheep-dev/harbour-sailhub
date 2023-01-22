import QtQuick 2.0
import Sailfish.Silica 1.0

import "../delegates/"
import "../."

Page {
    property string branch
    property string owner
    property string path: "/"
    property string repoName
    property string repoId
    property bool loading: true

    function load() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!, $branch: String!, $path: String!) {
                                   node(id: $nodeId) {
                                       ... on Repository {
                                           id
                                           ref(qualifiedName: $branch) {
                                               target {
                                                  ... on Commit {
                                                       file(path: $path) {
                                                           object {
                                                               ... on Tree {
                                                                   entries {
                                                                       extension
                                                                       name
                                                                       path
                                                                       type
                                                                      object {
                                                                           ... on Blob {
                                                                               isBinary
                                                                          }
                                                                       }
                                                                   }
                                                               }
                                                           }
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                   }
                               }',
                        variables: {
                            nodeId: repoId,
                            branch: branch,
                            path: path

                        }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to load file list"
                            notify.show(qsTrId("id-failed-to-load-file-list"))
                            return
                        }

                        filesModel.clear()

                        const parentFolder = path.substring(0, path.lastIndexOf("/"))
                        if (parentFolder.length === 0) parentFolder = "/"

                        if (path !== "/") filesModel.append({
                                                                name: "..",
                                                                path: parentFolder,
                                                                type: "tree"
                                                            })

                        // first folders
                        result.node.ref.target.file.object.entries.forEach(function(item) {
                            if (item.type === "tree") filesModel.append(item)
                        })

                        // now the files
                        result.node.ref.target.file.object.entries.forEach(function(item) {
                            if (item.type !== "tree") filesModel.append(item)
                        })
                    })
    }

    id: page
    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: loading

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            //% "Loading files..."
            text: qsTrId("id-loading-files")
        }
    }

    SilicaListView {
        PullDownMenu {
            busy: loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: load()
            }
        }

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

        model: ListModel { id: filesModel }

        opacity: loading ? 0.0 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: TreeListDelegate {
            width: parent.width

            menu: ContextMenu {
                MenuItem {
                    visible: model.type === "blob"
                    //% "Download"
                    text: qsTrId("id-download")
                    onClicked: Qt.openUrlExternally("https://github.com/" + owner + "/" + repoName + "/raw/" + branch + "/" + model.path)
                }
            }

            onClicked: {
                if (model.type === "tree") {
                    page.path = model.path
                    load()
                    return
                }

                switch (model.extension) {
                case ".md":
                    onClicked: pageStack.push(Qt.resolvedUrl("MarkdownViewerPage.qml"), {
                                                  branch: branch,
                                                  owner: owner,
                                                  path: model.path,
                                                  repo: repoName,
                                                  repoId: repoId
                                              })
                    break

                case ".bmp":
                case ".gif":
                case ".ico":
                case ".jpg":
                case ".jpeg":
                case ".png":
                case ".svg":
                    pageStack.push(Qt.resolvedUrl("ImageViewerPage.qml"), {
                                              branch: branch,
                                              owner: owner,
                                              path: model.path,
                                              repo: repoName
                                          })
                    break

                default:
                    if (model.object.isBinary) return

                    pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                                                      branch: page.branch,
                                                                      owner: page.owner,
                                                                      path: model.path,
                                                                      repo: page.repoName,
                                                                      repoId: page.repoId
                                                                  })
                    break
                }
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No files available"
            text: qsTrId("id-no-files-available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: load()
}
