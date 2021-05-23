import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import '..'

//import org.nubecula.harbour.sailhub 1.0

ListItem {
    property alias name: nameLabel.text
    property alias description: descriptionLabel.text

    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingSmall

    Row {
        id: delegateContent
        anchors.verticalCenter: parent.verticalCenter
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        spacing: Theme.paddingMedium

        CircleImage {
            id: avatarIcon
            width: Theme.iconSizeSmallPlus
            height: width

            fallbackItemVisible: false

            source: model.ownerAvatar

            BusyIndicator {
                size: BusyIndicatorSize.Small
                anchors.centerIn: avatarIcon
                running: avatarIcon.status !== Image.Ready
            }
        }

        Column {
            id: delegateColumn
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingSmall

            Label {
                id: nameLabel
                width: parent.width
                color: pressed ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                font.bold: true
                wrapMode: Text.Wrap
            }

            RepoFlagsItem {
                flags: model.flags
                lockReason: model.lockReason
            }

            Label {
                visible: model.description.length > 0
                id: descriptionLabel
                width: parent.width
                font.pixelSize: Theme.fontSizeExtraSmall
                wrapMode: Text.Wrap
                font.bold: true
                color: pressed ? Theme.highlightColor : Theme.primaryColor
            }

            Row {
                id: bottomLine
                width: parent.width
                spacing: Theme.paddingMedium

                Icon {
                    id: stargazerCountIcon
                    anchors.verticalCenter: parent.verticalCenter
                    source: "image://theme/icon-s-new?" + (model.stargazerCount > 0 ? "#ffff00" : Theme.primaryColor)
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: pressed ? Theme.highlightColor : Theme.primaryColor

                    text: StringHelper.count(model.stargazerCount)
                }

                Rectangle {
                    visible: model.languageName.length > 0
                    height: stargazerCountIcon.height * 0.5
                    width: height
                    anchors.verticalCenter: parent.verticalCenter

                    radius: stargazerCountIcon.height * 0.25
                    color: model.languageColor
                }

                Label {
                    visible: model.languageName.length > 0
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: Theme.fontSizeSmall
                    color: pressed ? Theme.highlightColor : Theme.primaryColor

                    text: model.languageName
                }
            }
        }
    }
}
