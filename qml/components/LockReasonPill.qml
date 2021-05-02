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
            return qsTr("Off Topic")

        case LockReason.Resolved:
            return qsTr("Resolved")

        case LockReason.Spam:
            return qsTr("Spam")

        case LockReason.TooHeated:
            return qsTr("Too heated")

        default:
            return qsTr("Locked")
        }
    }
}




