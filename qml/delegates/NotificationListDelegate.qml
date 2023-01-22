import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."
import "../components/"

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingSmall

    Icon {
        id: delegateIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        width: Theme.iconSizeSmall
        height: Theme.iconSizeSmall
        source: {
            switch (model.subject.type) {
            case "Issue":
                return "/usr/share/harbour-sailhub/icons/icon-m-issue.svg";

            case "PullRequest":
                return "/usr/share/harbour-sailhub/icons/icon-m-pull-request.svg";

            default:
                return "image://theme/icon-s-alarm"
            }
        }
    }

    Column {
        id: delegateContent
        anchors {
            left: delegateIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        spacing: Theme.paddingMedium

        Row {
            width: parent.width
            spacing: Theme.paddingSmall

            Label {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - timeSpanLabel.width - parent.spacing
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: Theme.fontSizeTiny
                text: model.repository.name + " #" + model.subject.url.substring(model.subject.url.lastIndexOf("/") + 1)
            }

            Label {
                id: timeSpanLabel
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Theme.fontSizeSmall
                text: StringHelper.timespan(new Date(model.updated_at))
            }
        }

        Label {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.bold: true
            text: model.subject.title
        }
    }
}
