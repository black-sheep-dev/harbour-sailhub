import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import '..'

ListItem {

    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingMedium

    Column {
        id: delegateContent
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingSmall

        Row {
            width: parent.width
            spacing: Theme.paddingMedium

            Icon {
                id: delegateIcon
                anchors.top: parent.top
                source: item.state === "MERGED" ?  "qrc:/icons/icon-m-merged" : "qrc:/icons/icon-m-pull-request"

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: {
                        switch (item.state) {
                        case "OPEN":
                            return SailHubStyles.colorStatusOpen

                        case "CLOSED":
                            return SailHubStyles.colorStatusClosed

                        case "MERGED":
                            return SailHubStyles.colorStatusMerged

                        default:
                            return Theme.primaryColor
                        }
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

                        text: item.repository.nameWithOwner + " #" + item.number
                    }

                    Label {
                        id: timeSpanLabel
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall

                        text: item.sortRole === PullRequestsitem.UpdatedAtRole ? item.updatedAtTimeSpan : item.createdAtTimeSpan
                    }
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Label {
                        width: parent.width - commentIcon.width - commentsLabel.width - 2*parent.spacing
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.bold: true

                        text: item.title
                    }

                    Icon {
                        id: commentIcon
                        anchors.verticalCenter: parent.verticalCenter
                        source: "image://theme/icon-s-chat"

                    }

                    Label {
                        id: commentsLabel
                        anchors.verticalCenter: commentIcon.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall
                        color: pressed ? Theme.highlightColor : Theme.primaryColor

                        text: item.comments.totalCount
                    }
                }
            }
        }
    }
}
