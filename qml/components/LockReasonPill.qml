import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Pill {
    property string lockReason

    backgroundColor: Theme.highlightColor
    color: Theme.primaryColor
    icon: "image://theme/icon-s-secure"
    text: {
        switch (lockReason) {
        case "OFF_TOPIC":
            //% "Off topic"
            return qsTrId("id-off-topic")

        case "RESOLVED":
            //% "Resolved"
            return qsTrId("id-resolved")

        case "SPAM":
            //% "Spam"
            return qsTrId("id-spam")

        case "TOO_HEATED":
            //% "Too heated"
            return qsTrId("id-too-heated")

        default:
            //% "Locked"
            return qsTrId("id-locked")
        }
    }
}




