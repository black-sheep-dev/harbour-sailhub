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

    configPath: "/app/harbour-sailhub/releases"

    orderField: "CREATED_AT"
    orderFields: ["CREATED_AT", "NAME"]
    orderFieldLabels: [
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Name"
        qsTrId("id-name")
    ]
    orderFieldType: "ReleaseOrderField = CREATED_AT"

    itemsPath: ["node", "releases", "nodes"]

    itemsQuery: '
    query(
        $nodeId: ID!,
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = DESC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on Repository {
                releases(
                    first: $itemCount,
                    after: $itemCursor,
                    orderBy: {
                        direction: $orderDirection
                        field: $orderField
                    }) {
                    nodes {
                        id
                        createdAt
                        isDraft
                        isLatest
                        isPrerelease
                        name
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
            //% "Releases"
            title: qsTrId("id-releases")
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
            MenuItem {
                //% "Sorting"
                text: qsTrId("id-sorting")
                onClicked: setSorting()
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No releases available"
            text: qsTrId("id-no-releases-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: ReleaseListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("ReleasePage.qml"), {
                                          nodeId: item.id
                                      })
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

