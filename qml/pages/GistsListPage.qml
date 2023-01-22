import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../components/"
import "../views/"
import "../delegates/"

ListPage {
    property string nodeType: "User"
    property string nodes: "gists"

    id: page
    allowedOrientations: Orientation.All

    configPath: "/app/harbour-sailhub/gists"

    orderDirection: "DESC"
    orderField: "UPDATED_AT"
    orderFields: ["PUSHED_AT", "CREATED_AT", "UPDATED_AT"]
    orderFieldLabels: [
        //% "Pushed at"
        qsTrId("id-pushed-at"),
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Updated at"
        qsTrId("id-updated-at"),
    ]
    orderFieldType: "GistOrderField = UPDATED_AT"

    itemsPath: ["node", "gists", "nodes"]

    itemsQuery: '
    query(
        $nodeId: ID!,
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = DESC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    privacy: ALL,
                    first: $itemCount,
                    after: $itemCursor,
                    orderBy: {
                        direction: $orderDirection
                        field: $orderField
                    }) {
                    nodes {
                        id
                        comments {
                            totalCount
                        }
                        createdAt
                        description
                        files {
                            isTruncated
                        }
                        forks {
                            totalCount
                        }
                        isPublic
                        owner {
                            avatarUrl
                            login
                        }
                        pushedAt
                        stargazerCount
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
        spacing: Theme.paddingMedium

        header: PageHeader {
            //% "Gists"
            title: qsTrId("id-gists")
            description: page.description
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
            //% "No gists available"
            text: qsTrId("id-no-gists-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: GistListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("GistPage.qml"), {
                                          nodeId: model.id
                                      })

        }

        onAtYEndChanged: if (atYEnd) loadMore()
    }

    Component.onCompleted: {
        switch (itemsQueryType) {
        case "GIST_FORKS":
            nodeType = "Gist"
            nodes = "forks"
            itemsPath: ["node", "forks", "nodes"]
            break

        default:
            break
        }

        refresh()
    }
}

