import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../views/"

ListPage {
    id: page
    allowedOrientations: Orientation.All

    itemsQuery: '
    query(
        $nodeId: ID!,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on Release {
                releaseAssets(
                    first: $itemCount,
                    after: $itemCursor
                ) {
                    nodes {
                        id
                        contentType
                        createdAt
                        downloadCount
                        downloadUrl
                        name
                        size
                        updatedAt
                    }
                    totalCount
                    pageInfo {
                        hasNextPage
                        endCursor
                    }
                }
            }
        }
    }'

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            id: header
            //% "Release assets"
            title: qsTrId("id-release-assets")
            description: description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No assets available"
            text: qsTrId("id-no-assets-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: AssetListDelegate {
            id: delegate

            menu: ContextMenu {
                MenuItem {
                    //% "Download"
                    text: qsTrId("id-download")
                    //% "Starting download"
                    onClicked: delegate.remorseAction(qsTrId("id-starting-download"), function() { Qt.openUrlExternally(item.downloadUrl) })
                }
            }
        }

        PushUpMenu {
            busy: loading
            visible: hasNextPage

            MenuItem {
                enabled: !loading
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more", totalCount - listView.count)
                onClicked: loadMore()
            }
        }
    }

    Component.onCompleted: refresh()
}

