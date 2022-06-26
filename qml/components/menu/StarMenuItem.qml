import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../queries/"

MenuItem {
    property bool starred: false
    property string nodeId
    property int stargazerCount: 0

    AddStarMutation {
        id: addStarMutation
        nodeId: starMenuItem.nodeId

        onResultChanged: {
            starred = result.addStar.starrable.viewerHasStarred
            stargazerCount = result.addStar.starrable.stargazerCount
        }
    }

    RemoveStarMutation {
        id: removeStarMutation
        nodeId: starMenuItem.nodeId

        onResultChanged: {
            starred = result.removeStar.starrable.viewerHasStarred
            stargazerCount = result.removeStar.starrable.stargazerCount
        }
    }

    id: starMenuItem

    text: starred ?
              //% "Unstar"
              qsTrId("id-unstar") :
              //% "Star"
              qsTrId("id-star")

    onClicked: {
        if (starred)
            Api.request(removeStarMutation)
        else
            Api.request(addStarMutation)
    }
}




