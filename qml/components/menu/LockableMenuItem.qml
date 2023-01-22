import QtQuick 2.0
import Sailfish.Silica 1.0

import "../../queries"
import "../."

MenuItem {
    property string nodeId
    property bool locked
    property alias viewerCanUpdate: lockableMenu.visible

    //% "Lock"
    property string lockText:qsTrId("id-lock")

    //% "Unlock"
    property string unlockText: qsTrId("id-unlock")

    function toggle() {
        if (locked) {
            unlockMutation.execute()
            return
        }

        var dialog = pageStack.push(Qt.resolvedUrl("../../dialogs/SelectLockReasonDialog.qml"))

        dialog.accepted.connect(function() {
            lockMutation.reason = dialog.reason
            lockMutation.execute()
        })
    }

    id: lockableMenu

    LockLockableMutation {
        id: lockMutation
        nodeId: lockableMenu.nodeId

        onResultChanged: lockableMenu.locked = result.lockLockable.lockedRecord.locked
    }

    UnlockLockableMutation {
        id: unlockMutation
        nodeId: lockableMenu.nodeId

        onResultChanged: lockableMenu.locked = result.unlockLockable.unlockedRecord.locked
    }

    text: locked ? unlockText : lockText

    onClicked: toggle()

}


