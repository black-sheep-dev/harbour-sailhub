import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import ".."

Item {
    property alias authorAvatar: authorItem.avatar
    property alias authorLogin: authorItem.login
    property string body
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

            interactive: true
            subtitle: {
                if (edited)
                    //% "Edited"
                    return timeSpan + " - " + qsTrId("id-edited")

                return timeSpan
            }

            onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), {
                                          login: authorLogin
                                      })
        }

        MarkdownLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            text: MarkdownParser.parse(body)
        }
    }
}


