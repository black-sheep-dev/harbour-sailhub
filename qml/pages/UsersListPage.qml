import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../views/"
import "../queries/assignee"

ListPage {
    property string nodeType
    property string nodes
    property string args: ""
    property bool viewerCanUpdate: false

    id: page
    allowedOrientations: Orientation.All

    configPath: "/apps/harbour-sailhub/users"

    itemsQuery: '
    query(
        $nodeId: ID!,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' {
                ' + nodes + '(
                    ' + args + '
                    first: $itemCount,
                    after: $itemCursor
                ) {
                    nodes {
                        id
                        avatarUrl
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

    AddAssigneesMutation {
        id: addAssigneesMutation
    }

    RemoveAssigneesMutation {
        id: remov
    }

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
            MenuItem {
                visible: (itemsQueryType === "ISSUE_ASSIGNEES" || itemsQueryType === "PULL_REQUEST_ASSIGNEES") && viewerCanUpdate
                //% "Assign user"
                text: qsTrId("id-assign-user")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/AssignUserDialog.qml"), { repoId: page.repoId })

                    dialog.accepted.connect(function() {
                        if (dialog.selected.lenth === 0) return

                        SailHub.api().assignUsers(usersModel.identifier, dialog.selected)
                    })
                }
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0 && !loading
            //% "No users available"
            text: qsTrId("id-no-users-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: UserListDelegate {
            id: delegate
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            onClicked: pageStack.push(Qt.resolvedUrl("UserPage.qml"), { nodeId: item.id })
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
        case "FOLLOWERS":
            nodeType = "User"
            nodes = "followers"
            itemsPath = ["node", "followers", "nodes"]
            break

        case "FOLLOWING":
            nodeType = "User"
            nodes = "following"
            itemsPath = ["node", "following", "nodes"]
            break

        case "WATCHERS":
            nodeType = "Repository"
            nodes = "watchers"
            itemsPath = ["node", "watchers", "nodes"]
            break

        case "STARGAZERS":
            nodeType = "Repository"
            nodes = "stargazers"
            itemsPath = ["node", "stargazers", "nodes"]
            break

        case "COLLABORATORS":
            nodeType = "Repository"
            nodes = "collaborators"
            itemsPath = ["node", "collaborators", "nodes"]
            args = "affiliation: ALL,"
            break

        case "ISSUE_PARTICIPANTS":
            nodeType = "Issue"
            nodes = "participants"
            itemsPath = ["node", "participants", "nodes"]
            break

        case "PULL_REQUEST_PARTICIPANTS":
            nodeType = "PullRequest"
            nodes = "participants"
            itemsPath = ["node", "participants", "nodes"]
            break

        case "ISSUE_ASSIGNEES":
            nodeType = "Issue"
            nodes = "assignees"
            itemsPath = ["node", "assignees", "nodes"]
            break

        case "PULL_REQUEST_ASSIGNEES":
            nodeType = "PullRequest"
            nodes = "assignees"
            itemsPath = ["node", "assignees", "nodes"]
            break

        case "ORGANIZATION_MEMBERS":
            nodeType = "Organization"
            nodes = "membersWithRole"
            itemsPath = ["node", "membersWithRole", "nodes"]
            break

        default:
            break

        }

        refresh()
    }
}
