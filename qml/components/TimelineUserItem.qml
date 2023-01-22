import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias avatarUrl: avatarIcon.source
    property string login

    id: userItem

    width: avatarIcon.width
    height: Theme.itemSizeExtraSmall

    CircleImage {
        id: avatarIcon
        anchors {
            left: parent.left
            leftMargin: Theme.paddingSmall
            verticalCenter: parent.verticalCenter
        }

        width: Theme.iconSizeSmall
        height: width
    }

    Label {
        anchors {
            left: avatarIcon.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.Wrap
        font.bold: true
        text: login
    }

    onClicked: pageStack.push(Qt.resolvedUrl("../pages/UserPage.qml"),  { login: login })
}
