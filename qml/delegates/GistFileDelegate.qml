import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../components/"

ListItem {
    width: parent.width

    contentHeight: languageItem.y + languageItem.height + 2*Theme.paddingSmall

    Icon {
        id: itemIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            top: parent.top
            topMargin: Theme.paddingSmall
        }
        source: {
            if (model.isImage) return "image://theme/icon-m-file-image"
            if (model.text === null) return "image://theme/icon-m-file-other-light"
            return "image://theme/icon-m-file-document-light"
        }
    }

    Label {
        id: nameLabel
        anchors {
            left: itemIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: itemIcon.verticalCenter
        }
        truncationMode: TruncationMode.Fade
        text: model.name
    }

    LanguageItem {
        id: languageItem
        visible: model.hasOwnProperty("language") && model.language.hasOwnProperty("color")
        anchors {
            left: itemIcon.right
            leftMargin: Theme.paddingMedium
            top: nameLabel.bottom
            topMargin: Theme.paddingMedium
        }

        name: model.language.hasOwnProperty("name") ? model.language.name : "None"
        color: model.language.hasOwnProperty("color") ? model.language.color : "#FFF"
    }

    Label {
        anchors {
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: languageItem.verticalCenter
        }
        font.pixelSize: Theme.iconSizeExtraSmall
        //% "Size"
        text: qsTrId("id-size") + " " + StringHelper.fileSize(model.size)
    }
}
