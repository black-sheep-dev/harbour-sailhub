import QtQuick 2.0
import Sailfish.Silica 1.0

//import org.nubecula.harbour.sailhub 1.0

ListItem {
    property bool lastItem: false

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
                visible: !item.isPublic
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

                text: item.description
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

                text: new Date(item.updatedAt).toLocaleDateString()
            }
        }

        Row {
            id: bottomLine
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: stargazerCountIcon
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-s-new?" + (item.stargazerCount > 0 ? "#ffff00" : Theme.primaryColor)
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: item.stargazerCount
            }

//            Icon {
//                id: fileCountIcon
//                anchors.verticalCenter: parent.verticalCenter
//                source: "image://theme/icon-s-attach"
//            }

//            Label {
//                anchors.verticalCenter: parent.verticalCenter
//                font.pixelSize: Theme.fontSizeSmall
//                color: pressed ? Theme.highlightColor : Theme.primaryColor

//                text: item.fileCount
//            }

            Icon {
                id: forkCountIcon
                anchors.verticalCenter: parent.verticalCenter
                width: Theme.iconSizeSmall
                height: Theme.iconSizeSmall
                source: "qrc:///icons/icon-m-fork"
            }

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: item.forks.totalCount
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

                text: item.comments.totalCount
            }
        }
    }
}
