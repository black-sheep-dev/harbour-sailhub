import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"

ListItem {
    property bool lastItem: false

    id: delegate
    width: parent.width
    contentHeight: delegateContent.height

    Column {
        id: delegateContent
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingSmall

        Item {
            width: 1
            height: Theme.paddingMedium
        }

        Label {
            width: parent.width
            font.bold: true

            text: model.name
        }

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Label {
                font.pixelSize: Theme.fontSizeSmall
                text: model.createdAtTimeSpan
            }

            Label {
                visible: model.isLatest
                font.pixelSize: Theme.fontSizeSmall
                color: "#64DD17"
                text: qsTr("Latest release")
            }
        }

        Item {
            width: 1
            height: Theme.paddingMedium
        }
    }

    Separator {
        visible: !lastItem
        anchors.top: delegateContent.bottom
        width: parent.width
        color: Theme.highlightBackgroundColor
    }
}
