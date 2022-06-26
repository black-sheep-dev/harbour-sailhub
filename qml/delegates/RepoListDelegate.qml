import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import '..'

ListItem {
    id: delegate
    width: parent.width
    contentHeight: delegateContent.height + 2*Theme.paddingSmall

    CircleImage {
        id: avatarIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            top: parent.top
        }

        width: Theme.iconSizeSmallPlus
        height: width

        fallbackItemVisible: false

        source: item.owner.avatarUrl

        BusyIndicator {
            size: BusyIndicatorSize.Small
            anchors.centerIn: avatarIcon
            running: avatarIcon.status !== Image.Ready
        }
    }

    Rectangle {
        anchors {
           horizontalCenter: avatarIcon.horizontalCenter
           top: avatarIcon.bottom
           topMargin: Theme.paddingMedium
           bottom: parent.bottom
           bottomMargin: Theme.paddingLarge
        }
        width: 5
        opacity: 0.5
        gradient: Gradient {
            GradientStop { position: 0.0; color: item.isPrivate ? Theme.errorColor : Theme.highlightColor; }
            GradientStop { position: 1.0; color: (item.isPrivate ? Theme.errorColor : Theme.highlightColor) + "00"; }
        }

    }

    Column {
        id: delegateContent
        anchors {
            left: avatarIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }

        spacing: Theme.paddingSmall

        Label {
            width: parent.width
            font.pixelSize: Theme.fontSizeTiny
            text: item.owner.login
        }

        Label {
            width: parent.width
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            font {
                pixelSize: Theme.fontSizeMedium
                bold: true
            }
            wrapMode: Text.Wrap

            text: item.name
        }

        RepoFlagsItem {
            isArchived: item.isArchived
            isDisabled: item.isDisabled
            isEmpty: item.isEmtpy
            isFork: item.isFork
            isInOrganization:  item.isInOrganization
            isLocked: item.isLocked
            isMirror: item.isMirror
            isPrivate: item.isPrivate
            isTemplate: item.isTemplate
            lockReason: item.lockReason
        }

        Label {
            visible: item.shortDescriptionHTML.length > 0
            width: parent.width
            font.pixelSize: Theme.fontSizeExtraSmall
            wrapMode: Text.Wrap
            font.bold: true
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            text: MarkdownParser.parseRaw(item.shortDescriptionHTML)
        }

        Row {
            width: parent.width
            spacing: Theme.paddingLarge

            StargazerItem {
                count: item.stargazerCount
            }

            LanguageItem {
                name: item.primaryLanguage.name
                color: item.primaryLanguage.color
            }
        }
    }

}
