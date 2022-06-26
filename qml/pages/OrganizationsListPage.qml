import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../views/"

ListPage {
    property string nodeType
    property string nodes

    id: page
    allowedOrientations: Orientation.All

    itemsQuery: '
    query(
        $nodeId: ID!,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    first: $itemCount,
                    after: $itemCursor
                ) {
                    nodes {
                        id
                        avatarUrl
                        description
                        login
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
            title: page.title
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
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No organizations available"
            text: qsTrId("id-no-organizations-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: OrganizationListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("OrganizationPage.qml"), {
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


    Component.onCompleted: {
        switch (itemsQueryType) {
        case "USER_ORGANIZATIONS":
            nodeType = "User"
            nodes = "organizations"
            itemsPath = ["node", "organizations", "nodes"]
            break

        default:
            break
        }

        refresh()
    }
}
