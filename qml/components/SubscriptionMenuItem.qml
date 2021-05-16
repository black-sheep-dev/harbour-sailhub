import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

MenuItem {
    property int subscription: SubscriptionState.Unknown
    property string nodeId


    id: subscriptionMenuItem
    text: {
        switch (subscription) {
        case SubscriptionState.Ignored:
        case SubscriptionState.Unsubscribed:
            return qsTr("Watch")

        default:
            return qsTr("Unwatch")
        }
    }

    onClicked: {
        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectSubscriptionDialog.qml"),
                                    { subscription: subscription })

        dialog.accepted.connect(function() {
            SailHub.api().subscribeTo(nodeId, dialog.subscription)
        })
    }

    Connections {
        target: SailHub.api()
        onSubscribedTo: if (subscriptionMenuItem.nodeId === nodeId) subscriptionMenuItem.subscription = state
    }
}




