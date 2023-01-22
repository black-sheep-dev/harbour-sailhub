import QtQuick 2.0
import Sailfish.Silica 1.0

import "../../queries/"

MenuItem {
    property string nodeId
    property string subscription: ""
    property alias viewerCanSubscribe: subscriptionMenu.visible

    UpdateSubscriptionMutation {
        id: updateSubscriptionMutation
        nodeId: subscriptionMenu.nodeId
        state: subscription
    }

    id: subscriptionMenu

    text: {
        switch (subscription) {
        case "IGNORED":
        case "UNSUBSCRIBED":
            //% "Watch"
            return qsTrId("id-watch")

        default:
            //% "Unwatch"
            return qsTrId("id-unwatch")
        }
    }

    onClicked: {
        var dialog = pageStack.push(Qt.resolvedUrl("../../dialogs/SelectSubscriptionDialog.qml"), { subscription: subscription })

        dialog.accepted.connect(function() {
            updateSubscriptionMutation.state = dialog.subscription
            subscription = dialog.subscription
            Api.request(updateSubscriptionMutation)
        })
    }
}
