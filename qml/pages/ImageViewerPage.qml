import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    property string branch
    property string owner
    property string path
    property string repo

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        readonly property string url: "https://github.com/" + owner + "/" + repo + "/raw/" + branch + "/" + path

        PullDownMenu {
            MenuItem {
                //% "Download"
                text: qsTrId("id-download")
                onClicked: Qt.openUrlExternally(url)
            }
        }

        anchors.fill: parent
        contentHeight: column.height
        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: repo
                description: branch + ":" + path
            }

            Image {
                id: image
                anchors.horizontalCenter: parent.horizontalCenter
                source: url

                BusyIndicator {
                    anchors.centerIn: parent
                    running: image.status === Image.Loading
                }
            }

            DetailItem {
                //% "Height"
                label: qsTrId("id-height")
                value: image.sourceSize.height + " px"
            }
            DetailItem {
                //% "Width"
                label: qsTrId("id-width")
                value: image.sourceSize.width + " px"
            }
        }
    }
}

