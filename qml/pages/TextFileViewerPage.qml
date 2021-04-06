import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    property string branch
    property string owner
    property string path
    property string repo
    property string repoId

    property bool busy: true

    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        size: Theme.itemSizeLarge
        running: busy
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: header.height + textArea.height

        PageHeader {
            id: header
            title: repo
            description: branch + ":" +path
        }

        TextArea {
            id: textArea
            anchors.top: header.bottom
            anchors.bottom: page.bottom
            width: parent.width

            readOnly: true
            font.pixelSize: Theme.fontSizeSmall
            softwareInputPanelEnabled: false
        }
    }

    Connections {
        target: SailHub.api()
        onFileContentAvailable: {
            busy = false
            textArea.text = content
        }
    }

    Component.onCompleted: SailHub.api().getFileContent(repoId, branch + ":" + path)
}
