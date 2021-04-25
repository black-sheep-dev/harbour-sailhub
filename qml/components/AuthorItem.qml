import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property bool interactive: true
    property string avatar
    property alias subtitle: subtitleLabel.text
    property alias title: titleLabel.text

    id: authorItem
    width: parent.width
    height: Theme.itemSizeMedium

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium

        CircleImage {
            id: avatarIcon
            width: authorItem.height * 0.75
            height: width
            anchors.verticalCenter: parent.verticalCenter

            fallbackItemVisible: false

            source: avatar + "?size=" + width

            BusyIndicator {
                size: BusyIndicatorSize.Medium
                anchors.centerIn: avatarIcon
                running: avatarIcon.status !== Image.Ready
            }
        }

        Column {
            width: parent.width - avatarIcon.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingSmall

            Label {
                id: titleLabel
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall
                font.bold: true
                color: getLabelColor()

                text: issue.author.login
            }

            Label {
                id: subtitleLabel
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall
                color: getLabelColor()
            }
        }
    }

    function getLabelColor() {
        if (interactive)
            return pressed ? Theme.highlightColor : Theme.primaryColor
        else
            return pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
    }
}
