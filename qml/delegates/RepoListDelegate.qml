import QtQuick 2.0
import Sailfish.Silica 1.0

//import org.nubecula.harbour.sailhub 1.0

ListItem {
    property string name
    property string description
    property int stargazerCount: 0
    //property Language language
    property string languageColor
    property string languageName

    id: delegate
    width: parent.width
    contentHeight: Theme.itemSizeHuge

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height - bottomLine.height
        anchors.top: parent.top

        Column {
            width: parent.width - Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter

            Label {
                width: parent.width
                text: name
                color: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
                font.pixelSize: Theme.fontSizeMedium
            }

            Label {
                width: parent.width
                text: description
                font.pixelSize: Theme.fontSizeExtraSmall
                wrapMode: Text.Wrap
            }
        }
    }
    Row {
        id: bottomLine
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.bottom: parent.bottom
        spacing: Theme.paddingMedium

        Image {
            id: stargazerCountIcon
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-s-new?" + "#ffff00"
        }

        Label {
            text: stargazerCount
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Theme.fontSizeSmall
        }

        Rectangle {
            height: stargazerCountIcon.height * 0.5
            width: height
            anchors.verticalCenter: parent.verticalCenter

            radius: stargazerCountIcon.height * 0.25
            color: languageColor
        }

        Label {
            text: languageName
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: Theme.fontSizeSmall
        }
    }
}
