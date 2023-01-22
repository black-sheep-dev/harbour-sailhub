import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../delegates/"

Dialog {
    property string nodeId
    property string repoId
    property var labelIds: []
    property var selectedLabelIds: []

    // page info
    property bool hasNextPage: false
    property var endCursor: null
    property int totalCount: 0

    function getQueryVariables() {
        const vars = {}
        vars["nodeId"] = repoId
        vars["itemCount"] = settings.paginationCount
        if (endCursor !== null) vars["itemCursor"] = endCursor
        return vars
    }

    function refresh() {
        if (listModel.count !== 0) listModel.clear()
        endCursor = null
        hasNextPage = false
        totalCount = 0

        sendRequest()
    }

    function loadMore() {
        if (hasNextPage) sendRequest()
    }

    function sendRequest() {
        listView.loading = true
        Api.request({
                        query: 'query(
                                    $nodeId: ID!,
                                    $orderField: LabelOrderField = NAME,
                                    $orderDirection: OrderDirection = ASC,
                                    $itemCount: Int = 20,
                                    $itemCursor: String = null
                                ) {
                                    node(id: $nodeId) {
                                        ... on Repository {
                                            labels (
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
                                }',
                        variables: getQueryVariables()
                    },
                    function(result, status) {
                        listView.loading = false

                        if (status !== 200) {
                            //% "Failed to load labels"
                            notify.show(qsTrId("id-failed-to-load-labels"))
                            return
                        }

                        result.node.labels.nodes.forEach(function(item) { listModel.append(item) })
                    })
    }

    id: dialog

    canAccept: labelIds.length !== selectedLabelIds.length

    DialogHeader {
        id: header
        anchors {
            top: parent.top
        }

        //% "Assign labels"
        title: qsTrId("id-assign-labels")
    }

    SilicaListView {
        property bool loading: true

        id: listView
        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: parent.bottom
        }

        model: ListModel { id: listModel }
        delegate: LabelListDelegate {
            id: delegate

            Icon {
                visible: selectedLabelIds.indexOf(model.id) >= 0
                anchors {
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                    verticalCenter: parent.verticalCenter
                }
                source: "image://theme/icon-m-acknowledge"
            }

            onClicked: {
                var arr = selectedLabelIds
                if (arr.indexOf(model.id) >= 0) {
                    arr.splice(arr.indexOf(model.id), 1)
                } else {
                    arr.push(model.id)
                }
                selectedLabelIds = arr
            }
        }

        onAtYEndChanged: if (atYEnd) loadMore()

        ViewPlaceholder {
            enabled: !listView.loading && listView.count === 0
            //% "No labels available"
            text: qsTrId("id-no-labels-available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        selectedLabelIds = selectedLabelIds.concat(labelIds)
        refresh()
    }
}

