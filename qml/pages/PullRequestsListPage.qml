import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../components/"
import "../delegates/"
import "../views/"

ListPage {
    property bool canEditFilter: false
    property var pullRequestStates: ["OPEN"]

    property string login: ""

    property string nodeType
    property string nodes
    property string args: ""

    id: page
    allowedOrientations: Orientation.All

    configPath: "/app/harbour-sailhub/pull-requests"

    orderField: "UPDATED_AT"
    orderFields: ["CREATED_AT", "UPDATED_AT"]
    orderFieldLabels: [
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Updated at"
        qsTrId("id-updated-at")
    ]
    orderFieldType: "IssueOrderField = UPDATED_AT"

    itemsQuery: '
    query(
        ' + (login.length > 0 ? '$userLogin: String!' : '$nodeId: ID!') + ',
        $states: [PullRequestState!]!,
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = DESC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(' + (login.length > 0 ? 'login: $userLogin' : 'id: $nodeId') + ') {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    ' + args + '
                    first: $itemCount,
                    after: $itemCursor,
                    states: $states,
                    orderBy: {
                        direction: $orderDirection
                        field: $orderField
                    }) {
                    nodes {
                        id
                        author {
                            avatarUrl
                            login
                        }
                        closed
                        comments {
                            totalCount
                        }
                        createdAt
                        number
                        repository {
                            nameWithOwner
                        }
                        state
                        title
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
    itemsQueryVariables: {
        var vars = getDefaultQueryVariables()
        vars["states"] = pullRequestStates
        if (login.length > 0) vars["userLogin"] = login
        return vars
    }

    SilicaListView {
        PullDownMenu {
            busy: loading
            MenuItem {
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }
            MenuItem {
                text: {
                    if (pullRequestStates.indexOf("OPEN") >= 0)
                        //% "Show closed pull requests"
                        return qsTrId("id-show-closed-pull-requests")
                    else if (pullRequestStates.indexOf("CLOSED") >= 0)
                        //% "Show open pull requests"
                        return qsTrId("id-show-open-pull-request")
                }

                onClicked: {
                    if (pullRequestStates.indexOf("OPEN") >= 0)
                        pullRequestStates = ["CLOSED", "MERGED"]
                    else if (pullRequestStates.indexOf("CLOSED") >= 0)
                        pullRequestStates = ["OPEN"]

                    refresh()
                }
            }
            MenuItem {
                //% "Sorting"
                text: qsTrId("id-sorting")
                onClicked: setSorting()
            }
        }

        id: listView
        anchors.fill: parent
        spacing: Theme.paddingMedium

        header: PageHeader {
            //% "Pull requests"
            title: qsTrId("id-pull-requests")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        model: itemsModel

        delegate: PullRequestListDelegate {
            id: delegate
            onClicked: pageStack.push(Qt.resolvedUrl("PullRequestPage.qml"), {
                                          nodeId: model.id,
                                          description: model.repository.nameWithOwner
                                      })
        }

        ViewPlaceholder {
            enabled: !loading && listView.count === 0
            //% "No pull requests available"
            text: qsTrId("id-no-pull-requests-available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        switch (itemsQueryType) {
        case "REPOSITORY":
            nodeType = "Repository"
            nodes = "pullRequests"
            itemsPath = ["node", "pullRequests", "nodes"]
            break

        case "USER_CREATED":
            nodeType = "User"
            nodes = "pullRequests"
            itemsPath = ["node", "pullRequests", "nodes"]
            "filterBy: { createdBy: $userLogin },"
            break

        case "USER_ASSIGNED":
            nodeType = "User"
            nodes = "pullRequests"
            itemsPath = ["node", "pullRequests", "nodes"]
            args = "filterBy: { assignee: $userLogin },"
            break

        case "USER_MENTIONED":
            nodeType = "User"
            nodes = "pullRequests"
            itemsPath = ["node", "pullRequests", "nodes"]
            args = "filterBy: { mentioned: $userLogin },"
            pullRequestStates = ["OPEN", "MERGED", "CLOSED"]
            break

        case "LABEL":
            nodeType = "Label"
            nodes = "pullRequests"
            itemsPath = ["node", "pullRequests", "nodes"]
            pullRequestStates = ["OPEN", "MERGED", "CLOSED"]
            break

        default:
            break
        }

        refresh()
    }
}

