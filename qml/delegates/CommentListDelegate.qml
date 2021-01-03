import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property string avatar
    property string body
    property date createdAt
    property string login
    property date lastEditAt
    property bool lastItem: false

    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeLarge

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingMedium

        Row {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingMedium

            CircleImage {
                id: avatarIcon
                width: parent.height - 2 * Theme.paddingSmall
                source: avatar
                anchors.verticalCenter: parent.verticalCenter

                fallbackItemVisible: false
            }

            Column {
                width: parent.width - avatarIcon.width - Theme.paddingMedium
                anchors.verticalCenter: avatarIcon.verticalCenter

                Label {
                    width: parent.width
                    color: pressed ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeMedium
                    font.bold: true

                    text: login
                }
                Label {
                    color: pressed ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeSmall

                    text: createdAt.toLocaleString(Qt.locale())
                }
            }
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            wrapMode: Text.Wrap

            text: body
        }

        Separator {
            visible: !lastItem
            width: parent.width
            color: Theme.highlightBackgroundColor
        }
    }
}

