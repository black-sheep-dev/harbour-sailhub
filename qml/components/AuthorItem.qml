import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property bool interactive: true
    property string avatar
    property alias login: loginLabel.text
    property alias subtitle: subtitleLabel.text

    id: authorItem
    width: parent.width
    height: Theme.itemSizeMedium

    CircleImage {
        id: avatarIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }

        width: authorItem.height * 0.75
        height: width

        source: avatar// + "?size=" + Math.round(width)
    }

    Column {
        anchors {
            left: avatarIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        spacing: Theme.paddingSmall

        Label {
            id: loginLabel
            width: parent.width
            font.pixelSize: Theme.fontSizeMedium
            font.bold: true
            color: getLabelColor()
        }

        Label {
            visible: subtitle.length > 0
            id: subtitleLabel
            width: parent.width
            font.pixelSize: Theme.fontSizeSmall
            color: getLabelColor()
        }
    }

    function getLabelColor() {
        if (interactive)
            return pressed ? Theme.highlightColor : Theme.primaryColor
        else
            return pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
    }

    onClicked: {
        if (!interactive) return

        pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"),  { login: login })
    }
}
