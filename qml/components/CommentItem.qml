import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../tools/"

Item {
    property alias authorLogin: authorItem.title
    property alias authorAvatar: authorItem.avatar
    property string body
    property bool edited: false
    property string timeSpan

    width: parent.width
    height: contentColumn.height

    MarkdownParser {
        id: markdownParser
    }

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.paddingMedium

        AuthorItem {
            id: authorItem

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

        MarkdownLabel {
            id: bodyLabel
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            text: markdownParser.parse(body)
        }
    }
}


