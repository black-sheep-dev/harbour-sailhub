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

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: delegateIcon
                anchors.top: parent.top
                width: Theme.iconSizeSmall
                height: Theme.iconSizeSmall
                fillMode: Image.PreserveAspectFit
                source: {
                    switch (model.type) {
                    case Notification.Issue:
                        return "image://theme/icon-s-high-importance";

                    case Notification.PullRequest:
                        return "qrc:///icons/icon-m-pull-request";

                    default:
                        return "image://theme/icon-s-alarm"
                    }
                }
            }

            Column {
                width: parent.width - delegateIcon.width - parent.spacing

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - timeSpanLabel.width - parent.spacing
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.pixelSize: Theme.fontSizeTiny

                        text: model.repoName + " #" + model.number
                    }

                    Label {
                        id: timeSpanLabel
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall

                        text: model.updatedAtTimeSpan
                    }
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.bold: true

                    text: model.title
                }
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
