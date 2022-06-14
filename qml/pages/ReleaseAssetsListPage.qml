import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: assetsModel.identifier

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            id: header
            //% "Release assets"
            title: qsTrId("id-release-assets")
            description: header.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: assetsModel.loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: {
                    refresh()
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: assetsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No assets available"
            text: qsTrId("id-no-assets-available")
        }

        VerticalScrollDecorator {}

        model: ReleaseAssetsModel { id: assetsModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: AssetListDelegate {
            id: delegate

            menu: ContextMenu {
                MenuItem {
                    //% "Download"
                    text: qsTrId("id-download")
                    //onClicked: SailHub.api().downloader().download(model.downloadUrl, model.name)
                    onClicked: Qt.openUrlExternally(model.downloadUrl)
                }
            }

            Connections {
                target: SailHub.api().downloader()
                onDownloadProgress: if (url === model.downloadUrl) delegate.downloadProgress = percentage
                onFinished: if (url === model.downloadUrl) delegate.downloadProgress = 100
            }
        }

        PushUpMenu {
            busy: assetsModel.loading
            visible: assetsModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", assetsModel.totalCount - listView.count)
                onClicked: getAssets()
            }
        }
    }

    function getAssets() {
        SailHub.api().getPaginationModel(assetsModel)
    }

    function refresh() {
        assetsModel.reset()
        getAssets()
    }

    Connections {
        target: SailHub.api()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete assetsModel
}

