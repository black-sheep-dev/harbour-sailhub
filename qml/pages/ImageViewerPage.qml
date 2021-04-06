import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    property string branch
    property string owner
    property string path
    property string repo

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: repo
                description: branch + ":" +path
            }

            Item {
                width: 1
                height: Theme.paddingMedium
            }

            Image {
                id: image
                anchors.horizontalCenter: parent.horizontalCenter
                source: "https://github.com/" + owner + "/" + repo + "/raw/" + branch + "/" + path

                BusyIndicator {
                    anchors.centerIn: parent
                    running: image.status === Image.Loading
                }
            }

            Item {
                width: 1
                height: Theme.paddingMedium
            }

            DetailItem {
                label: qsTr("Height")
                value: image.sourceSize.height + " px"
            }
            DetailItem {
                label: qsTr("Width")
                value: image.sourceSize.width + " px"
            }
        }
    }
}

