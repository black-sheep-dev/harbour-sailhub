import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

ListItem {
    width: parent.width

    contentHeight: Theme.itemSizeMedium

    Icon {
        id: itemIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        source: {
            if (model.type === "tree") return "image://theme/icon-m-file-folder"

            switch (model.extension) {
            case ".md":
                return "image://theme/icon-m-file-formatted-light"

            case ".bmp":
            case ".gif":
            case ".ico":
            case ".jpg":
            case ".jpeg":
            case ".png":
            case ".svg":
                return "image://theme/icon-m-file-image"

            default:
                if (model.object.isBinary) return "image://theme/icon-m-file-other-light"

                return "image://theme/icon-m-file-document-light"
            }
        }
    }

    Label {
        anchors {
            left: itemIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        truncationMode: TruncationMode.Fade
        text: model.name
    }
}
