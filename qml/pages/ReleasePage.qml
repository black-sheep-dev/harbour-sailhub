import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property string nodeId
    property Release release

    id: page
    allowedOrientations: Orientation.All

    QueryObject {
        id: query
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
                onClicked: {
                    SailHub.api().request(query)
                }
            }
        }

        anchors.fill: parent
        contentHeight: headerColumn.height

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

                text: query.result.name
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Label {
                    visible: query.result.isDraft
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#b71c1c"
                    //% "Draft"
                    text: qsTrId("id-draft")
                }

                Label {
                    visible: query.result.isLatest
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#64DD17"
                    //% "Latest release"
                    text: qsTrId("id-latest-release")
                }

                Label {
                    visible: query.result.isPrerelease
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#f29312"
                    //% "Pre-release"
                    text: qsTrId("id-pre-release")
                }
            }

            CommentItem {
                authorAvatar: query.result.author.avatarUrl
                authorLogin: query.result.author.login
                body: query.result.description
                timeSpan: new Date(query.result.publishedAt).toLocaleDateString(Qt.locale())
            }

            SectionHeader {
                //% "Info"
                text: qsTrId("id-info")
            }

            IconRelatedItem {
                title: query.result.tagCommit.abbreviatedOid
                icon: "image://theme/icon-m-swipe"
                showNextIcon: false
            }

            IconRelatedItem {
                title: query.result.tagName
                icon: "image://theme/icon-m-link"
                showNextIcon: false
            }

            SectionHeader {
                //% "Content"
                text: qsTrId("id-content")
            }

            RelatedValueItem {
                width: parent.width
                //% "Assets"
                label: qsTrId("id-assets")
                icon: "image://theme/icon-m-levels"
                value: query.result.releaseAssets.totalCount

                onClicked: pageStack.push(Qt.resolvedUrl("ReleaseAssetsListPage.qml"), {
                                              description: query.result.name,
                                              identifier: query.result.id
                                          })
            }

            RelatedValueItem {
                width: parent.width

                //% "Source code"
                label: qsTrId("id-source-code") + " (zip)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + query.result.repository.nameWithOwner + "/archive/refs/tags/" + query.result.tagName + ".zip")
            }

            RelatedValueItem {
                width: parent.width

                //% "Source code"
                label: qsTrId("id-source-code") + " (tar.gz)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + query.result.repository.nameWithOwner + "/archive/refs/tags/" + query.result.tagName + ".tar.gz")
            }
        }
    }

    Component.onCompleted: SailHub.api().request(query)
}
