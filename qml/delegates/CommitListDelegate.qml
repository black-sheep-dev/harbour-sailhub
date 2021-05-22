import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingMedium

    Row {
        id: delegateContent
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Column {
            width: parent.width - timeSpanLabel.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingSmall

            Label {
                width: parent.width
                wrapMode: Text.Wrap
                font.bold: true

                text: model.messageHeadline
            }

            Row {
                width: parent.width
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    width: Theme.iconSizeSmall
                    height: width
                    anchors.verticalCenter: parent.verticalCenter

                    fallbackItemVisible: false

                    source: model.authorAvatar

                    BusyIndicator {
                        size: BusyIndicatorSize.Small
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    text: model.authorName
                }
            }
        }

        Label {
            id: timeSpanLabel
            text: model.pushedAtTimeSpan
        }
    }
}
