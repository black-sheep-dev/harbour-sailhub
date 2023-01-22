import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../components/"
import "../views/"
import "../delegates/"

ListPage {
    id: page
    allowedOrientations: Orientation.All

    configPath: "/app/harbour-sailhub/discussions"

    orderField: "UPDATED_AT"
    orderFields: ["CREATED_AT", "UPDATED_AT"]
    orderFieldLabels: [
        //% "Created at"
        qsTrId("id-created-at"),
        //% "Updated at"
        qsTrId("id-updated-at")
    ]
    orderFieldType: "DiscussionOrderField = UPDATED_AT"

    itemsPath: ["node", "discussions", "nodes"]

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
                discussions(
                    first: $itemCount,
                    after: $itemCursor,
                    orderBy: {
                        direction: $orderDirection
                        field: $orderField
                    }) {
                    nodes {
                        id
                        activeLockReason
                        author {
                            avatarUrl
                            login
                        }
                        category {
                            emojiHTML
                            name
                        }
                        comments {
                            totalCount
                        }
                        createdAt
                        locked
                        title
                        updatedAt
                        upvoteCount
                        viewerCanDelete
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
            //% "Discussions"
            title: qsTrId("id-discussions")
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

            MenuItem {
                //% "Start new"
                text: qsTrId("id-start-new-discussion")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectDiscussionCategoryDialog.qml"), {
                                                    repoId: identifier
                                                })

                    dialog.accepted.connect(function() {
                        var dialogContent = pageStack.push(Qt.resolvedUrl("../dialogs/EditDiscussionDialog.qml"), {
                                                               acceptDestination: page,
                                                               acceptDestinationAction: PageStackAction.Pop,
                                                               edit: false
                                                           })
                        dialogContent.accepted.connect(function() {
                            SailHub.api().createDiscussion(dialogContent.title, dialogContent.body, dialog.selected, discussionsModel)
                        })
                    })
                }
            }
        }

        ViewPlaceholder {
            enabled: !loading && listView.count == 0
            //% "No discussions available"
            text: qsTrId("id-no-discussions-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        delegate: DiscussionListDelegate {
            id: delegate

            menu: ContextMenu {
                visible: model.viewerCanDelete
                MenuItem {
                    //% "Delete"
                    text: qsTrId("id-delete")
                    //% "Deleting discussion"
                    onClicked: delegate.remorseAction(qsTrId("id-deleting-discussion"), function() {
                        //SailHub.api().deleteDiscussion(item.id)
                    })
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl("DiscussionPage.qml"), {
                                          nodeId: model.id
                                      })
        }

        onAtYEndChanged: if (atYEnd) loadMore()
    }

    Component.onCompleted: refresh()
}

