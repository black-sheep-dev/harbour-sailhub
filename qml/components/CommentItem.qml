import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

Item {
    property alias authorLogin: authorItem.title
    property alias authorAvatar: authorItem.avatar
    property alias body: bodyLabel.text
    property bool edited: false
    property string timeSpan

    width: parent.width
    height: contentColumn.height

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingMedium

        AuthorItem {
            id: authorItem
            width: parent.width
            height: Theme.itemSizeMedium

            interactive: true
            subtitle: {
                if (edited)
                    return timeSpan + " - " + qsTr("Edited")

                return timeSpan
            }

            onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), {
                                          login: authorLogin
                                      })
        }

        LinkedLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
            linkColor: Theme.highlightColor

            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
}


