import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../js/stringhelper.js" as StringHelper

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingSmall

    Row {
        id: delegateContent
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        Icon {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-file-other-light"
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

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "image://theme/icon-s-sd-card"
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall
                    text: StringHelper.fileSize(model.size)
                }

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "image://theme/icon-s-cloud-download"
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall
                    text: StringHelper.count(model.downloadCount)
                }
            }
        }
    }
}
