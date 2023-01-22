import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"
import "../delegates/"
import "../tools/"
import "../views/"
import "../."

ListPage {
    property string nodeType
    property string nodes

    id: page
    allowedOrientations: Orientation.All

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
                        isArchived
                        isDisabled
                        isEmpty
                        isFork
                        isInOrganization
                        isLocked
                        isMirror
                        isPrivate
                        isTemplate
                        lockReason
                        name
                        owner {
                            avatarUrl
                            login
                        }
                        primaryLanguage {
                            color
                            name
                        }
                        shortDescriptionHTML
                        stargazerCount
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
                //% "Search"
                text: qsTrId("id-search")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SearchDialog.qml"))
                    dialog.accepted.connect(function() {

                    })
                }
            }
        }

        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Search"
            title: qsTrId("id-search")
            description: "TODO"
        }

        spacing: Theme.paddingMedium
        model: itemsModel
        onAtYEndChanged: if (atYEnd && hasNextPage) loadMore()

        opacity: loading ? 0.4 : 1
        Behavior on opacity { FadeAnimation {} }

        delegate: RepoListDelegate {
            onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                          nodeId: model.id
                                      })

        }

        ViewPlaceholder {
            enabled: listView.count == 0 && !loading
            //% "No repositories available"
            text: qsTrId("id-no-repositories-available")
        }

        VerticalScrollDecorator {}
    }
}
