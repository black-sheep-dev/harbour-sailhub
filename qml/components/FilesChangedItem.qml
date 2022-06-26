import QtQuick 2.0
import Sailfish.Silica 1.0

import '..'

BackgroundItem {
    property int additions: 0
    property int deletions: 0
    property int files: 0

    width: parent.width

    Icon {
        id: fileIcon
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        width: Theme.iconSizeMedium
        height: Theme.iconSizeMedium
        source: "qrc:/icons/icon-m-files-changed"
    }

    Label {
        anchors {
            left: fileIcon.right
            leftMargin: Theme.paddingMedium
            right: additionsLabel.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.Wrap
        //% "%n file(s) changed"
        text: qsTrId("id-files-changed", files)
    }

    Label {
        id: additionsLabel
        visible: additions > 0
        anchors {
            right: deletionsLabel.left
            rightMargin: Theme.paddingSmall
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: Theme.fontSizeExtraSmall
        color: SailHubStyles.colorSuccess
        text: "+" + additions
    }
    Label {
        id: deletionsLabel
        visible: deletions > 0
        anchors {
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: Theme.fontSizeExtraSmall
        color: SailHubStyles.colorError
        text: "-" + deletions
    }

}


