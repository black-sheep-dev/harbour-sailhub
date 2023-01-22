import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."

ListItem {
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
                visible: !model.isPublic
                id: privateIcon
                source: "image://theme/icon-s-outline-secure?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
            }

            Label {
                width: parent.width
                anchors.verticalCenter: privateIcon.verticalCenter
                color: pressed ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                font.bold: true
                wrapMode: Text.Wrap

                text: model.description
            }
        }

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: dateIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-date"
            }

            Label {
                width: parent.width - dateIcon.width - parent.spacing
                anchors.verticalCenter: dateIcon.verticalCenter
                font.pixelSize: Theme.fontSizeTiny
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: StringHelper.timespan(new Date(model.updatedAt))
            }
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

                text: model.stargazerCount
            }

            Icon {
                id: fileCountIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-attach"
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.files.count
            }

            Icon {
                id: forkCountIcon
                anchors.verticalCenter: parent.verticalCenter
                width: Theme.iconSizeSmall
                height: Theme.iconSizeSmall
                source: "/usr/share/harbour-sailhub/icons/icon-m-fork.svg"
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.forks.totalCount
            }

            Icon {
                id: commentCountIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-chat"
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.comments.totalCount
            }
        }
    }
}
