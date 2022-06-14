import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingMedium

    Row {
        id: delegateContent
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        Icon {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-events"
        }

        Column {
            width: parent.width - icon.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingSmall

            Label {
                width: parent.width
                font.bold: true

                text: model.name
            }

            Row {
                width: parent.width
                spacing: Theme.paddingMedium

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    text: model.createdAtTimeSpan
                }

                Label {
                    visible: model.isDraft
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#b71c1c"
                    //% "Draft"
                    text: qsTrId("id-draft")
                }

                Label {
                    visible: model.isLatest
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#64DD17"
                    //% "Latest release"
                    text: qsTrId("id-latest-release")
                }

                Label {
                    visible: model.isPrerelease
                    font.pixelSize: Theme.fontSizeSmall
                    color: "#f29312"
                    //% "Pre-release"
                    text: qsTrId("id-pre-release")
                }
            }
        }
    }
}


