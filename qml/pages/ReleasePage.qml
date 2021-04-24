import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"

Page {
    property bool busy: false
    property string nodeId
    property Release release

    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: page.busy
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    page.busy = true
                    SailHub.api().getRelease(page.nodeId)
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

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                title: qsTr("Release")
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
                    text: qsTr("Draft")
                }

                Label {
                    visible: release.isLatest
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#64DD17"
                    text: qsTr("Latest release")
                }

                Label {
                    visible: release.isPrerelease
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#f29312"
                    text: qsTr("Pre-release")
                }
            }

            CommentItem {
                authorAvatar: release.author.avatarUrl
                authorLogin: release.author.login
                body: release.description
                timeSpan: release.publishedAt.toLocaleDateString(Qt.locale())
            }

            SectionHeader {
                text: qsTr("Info")
            }

            IconRelatedItem {
                title: release.tagCommit
                icon: "image://theme/icon-m-swipe"
                showNextIcon: false
            }

            IconRelatedItem {
                title: release.tagName
                icon: "image://theme/icon-m-link"
                showNextIcon: false
            }

            SectionHeader {
                text: qsTr("Content")
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Assets")
                icon: "image://theme/icon-m-levels"
                value: release.assetCount

                onClicked: pageStack.push(Qt.resolvedUrl("ReleaseAssetsListPage.qml"), {
                                              description: release.name,
                                              identifier: release.nodeId
                                          })
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Source code") + " (zip)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + release.repository + "/archive/refs/tags/" + release.tagName + ".zip")
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Source code") + " (tar.gz)"
                icon: "image://theme/icon-m-file-archive-folder"
                showValue: false

                onClicked: Qt.openUrlExternally("https://github.com/" + release.repository + "/archive/refs/tags/" + release.tagName + ".tar.gz")
            }
        }
    }

    Connections {
        target: SailHub.api()
        onReleaseAvailable: {
            if (release.nodeId !== page.nodeId) return

            page.release = release;
            page.busy = false;
        }
    }

    Component.onCompleted: SailHub.api().getRelease(page.nodeId)
}
