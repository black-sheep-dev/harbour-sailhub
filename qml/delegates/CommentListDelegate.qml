import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property bool lastItem: false

    id: delegate
    width: parent.width
    contentHeight: contentColumn.height

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingSmall

        Item {
            width: 1
            height: Theme.paddingSmall
        }

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
                            return model.createdAtTimeSpan + " - " + qsTr("Edited")

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

        Item {
            width: 1
            height: Theme.paddingSmall
        }

        Separator {
            visible: !lastItem
            width: parent.width
            color: Theme.highlightBackgroundColor
        }
    }
}

