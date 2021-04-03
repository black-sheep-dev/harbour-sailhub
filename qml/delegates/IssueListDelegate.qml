import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property bool lastItem: false

    id: delegate
    width: parent.width
    contentHeight: delegateContent.height

    Column {
        id: delegateContent
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingSmall

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: closedIcon
                source: model.closed ? "image://theme/icon-s-installed?00ff00" : "image://theme/icon-s-high-importance?#ff0000"
            }

            Label {
                width: parent.width - closedIcon.width - numberLabel.width - 2 * parent.spacing
                anchors.verticalCenter: closedIcon.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.repository
            }

            Label {
                id: numberLabel
                anchors.verticalCenter: closedIcon.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: " #" + model.number
            }
        }

        Label {
            width: parent.width
            wrapMode: Text.Wrap
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            font.bold: true

            text: model.title
        }

        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Icon {
                id: dateIcon
                source: "image://theme/icon-s-date"
            }

            Label {
                width: parent.width - dateIcon.width - commentIcon.width - commentsLabel.width - 3 * parent.spacing
                anchors.verticalCenter: commentIcon.verticalCenter
                font.pixelSize: Theme.fontSizeTiny
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.createdAt.toLocaleDateString(Qt.locale())
            }

            Icon {
                id: commentIcon
                source: "image://theme/icon-s-chat"
            }

            Label {
                id: commentsLabel
                anchors.verticalCenter: commentIcon.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.commentCount
            }
        }

        Separator {
            visible: !lastItem
            width: parent.width
            color: Theme.highlightBackgroundColor
        }
    }
}
