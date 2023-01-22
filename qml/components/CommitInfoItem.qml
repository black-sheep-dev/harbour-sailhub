import QtQuick 2.0
import Sailfish.Silica 1.0

import "../."

Column {
    property var commit

    id: contentColumn
    width: parent.width
    spacing: Theme.paddingMedium

    AuthorItem {
        avatar: commit.author.user.avatarUrl
        login: commit.author.user.name
        subtitle: commit.author.user.login

        onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"), { nodeId: commit.author.user.id })
    }

    Label {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        wrapMode: Text.Wrap
        font.pixelSize: Theme.fontSizeExtraSmall
        text: StringHelper.timespan(commit.committedDate)
    }

    Label {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        wrapMode: Text.Wrap
        text: commit.messageHeadline
    }

    IconRelatedItem {
        title: commit.abbreviatedOid
        icon: "image://theme/icon-m-swipe"
        showNextIcon: false
    }

    FilesChangedItem {
        additions: commit.additions
        deletions: commit.deletions
        files: commit.changedFiles
    }
}

