import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../components/"
import "../delegates/"
import "../queries/issue"
import "../views/"

ListPage {
    property bool canEditFilter: false
    property var issueStates: ["OPEN"]

    property string login: ""
    property string args: ""
    property string nodeData: ""

    property string nodeType
    property string nodes

    id: page
    allowedOrientations: Orientation.All

    configPath: "/app/harbour-sailhub/issues"

    orderField: "UPDATED_AT"
    orderFields: ["COMMENTS", "CREATED_AT", "UPDATED_AT"]
    orderFieldLabels: [
        //% "Comments"
        qsTrId("id-comments"),
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Updated at"
        qsTrId("id-updated-at")
    ]
    orderFieldType: "IssueOrderField = UPDATED_AT"

    itemsQuery: '
    query(
        $nodeId: ID!,
        ' + (login.length > 0 ? '$userLogin: String!,' : '') + '
        ' + (issueStates.length > 0 ? '$states: [IssueState!]!,' : '') + '
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = DESC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    ' + args + '
                    first: $itemCount,
                    after: $itemCursor,
                    ' + (issueStates.length > 0 ? 'states: $states,' : '') + '
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
        const vars = getDefaultQueryVariables()
        vars["states"] = issueStates
        if (login.length > 0) vars["userLogin"] = login
        return vars
    }


    CreateIssueMutation {
        id: createIssueMutation
        onResultChanged: refresh()
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
                //% "Sorting"
                text: qsTrId("id-sorting")
                onClicked: setSorting()
            }
            MenuItem {
                //% "Create new"
                text: qsTrId("id-create-new")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"))

                    dialog.accepted.connect(function() {
                        createIssueMutation.title = dialog.title
                        createIssueMutation.body = dialog.body
                        createIssueMutation.execute()
                    })
                }
            }
            MenuItem {
                visible: canEditFilter
                text: {
                    if (page.issueStates[0] === "OPEN") {
                        //% "Show closed issues"
                        return qsTrId("id-show-closed-issues")
                    } else if (page.issueStates[0] === "CLOSED") {
                        //% "Show open issues"
                        return qsTrId("id-show-open-issues")
                    }
                }

                onClicked: {
                    if (page.issueStates[0] === "OPEN") {
                        page.issueStates[0] = "CLOSED"
                    } else if (page.issueStates[0] === "CLOSED") {
                        page.issueStates[0] = "OPEN"
                    }

                    refresh()
                }
            }
        }

        id: listView
        anchors.fill: parent
        spacing: Theme.paddingMedium

        header: PageHeader {
            //% "Issues"
            title: qsTrId("id-issues")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        model: itemsModel

        delegate: IssueListDelegate {
            id: delegate
            onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), { nodeId: model.id })
        }

        ViewPlaceholder {
            enabled: listView.count == 0 && !loading
            //% "No issues available"
            text: qsTrId("id-no-issues-available")
        }

        VerticalScrollDecorator {}
    }

    onStatusChanged: if (status === PageStatus.Activating) refresh()

    Component.onCompleted: {
        switch (itemsQueryType) {
        case "REPOSITORY_ISSUES":
            nodeType = "Repository"
            nodes = "issues"
            itemsPath = ["node", "issues", "nodes"]
            break

        case "USER_CREATED_ISSUES":
            nodeType = "User"
            nodes = "issues"
            itemsPath = ["node", "issues", "nodes"]
            args = "filterBy: { createdBy: $userLogin },"
            break

        case "USER_ASSIGNED_ISSUES":
            nodeType = "User"
            nodes = "issues"
            itemsPath = ["node", "issues", "nodes"]
            args = "filterBy: { assignee: $userLogin },"
            break

        case "USER_MENTIONED_ISSUES":
            nodeType = "User"
            nodes = "issues"
            itemsPath = ["node", "issues", "nodes"]
            args = "filterBy: { mentioned: $userLogin },"
            issueStates = ["OPEN", "CLOSED"]
            break

        case "CLOSING_ISSUES_REFERENCES":
            nodeType = "PullRequest"
            nodes = "closingIssuesReferences"
            itemsPath = ["node", "closingIssuesReferences", "nodes"]
            issueStates = []
            break

        case "LABEL":
            nodeType = "Label"
            nodes = "issues"
            itemsPath = ["node", "issues", "nodes"]
            issueStates = ["OPEN", "CLOSED"]
            break

        default:
            break
        }
    }
}

