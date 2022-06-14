import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Pill {
    property int lockReason: LockReason.Unknown

    backgroundColor: Theme.highlightColor
    color: Theme.primaryColor
    icon: "image://theme/icon-s-secure"
    text: {
        switch (lockReason) {
        case LockReason.OffTopic:
            //% "Off topic"
            return qsTrId("id-off-topic")

        case LockReason.Resolved:
            //% "Resolved"
            return qsTrId("id-resolved")

        case LockReason.Spam:
            //% "Spam"
            return qsTrId("id-spam")

        case LockReason.TooHeated:
            //% "Too heated"
            return qsTrId("id-too-heated")

        default:
            //% "Locked"
            return qsTrId("id-locked")
        }
    }
}




