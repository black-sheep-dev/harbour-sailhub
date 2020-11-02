import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property string title
    property int stargazers: 0
    property string language
    property date lastUpdate

    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeLarge

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * x
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter

        Image {
            id: repoIcon

            anchors.verticalCenter: parent.verticalCenter

            source: "image://theme/icon-m-pin"
        }

        Item {
            width: Theme.paddingMedium
            height: 1
        }

        Column {
            width: parent.width - repoIcon.width - Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter

            Label {
                width: parent.width
                text: title
                color: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
                font.pixelSize: Theme.fontSizeMedium
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall

                Image {
                    id: starIcon
                    anchors.verticalCenter: parent.verticalCenter
                    source: "image://theme/icon-s-favorite"
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall

                    text: stargazers
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall

                    text: "|"
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall

                    text: language
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall

                    text: "|"
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeExtraSmall

                    text: qsTr("Updated on %1").arg(lastUpdate.toDateString())
                }
            }
        }
    }
}
