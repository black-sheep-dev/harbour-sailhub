import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."

Page {
    property string branch
    property string owner
    property string path
    property string repo
    property string repoId

    property bool loading: true
    property bool downloadAvailable: true

    property string title: repo
    property string description: branch + ":" + path
    property alias text: textArea.text


    function refresh() {
        loading = true
        Api.request({
                        query: 'query($nodeId: ID!, $branch: String!) {
                                    node(id: $nodeId) {
                                        ... on Repository {
                                            id
                                            object(expression: $branch) {
                                                ... on Blob {
                                                    byteSize
                                                    isBinary
                                                    text
                                                }
                                            }
                                        }
                                    }
                                }',
                        variables: {
                            nodeId: repoId,
                            branch: branch + ":" + path
                        }
                    },
                    function(result, status) {
                        loading = false

                        if (status !== 200) {
                            //% "Failed to load text file"
                            notify.show(qsTrId("id-failed-to-load-text-file"))
                            return
                        }

                        text = result.node.object.text
                    })
    }

    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        size: Theme.itemSizeLarge
        running: loading
    }

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                visible: downloadAvailable
                //% "Download"
                text: qsTrId("id-download")
                onClicked: Qt.openUrlExternally("https://github.com/" + owner + "/" + repo + "/raw/" + branch + "/" + path)
            }
            MenuItem {
                //% "Copy to clipboard"
                text: qsTrId("id-copy-to-clipboard")
                onClicked: Clipboard.text = textArea.text
            }
        }

        anchors.fill: parent
        contentHeight: header.height + textArea.height

        PageHeader {
            id: header
            title: page.title
            description: page.description
        }

        TextArea {
            id: textArea
            anchors {
                top: header.bottom
                bottom: parent.bottom
            }
            width: parent.width

            readOnly: true
            font.pixelSize: Theme.fontSizeSmall
            softwareInputPanelEnabled: false
        }
    }

    Component.onCompleted: if (text.length === 0) refresh()
}
