import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

MenuItem {
    property bool starred: false
    property string nodeId

    id: starMenuItem

    text: starred ?
              //% "Unstar"
              qsTrId("id-unstar") :
              //% "Star"
              qsTrId("id-star")

    onClicked: {
        if (starred)
            SailHub.api().removeStar(nodeId)
        else
            SailHub.api().addStar(nodeId)
    }

    Connections {
        target: SailHub.api()
        onStarred: if (nodeId === starMenuItem.nodeId) starMenuItem.starred = starred
    }
}




