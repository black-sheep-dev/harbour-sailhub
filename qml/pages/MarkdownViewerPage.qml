import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."

Page {
    property string branch
    property string owner
    property string path
    property string repo
    property string repoId 

    property bool loading: false

    property string title: repo
    property string description: branch + ":" + path
    property string body

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
                            //% "Failed to load markdown file"
                            notify.show(qsTrId("id-failed-to-load-markdown-file"))
                            return
                        }

                        body = result.node.object.text
                    })
    }

    function parseContent() {
        var convertedText = MarkdownParser.parse(body)
        const url = "https://github.com/" + owner + "/" + repo + "/raw/" + branch + "/"
        bodyLabel.text = convertedText.replace(/src="(?!http)/gmi, "src=\"" + url)
    }

    onBodyChanged: parseContent()

    id: page
    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        size: Theme.itemSizeLarge
        running: loading

        Label {
            anchors {
                top: parent.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            color: Theme.highlightColor
            //% "Loading file..."
            text: qsTrId("id-loading-file")
        }
    }

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                //% "Copy to clipboard"
                text: qsTrId("id-copy-to-clipboard")
                onClicked: Clipboard.text = bodyLabel.text
            }
        }

        anchors.fill: parent
        contentHeight: spacer.y + spacer.height

        PageHeader {
            id: header
            title: page.title
            description: page.description
        }

        LinkedLabel {
            id: bodyLabel
            anchors.top: header.bottom
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
            textFormat: Text.RichText

            onLinkActivated: Qt.openUrlExternally(link)
        }

        Item {
            id: spacer
            anchors.top: bodyLabel.bottom
            width: 1
            height: Theme.paddingLarge
        }
    }

    Component.onCompleted: if (body.length === 0) refresh()
}
