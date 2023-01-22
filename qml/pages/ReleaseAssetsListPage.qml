import QtQuick 2.0
import Sailfish.Silica 1.0

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
        PullDownMenu {
            busy: loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
        }

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

        model: itemsModel

        delegate: AssetListDelegate {
            id: delegate
            onClicked: Qt.openUrlExternally(model.downloadUrl)
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No assets available"
            text: qsTrId("id-no-assets-available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: refresh()
}

