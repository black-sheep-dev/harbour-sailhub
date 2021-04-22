import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

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
                source: model.state === PullRequest.StateMerged ?  "qrc:///icons/icon-m-merged" : "qrc:///icons/icon-m-pull-request"

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: {
                        if (model.state === PullRequest.StateOpen)
                            return "#64DD17"

                        if (model.state === PullRequest.StateClosed)
                            return "#D50000"

                        if (model.state === PullRequest.StateMerged)
                            return "#D500F9"

                        return "#FFFFFF"
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

                        text: model.repository + " #" + model.number
                    }

                    Label {
                        id: timeSpanLabel
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Theme.fontSizeSmall

                        text: model.sortRole === PullRequestsModel.UpdatedAtRole ? model.updatedAtTimeSpan : model.createdAtTimeSpan
                    }
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.bold: true

                    text: model.title
                }

                Item {
                    width: 1
                    height: parent.spacing
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Icon {
                        id: dateIcon
                        anchors.verticalCenter: parent.verticalCenter
                        source: "image://theme/icon-s-date"
                    }

                    Label {
                        width: parent.width - dateIcon.width - commentIcon.width - commentsLabel.width - 3 * parent.spacing
                        anchors.verticalCenter: commentIcon.verticalCenter
                        font.pixelSize: Theme.fontSizeTiny
                        color: pressed ? Theme.highlightColor : Theme.primaryColor

                        text: model.createdAt.toLocaleDateString(Qt.locale())
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

                        text: model.commentCount
                    }
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
