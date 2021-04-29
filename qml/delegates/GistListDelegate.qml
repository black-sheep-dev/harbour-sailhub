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
                anchors.verticalCenter: commentIcon.verticalCenter
                font.pixelSize: Theme.fontSizeTiny
                color: pressed ? Theme.highlightColor : Theme.primaryColor

                text: model.updatedAt.toLocaleDateString(Qt.locale())
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

//            Icon {
//                id: fileCountIcon
//                anchors.verticalCenter: parent.verticalCenter
//                source: "image://theme/icon-s-attach"
//            }

//            Label {
//                anchors.verticalCenter: parent.verticalCenter
//                font.pixelSize: Theme.fontSizeSmall
//                color: pressed ? Theme.highlightColor : Theme.primaryColor

//                text: model.fileCount
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

                text: model.forkCount
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

                text: model.commentCount
            }
        }
    }
}
