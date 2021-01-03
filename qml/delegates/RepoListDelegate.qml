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
    property bool lastItem: false
    property bool isPrivate: false

    id: delegate
    width: parent.width
    contentHeight: delegateColumn.height

    Column {
        id: delegateColumn
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingSmall

        Item {
            width: 1
            height: Theme.paddingSmall
        }

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                visible: isPrivate
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

                text: name
            }
        }

        Label {
            visible: description.length > 0
            width: parent.width
            font.pixelSize: Theme.fontSizeExtraSmall
            wrapMode: Text.Wrap
            font.bold: true
            color: pressed ? Theme.highlightColor : Theme.primaryColor

            text: description
        }

        Row {
            id: bottomLine
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: stargazerCountIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-new?" + (stargazerCount > 0 ? "#ffff00" : Theme.primaryColor)
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: stargazerCount
            }

            Rectangle {
                height: stargazerCountIcon.height * 0.5
                width: height
                anchors.verticalCenter: parent.verticalCenter

                radius: stargazerCountIcon.height * 0.25
                color: languageColor
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: languageName
            }
        }

        Separator {
            visible: !lastItem
            width: parent.width
            color: Theme.highlightBackgroundColor
        }
    }
}
