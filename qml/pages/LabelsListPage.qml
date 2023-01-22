import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../components/"
import "../delegates/"
import "../dialogs/"
import "../queries/"
import "../views/"

ListPage {
    property string nodeType
    property string nodes: "labels"
    property string repoId
    property bool viewerCanAssign: false

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

    itemsPath: ["node", "labels", "nodes"]

    itemsQuery: '
    query(
        $nodeId: ID!,
        $orderField: ' + orderFieldType + ',
        $orderDirection: OrderDirection = ASC,
        $itemCount: Int = 20,
        $itemCursor: String = null
    ) {
        node(id: $nodeId) {
            ... on ' + nodeType + ' { '
                + nodes + '(
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
                        repository {
                            id
                        }
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

    AddLabelsToLabelableMutation {
        id: addLabelsToLabelableMutation
        nodeId: page.nodeId
    }
    RemoveLabelsFromLabelableMutation {
        id: removeLabelsFromLabelableMutation
        nodeId: page.nodeId
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        spacing: Theme.paddingLarge

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
            MenuItem {
                visible: viewerCanAssign
                //% "Assign"
                text: qsTrId("id-assign")
                onClicked: {
                    const labelIds = []
                    for (var i=0; i < itemsModel.count; i++) {
                        labelIds.push(itemsModel.get(i).id)
                    }

                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/AssingLabelsToLabelableDialog.qml"), {
                                                    nodeId: nodeId,
                                                    repoId: repoId,
                                                    labelIds: labelIds
                                                })

                    dialog.accepted.connect(function() {
                        const deselected = []
                        dialog.labelIds.forEach(function(labelId) {
                            if (dialog.selectedLabelIds.indexOf(labelId) < 0) deselected.push(labelId)
                        })
                        if (deselected.length > 0) {
                            removeLabelsFromLabelableMutation.labelIds = deselected
                            removeLabelsFromLabelableMutation.execute()
                        }

                        const selected = []
                        dialog.selectedLabelIds.forEach(function(labelId) {
                            if (labelIds.indexOf(labelId) < 0) selected.push(labelId)
                        })
                        if (selected.length > 0) {
                            addLabelsToLabelableMutation.labelIds = selected
                            addLabelsToLabelableMutation.execute()
                        }
                    })
                }
            }
        }

        ViewPlaceholder {
            enabled: !loading && listView.count === 0
            //% "No labels available"
            text: qsTrId("id-no-labels-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        opacity: loading ? 0.0 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: LabelListDelegate {
            id: delegate

            menu: ContextMenu {
                MenuItem {
                    visible: viewerCanAssign
                    //% "Remove"
                    text: qsTrId("id-remove")
                    //% "Removing label"
                    onClicked: delegate.remorseAction(qsTrId("id-removing-label"), function() {
                        const removeId = []
                        removeId.push(model.id)
                        removeLabelsFromLabelableMutation.labelIds = removeId
                        removeLabelsFromLabelableMutation.execute()
                        itemsModel.remove(index)
                    })
                }
            }

            onClicked: pageStack.push(Qt.resolvedUrl("LabelPage.qml"), { nodeId: model.id })
        }

        onAtYEndChanged: if (atYEnd) loadMore()
    }

    onStatusChanged: if (status === PageStatus.Active) refresh()
}

