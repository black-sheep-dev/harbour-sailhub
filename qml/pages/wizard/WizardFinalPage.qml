import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../components"

Dialog {
    id: dialog
    allowedOrientations: Orientation.Portrait

    acceptDestination: Qt.resolvedUrl("../OverviewPage.qml")
    acceptDestinationAction: PageStackAction.Replace
    acceptDestinationReplaceTarget: null

    DialogHeader {
        id: header
        //% "Complete"
        acceptText: qsTrId("id-complete")
        //% "Back"
        cancelText: qsTrId("id-back")
    }

    Column {
        anchors.top: header.bottom
        width: parent.width
        spacing: Theme.paddingMedium

        Label {
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Setup process completed"
            text: qsTrId("id-wizard-completed")

            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeLarge
        }
    }

    onAccepted: SailHub.initialize()
}

