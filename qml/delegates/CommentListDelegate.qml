import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: contentColumn.height + 2*Theme.paddingMedium

    Column {
        id: contentColumn
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Row {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingMedium

            CircleImage {
                id: avatarIcon
                width: parent.height - 2 * Theme.paddingSmall
                source: model.authorAvatarUrl
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

                    text: model.authorLogin
                }
                Label {
                    color: pressed ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeSmall

                    text: {
                        if (model.edited)
                            //% "Edited"
                            return model.createdAtTimeSpan + " - " + qsTrId("id-edited")

                        return model.createdAtTimeSpan
                    }
                }
            }
        }

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            wrapMode: Text.Wrap

            text: model.bodyExcerpt
        }
    }
}

