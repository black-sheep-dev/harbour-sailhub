import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../tools/"

Page {
    property string branch
    property string owner
    property string path
    property string repo
    property string repoId

    property bool busy: true

    property string body


    MarkdownParser {
        id: markdownParser
    }

    function parseContent() {
        var convertedText = markdownParser.parse(body)

        const url = "https://github.com/" + owner + "/" + repo + "/raw/" + branch + "/"

        bodyLabel.text = convertedText.replace(/src="(?!http)/gmi, "src=\"" + url)
    }

    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        size: Theme.itemSizeLarge
        running: busy
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: header.height + bodyLabel.height

        PageHeader {
            id: header
            title: repo
            description: branch + ":" +path
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
    }

    Connections {
        target: SailHub.api()
        onFileContentAvailable: {
            busy = false
            body = content
            parseContent()
        }
    }

    Component.onCompleted: SailHub.api().getFileContent(repoId, branch + ":" + path)
}
