import QtQuick 2.0
import Sailfish.Silica 1.0

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
            title: page.title
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        model: itemsModel

        delegate: OrganizationListDelegate {
            id: delegate

            onClicked: pageStack.push(Qt.resolvedUrl("OrganizationPage.qml"), {
                                          nodeId: model.id
                                      })
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No organizations available"
            text: qsTrId("id-no-organizations-available")
        }

        VerticalScrollDecorator {}
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
