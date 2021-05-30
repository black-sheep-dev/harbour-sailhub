import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    width: parent.width

    contentHeight: Theme.itemSizeMedium

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        Icon {
            id: itemIcon
            anchors.verticalCenter: parent.verticalCenter
            source: {
                if (model.type === TreeItem.Tree) {
                    return "image://theme/icon-m-file-folder"
                } else {
                    switch (model.fileType) {
                    case File.Image:
                        return "image://theme/icon-m-file-image"

                    case File.Markdown:
                        return "image://theme/icon-m-file-formatted-light"

                    case File.Text:
                        return "image://theme/icon-m-file-document-light"

                    default:
                        return "image://theme/icon-m-file-other-light"
                    }
                }
            }
        }

        Label {
            width: parent.width - itemIcon.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter

            text: model.name
        }
    }
}
