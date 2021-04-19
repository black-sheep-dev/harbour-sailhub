import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../js/showdown.js" as ShowDown

Page {
    property string branch
    property string owner
    property string path
    property string repo
    property string repoId

    property bool busy: true

    property string body

    property var showdown: ShowDown.showdown
    property var converter: new showdown.Converter({
                                    simplifiedAutoLink: true,
                                    excludeTrailingPunctuationFromURLs: true,
                                    strikethrough: true,
                                    tables: true,
                                    tasklists: false,
                                    parseImgDimensions: true,
                                    simpleLineBreaks: true,
                                    emoji: true })

    function parseContent() {
        var convertedText = converter.makeHtml(body)

        bodyLabel.text = "<style>\n" +
                "ul,ol,table,img { margin: " + Theme.paddingLarge + "px 0px; }\n" +
                "a:link { color: " + Theme.primaryColor + "; }\n" +
                "a.checkbox { text-decoration: none; padding: " + Theme.paddingSmall + "px; display: inline-block; }\n" +
                "li.tasklist { font-size:large; margin: " + Theme.paddingMedium + "px 0px; }\n" +
                "del { text-decoration: line-through; }\n" +
                "table { border-color: " + Theme.secondaryColor + "; }\n" +
                "</style>\n" + convertedText + "<br><br>"
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
            linkColor: Theme.highlightColor
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
