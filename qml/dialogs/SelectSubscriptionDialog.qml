import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    property int subscription

    Column {
        width: parent.width

        DialogHeader {
            title: qsTr("Choose Subscription")
            acceptText: qsTr("Select")
        }

        TextSwitch {
            id: ignoreSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Unsubscribe")
            description: qsTr("Disable all notifications")

            checked: subscription === SubscriptionState.Ignored
            onClicked: subscription = SubscriptionState.Ignored
        }

        TextSwitch {
            id: unsubscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Subscribe")
            description: qsTr("Get notified only when participating or mentioned")

            checked: subscription === SubscriptionState.Unsubscribed
            onClicked: subscription = SubscriptionState.Unsubscribed
        }

        TextSwitch {
            id: subscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Subscribe (all)");
            description: qsTr("Get notified of all conversation")

            checked: subscription === SubscriptionState.Subscribed
            onClicked: subscription = SubscriptionState.Subscribed
        }
    }
}
