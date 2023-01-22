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

        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: page.title
            description: page.description
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

    Component.onCompleted: { 
        configPath = "/apps/harbour-sailhub/repos"
        orderFields = ["NAME", "CREATED_AT", "PUSHED_AT", "UPDATED_AT", "STARGAZERS"]
        orderFieldLabels = [
            //% "Name"
            qsTrId("id-name"),
            //% "Created at"
            qsTrId("id-created-at"),
            //% "Pushed at"
            qsTrId("id-pushed-at"),
            //% "Updated at"
            qsTrId("id-updated-at"),
            //% "Stargazers"
            qsTrId("id-stargazers")
        ]
        orderFieldType = "RepositoryOrderField = NAME"

        itemsPath = ["node", "repositories", "nodes"]

        switch (itemsQueryType) {
        case "STARRED_REPOS":
            nodeType = "User"
            nodes = "starredRepositories"
            itemsPath = ["node", "starredRepositories", "nodes"]

            configPath = "/apps/harbour-sailhub/starred-repositories"
            orderFields = ["STARRED_AT"]
            //% "Starred at"
            orderFieldLabels = [qsTrId("id-starred-at")]
            orderFieldType = "StarOrderField = STARRED_AT"
            break

        case "USER_REPOS":
            nodeType = "User"
            nodes = "repositories"
            break

        case "ORGANIZATION_REPOS":
            nodeType = "Organization"
            nodes = "repositories"
            break

        case "FORKS":
            nodeType = "Repository"
            nodes = "forks"
            itemsPath = ["node", "forks", "nodes"]
            break

        default:
            break
        }

        refresh()
    }
}
