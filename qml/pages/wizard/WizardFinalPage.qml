import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../components"

Dialog {
    id: dialog
    allowedOrientations: Orientation.Portrait

    DialogHeader {
        id: header
        acceptText: qsTr("Complete")
        cancelText: qsTr("Back")
    }

    Column {
        anchors.top: header.bottom
        width: parent.width
        spacing: Theme.paddingMedium

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Setup process completed")

            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeLarge
        }
    }

    onAccepted: {
        SailHub.initialize()
        pageStack.clear()
        pageStack.push(Qt.resolvedUrl("../OverviewPage.qml"))
    }
}

