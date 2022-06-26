import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property string nodeId
    property alias release: query.result

    id: page
    allowedOrientations: Orientation.All

    function refresh() { Api.request(query) }

    QueryObject {
        id: query
        resultNodePath: "node"
        query: '
            query($nodeId: ID!) {
                node(id: $nodeId) {
                    ... on Release {
                        id
                        author {
                            avatarUrl
                            login
                        }
                        description
                        isDraft
                        isLatest
                        isPrerelease
                        name
                        publishedAt
                        releaseAssets {
                            totalCount
                        }
                        repository {
                            nameWithOwner
                        }
                        tagCommit {
                           abbreviatedOid
                        }
                        tagName
                    }
                }
            }'
        variables: {
            "nodeId": page.nodeId
        }

        onErrorChanged: notification.showErrorMessage(error)
    }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: !query.ready

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
            busy: !query.ready
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height

        opacity: !query.ready ? 0.0 : 1.0
        Behavior on opacity { FadeAnimation {} }

        RemorsePopup { id: remorse }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            PageHeader {
                //% "Release"
                title: qsTrId("id-release")
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor

                text: release.name
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Label {
                    visible: release.isDraft
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#b71c1c"
                    //% "Draft"
                    text: qsTrId("id-draft")
                }

                Label {
                    visible: release.isLatest
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#64DD17"
                    //% "Latest release"
                    text: qsTrId("id-latest-release")
                }

                Label {
                    visible: release.isPrerelease
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#f29312"
                    //% "Pre-release"
                    text: qsTrId("id-pre-release")
                }
            }

            CommentItem {
                authorAvatar: release.author.avatarUrl
                authorLogin: release.author.login
                body: release.description
                timeSpan: new Date(release.publishedAt).toLocaleDateString(Qt.locale())
            }

            SectionHeader {
                //% "Info"
                text: qsTrId("id-info")
            }

            IconRelatedItem {
                title: release.tagCommit.abbreviatedOid
                icon: "image://theme/icon-m-swipe"
                showNextIcon: false
            }

            IconRelatedItem {
                title: release.tagName
                icon: "image://theme/icon-m-link"
                showNextIcon: false
            }

            SectionHeader {
                //% "Content"
                text: qsTrId("id-content")
            }

            RelatedValueItem {
                enabled: release.releaseAssets.totalCount > 0
                width: parent.width
                //% "Assets"
                label: qsTrId("id-assets")
                icon: "image://theme/icon-m-levels"
                value: release.releaseAssets.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("ReleaseAssetsListPage.qml"), {
                                              nodeId: nodeId,
                                              description: release.name
                                          })
            }

            RelatedValueItem {
                width: parent.width

                //% "Source code"
                label: qsTrId("id-source-code") + " (zip)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + release.repository.nameWithOwner + "/archive/refs/tags/" + release.tagName + ".zip")
            }

            RelatedValueItem {
                width: parent.width

                //% "Source code"
                label: qsTrId("id-source-code") + " (tar.gz)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + release.repository.nameWithOwner + "/archive/refs/tags/" + release.tagName + ".tar.gz")
            }
        }
    }

    Component.onCompleted: refresh()
}
