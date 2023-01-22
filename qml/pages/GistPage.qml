import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../components/"
import "../components/menu"
import "../delegates/"

Page {
    property string nodeId
    property var gist
    property bool loading: true

    function refresh() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!) {
                                    node(id: $nodeId) {
                                        ... on Gist {
                                            id
                                            comments {
                                                totalCount
                                            }
                                            description
                                            files {
                                                encodedName
                                                extension
                                                isImage
                                                language {
                                                    color
                                                    name
                                                }
                                                name
                                                size
                                                text
                                            }
                                            forks {
                                                totalCount
                                            }
                                            isFork
                                            isPublic
                                            name
                                            owner {
                                                avatarUrl
                                                login
                                            }
                                            stargazerCount
                                            viewerHasStarred
                                        }
                                    }
                                }',
                        variables: { nodeId: page.nodeId }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to fetch gist details"
                            notify.show(qsTrId("id-failed-to-fetch-gist-details"))
                            return
                        }

                        gist = result.node

                        if (filesModel.count > 0) filesModel.clear()
                        result.node.files.forEach(function(file) { filesModel.append(file) })
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
            //% "Loading data..."
            text: qsTrId("id-loading-data")
        }
    }

    SilicaFlickable {
        PullDownMenu {
            StarMenuItem {
                starred: gist.viewerHasStarred
                nodeId: page.nodeId
                onStargazerCountChanged: stargazerCountItem.count = stargazerCount
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                //% "Gist"
                title: qsTrId("id-gist")
                description: gist.name
            }

            // owner
            BackgroundItem {
                width: parent.width

                CircleImage {
                    id: avatarIcon
                    anchors {
                        left: parent.left
                        leftMargin: Theme.horizontalPageMargin
                        verticalCenter: parent.verticalCenter
                    }
                    width: parent.height * 0.75
                    height: width
                    source: gist.owner.avatarUrl
                }

                Label {
                    anchors {
                        left: avatarIcon.right
                        leftMargin: Theme.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }

                    text: gist.owner.login
                }

                onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), { nodeId: gist.owner.id })
            }

            // flags
            RepoFlagsItem {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                isFork: gist.isFork
                isPrivate: !gist.isPublic
            }

            // description
            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                text: MarkdownParser.parse(gist.description)
            }

            // counters
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                CounterItem {
                    property int count: gist.stargazerCount

                    id: stargazerCountItem
                    width: parent.width / 3
                    //% "%n star(s)"
                    title: qsTrId("id-stars-count", StringHelper.count(count))
                    icon: "image://theme/icon-m-favorite"
                    onClicked: {
                        if (count === 0) return;

                        pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                                   nodeId: nodeId,
                                                   itemsQueryType: "STARGAZERS",
                                                   //% "Stargazer"
                                                   title: qsTrId("id-stargazer"),
                                                   description: gist.name
                                              })
                    }
                }

                CounterItem {
                    width: parent.width / 3
                    //% "%n forks(s)"
                    title: qsTrId("id-forks-count", StringHelper.count(gist.forks.totalCount))
                    icon: "/usr/share/harbour-sailhub/icons/icon-m-fork.svg"
                    onClicked: {
                        if (gist.forks.totalCount === 0) return;

                        pageStack.push(Qt.resolvedUrl("GistListPage.qml"), {
                                                                   nodeId: nodeId,
                                                                   itemsQueryType: "GIST_FORKS",
                                                                   //% "Forks"
                                                                   title: qsTrId("id-forks"),
                                                                   description: gist.name
                                                                 })
                    }
                }

                CounterItem {
                    width: parent.width / 3
                    //% "%n comment(s)"
                    title: qsTrId("id-comments-count", StringHelper.count(gist.comments.totalCount))
                    icon: "image://theme/icon-s-chat"
                }
            }

            SectionHeader {
                //% "Files"
                text: qsTrId("id-files")
            }

            Repeater {
                model: ListModel { id: filesModel }
                delegate: GistFileDelegate {
                    onClicked: {
                        if (model.text === null) {
                            return
                        } else {
                            onClicked: pageStack.push(Qt.resolvedUrl("TextFileViewerPage.qml"), {
                                                          title: model.name,
                                                          //% "Gist"
                                                          description: qsTrId("id-gist") + ": " + gist.name,
                                                          text: model.text,
                                                          downloadAvailable: false
                                                      })
                        }

                        if (model.extension === ".md") {
                            onClicked: pageStack.push(Qt.resolvedUrl("MarkdownViewerPage.qml"), {
                                                          title: model.name,
                                                          //% "Gist"
                                                          description: qsTrId("id-gist") + ": " + gist.name,
                                                          body: model.text
                                                      })
                            return
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: refresh()
}



