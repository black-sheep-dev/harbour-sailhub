import QtQuick 2.0
import Sailfish.Silica 1.0

import '..'

BackgroundItem {
    property int additions: 0
    property int deletions: 0
    property int files: 0

    width: parent.width

    Row {
        x: Theme.horizontalPageMargin
        width: parent.width - 2*x
        height: parent.height
        spacing: Theme.paddingSmall

        Icon {
            id: fileIcon
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            source: "qrc:/icons/icon-m-files-changed"
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - fileIcon.width - additionsLabel.width - deletionsLabel.width - 3 * parent.spacing

            //% "%n file(s) changed"
            text: qsTrId("id-files-changed", files)
        }

        Label {
            id: additionsLabel
            visible: additions > 0
            anchors.verticalCenter: parent.verticalCenter
            //font.pixelSize: Theme.fontSizeExtraSmall
            color: SailHubStyles.colorSuccess
            text: "+" + additions
        }
        Label {
            id: deletionsLabel
            visible: deletions > 0
            anchors.verticalCenter: parent.verticalCenter
            //font.pixelSize: Theme.fontSizeExtraSmall
            color: SailHubStyles.colorError
            text: "-" + deletions
        }
    }
}


