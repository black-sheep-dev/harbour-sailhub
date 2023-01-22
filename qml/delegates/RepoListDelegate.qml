import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components/"
import "../."

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
            topMargin: Theme.paddingMedium
        }

        width: Theme.iconSizeSmallPlus
        height: width
        source: model.owner.avatarUrl
    }

    Rectangle {
        anchors {
           horizontalCenter: avatarIcon.horizontalCenter
           top: avatarIcon.bottom
           bottom: parent.bottom
        }
        width: 4
        opacity: 0.5
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent"; }
            GradientStop { position: 0.5; color: model.isPrivate ? Theme.errorColor : Theme.highlightColor; }
            GradientStop { position: 1.0; color: "transparent"; }
        }

    }

    Column {
        id: delegateContent
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            left: avatarIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }

        spacing: Theme.paddingSmall

        Label {
            width: parent.width
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.highlightColor
            text: model.owner.login
        }

        Label {
            width: parent.width
            color: Theme.highlightColor
            font {
                pixelSize: Theme.fontSizeMedium
                bold: true
            }
            wrapMode: Text.Wrap

            text: model.name
        }

        RepoFlagsItem {
            isArchived: model.isArchived
            isDisabled: model.isDisabled
            isEmpty: model.isEmpty
            isFork: model.isFork
            isInOrganization:  model.isInOrganization
            isLocked: model.isLocked
            isMirror: model.isMirror
            isPrivate: model.isPrivate
            isTemplate: model.isTemplate
            lockReason: model.lockReason === undefined ? "" : model.lockReason
        }

        Label {
            visible: model.shortDescriptionHTML.length > 0
            width: parent.width
            font.pixelSize: Theme.fontSizeExtraSmall
            wrapMode: Text.Wrap
            font.bold: true
            color: pressed ? Theme.highlightColor : Theme.primaryColor
            text: MarkdownParser.parseRaw(model.shortDescriptionHTML)
        }

        Row {
            width: parent.width
            spacing: Theme.paddingLarge

            StargazerItem { count: model.stargazerCount }

            LanguageItem {
                visible: model.hasOwnProperty("primaryLanguage") && model.primaryLanguage.hasOwnProperty("color")
                name: model.primaryLanguage.hasOwnProperty("name") ? model.primaryLanguage.name : ""
                color: model.primaryLanguage.hasOwnProperty("color") ? model.primaryLanguage.color : "#FFF"
            }
        }
    }
}
