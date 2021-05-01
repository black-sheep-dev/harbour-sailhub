import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/stringhelper.js" as StringHelper

//import org.nubecula.harbour.sailhub 1.0

ListItem {
    property alias name: nameLabel.text
    property alias description: descriptionLabel.text

    id: delegate
    width: parent.width
    contentHeight: delegateColumn.height + 2*Theme.paddingMedium

    Column {
        id: delegateColumn
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                visible: model.isPrivate
                id: privateIcon
                source: "image://theme/icon-s-outline-secure?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
            }

            Label {
                id: nameLabel
                width: parent.width
                anchors.verticalCenter: privateIcon.verticalCenter
                color: pressed ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                font.bold: true
                wrapMode: Text.Wrap
            }
        }

        Label {
            visible: model.description.length > 0
            id: descriptionLabel
            width: parent.width
            font.pixelSize: Theme.fontSizeExtraSmall
            wrapMode: Text.Wrap
            font.bold: true
            color: pressed ? Theme.highlightColor : Theme.primaryColor
        }

        Row {
            id: bottomLine
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: stargazerCountIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-new?" + (model.stargazerCount > 0 ? "#ffff00" : Theme.primaryColor)
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: StringHelper.count(model.stargazerCount)
            }

            Rectangle {
                visible: model.languageName.length > 0
                height: stargazerCountIcon.height * 0.5
                width: height
                anchors.verticalCenter: parent.verticalCenter

                radius: stargazerCountIcon.height * 0.25
                color: model.languageColor
            }

            Label {
                visible: model.languageName.length > 0
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.languageName
            }
        }
    }
}
