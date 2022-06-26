import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import ".."

Page {
    property alias configPath: config.path
    property string description
    property bool loading: !query.ready
    property string title
    property bool showBusyIndicator: true

    // user permissions
    property bool canFilter: true
    property bool canSort: true

    // query model related properties
    property string nodeId
    property alias itemsQuery: query.query
    property string itemsQueryType: ""
    property alias itemsQueryVariables: query.variables
    property var itemsPath: []
    property var itemsModel: ArrayModel { }
    property alias queryResult: query.result

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
        itemsModel.clear()
        endCursor = null
        hasNextPage = false
        totalCount = 0
        Api.request(query)
    }

    function loadMore() {
        Api.request(query)
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

    QueryObject {
        id: query
        variables: getDefaultQueryVariables()
        onReadyChanged: {
            if (error !== QueryObject.ErrorNone) return

            var arr = result

            for (var i=0; i < itemsPath.length; i++) {
                arr = arr[itemsPath[i]]

                if (i === itemsPath.length - 2) {
                    if (arr.hasOwnProperty("totalCount")) totalCount = arr.totalCount
                    if (arr.hasOwnProperty("pageInfo")) setPageInfo(arr.pageInfo)
                }
            }

            itemsModel.addItems(arr)
        }

        onErrorChanged: if (error !== QueryObject.ErrorNone) notification.showErrorMessage(error)
    }

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
        running: loading && itemsModel.count === 0 && showBusyIndicator

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            //% "Loading data..."
            text: qsTrId("id-loading-data")
        }
    }
}
