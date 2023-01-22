import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../components/"

Page {
    property string nodeId
    property var label
    property bool loading: true

    function refresh() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!) {
                                    node(id: $nodeId) {
                                        ... on Label {
                                            id
                                            description
                                            issues {
                                                totalCount
                                            }
                                            name
                                            pullRequests {
                                                totalCount
                                            }
                                        }
                                    }
                                }',
                        variables: { nodeId: page.nodeId }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to fetch label details"
                            notify.show(qsTrId("id-failed-to-fetch-label-details"))
                            return
                        }

                        label = result.node
                    })
    }


    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        anchors.centerIn: page
        running: loading

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

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                //% "Label"
                title: qsTrId("id-label")
                description: label.name
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                color: Theme.highlightColor
                text: label.description
            }

            SectionHeader {
                //% "Related"
                text: qsTrId("id-related")
            }

            RelatedValueItem {
                width: parent.width
                //% "Issues"
                label: qsTrId("id-issues")
                value: page.label.issues.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-issue.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("IssuesListPage.qml"), {
                                               nodeId: nodeId,
                                               itemsQueryType: "LABEL",
                                               canEditFilter: true,
                                               //% "Label"
                                               description: qsTrId("id-label") + " : " + page.label.name,
                                          })
            }
            RelatedValueItem {
                width: parent.width
                //% "Pull requests"
                label: qsTrId("id-pull-requests")
                value: page.label.pullRequests.totalCount
                icon: "/usr/share/harbour-sailhub/icons/icon-m-pull-request.svg"
                onClicked: pageStack.push(Qt.resolvedUrl("PullRequestsListPage.qml"), {
                                              nodeId: nodeId,
                                              //% "Label"
                                              description: qsTrId("id-label") + " : " + page.label.name,
                                              itemsQueryType: "LABEL"
                                          })
            }
        }
    }

    Component.onCompleted: refresh()
}


