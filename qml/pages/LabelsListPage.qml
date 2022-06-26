import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../views/"

ListPage {
    property string nodeType
    property string nodes

    id: page
    allowedOrientations: Orientation.All

    configPath: "/app/harbour-sailhub/labels"

    orderField: "NAME"
    orderFields: ["CREATED_AT", "NAME"]
    orderFieldLabels: [
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Name"
        qsTrId("id-name")
    ]
    orderFieldType: "LabelOrderField = NAME"

    nodes: "labels"

    itemsQuery: '
    query(
        $nodeId: ID!,
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = ASC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    first: $itemCount,
                    after: $itemCursor,
                    orderBy: {
                        direction: $orderDirection
                        field: $orderField
                    }) {
                    nodes {
                        id
                        color
                        createdAt
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
            //% "Labels"
            title: qsTrId("id-labels")
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
            //% "No labels available"
            text: qsTrId("id-no-labels-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: LabelListDelegate {}

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

