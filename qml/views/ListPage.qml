import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../."

Page {
    property alias configPath: config.path 
    property bool loading: true

    // components
    property string description
    property string title
    property bool showBusyIndicator: true

    // user permissions
    property bool canFilter: true
    property bool canSort: true

    // query model related properties
    property string nodeId
    property var itemsModel: ListModel {}
    property string itemsQuery
    property string itemsQueryType: ""
    property var itemsQueryVariables: undefined
    property var itemsPath: []
    property var itemSubPath: []

    // pagination
    property int paginationCount: 0

    // sorting
    property alias orderField: config.orderField
    property var orderFields: []
    property var orderFieldLabels: []
    property string orderFieldType: ""
    property alias orderDirection: config.orderDirection

    // filtering

    // page info
    property bool hasNextPage: false
    property var endCursor: null
    property int totalCount: 0

    // functions
    function refresh() {
        if (itemsModel.count !== 0) itemsModel.clear()
        endCursor = null
        hasNextPage = false
        totalCount = 0

        sendRequest()
    }

    function loadMore() {
        if (hasNextPage) sendRequest()
    }

    function sendRequest() {
        loading = true
        Api.request({
                        query: itemsQuery.replace(/[\n\r] +(?= )/g, ''),
                        variables: itemsQueryVariables === undefined ? getDefaultQueryVariables() : itemsQueryVariables
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(result))
                            //% "Failed to load items"
                            notify.show(qsTrId("id-failed-to-load-items"))
                            return
                        }

                        var arr = result

                        for (var i=0; i < itemsPath.length; i++) {
                            arr = arr[itemsPath[i]]

                            if (i === itemsPath.length - 2) {
                                if (arr.hasOwnProperty("totalCount")) totalCount = arr.totalCount
                                if (arr.hasOwnProperty("pageInfo")) setPageInfo(arr.pageInfo)
                            }
                        }

                        arr.forEach(function(item) {
                            var entity = item
                            for (var i=0; i < itemSubPath.length; i++) {
                                entity = entity[itemSubPath[i]]
                            }
                            itemsModel.append(entity) }
                        )
                    })
    }

    function setSorting() {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                        direction: orderDirection,
                                        field: orderField,
                                        fields: orderFields,
                                        fieldLabels: orderFieldLabels
                                    })

        dialog.accepted.connect(function() {
            orderField = dialog.field
            orderDirection = dialog.direction

            refresh()
        })
    }

    function setPageInfo(data) {
        hasNextPage = data.hasNextPage
        endCursor = data.endCursor
    }

    function getDefaultQueryVariables() {
        const vars = {}

        vars["nodeId"] = nodeId
        if (orderFields.length > 0) {
            if (orderField.length > 0) vars["orderField"] = orderField
            vars["orderDirection"] = orderDirection
        }
        vars["itemCount"] =  paginationCount > 0 ? paginationCount : settings.paginationCount

        if (endCursor !== null) vars["itemCursor"] = endCursor

        return vars
    }

    id: page
    allowedOrientations: Orientation.All

    ConfigurationGroup {
        id: config

        synchronous: true
        property string orderField: ""
        property string orderDirection: "ASC"
    }

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: loading && showBusyIndicator

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            text: loading && itemsModel.count === 0 ?
                      //% "Loading data..."
                      qsTrId("id-loading-data") :
                      //% "Loading more..."
                      qsTrId("id-loading-more")
        }
    }
}
