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

            onClicked: {
                unsubscribeSwitch.checked = !checked
                subscribeSwitch.checked = !checked
            }
        }

        TextSwitch {
            id: unsubscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Subscribe")
            description: qsTr("Get notified only when participating or mentioned")

            onClicked: {
                subscribeSwitch.checked = !checked
                ignoreSwitch.checked = !checked
            }
        }

        TextSwitch {
            id: subscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            text: qsTr("Subscribe (all)");
            description: qsTr("Get notified of all conversation")

            onClicked: {
                unsubscribeSwitch.checked = !checked
                ignoreSwitch.checked = !checked
            }
        }
    }

    function setSubcriptionState() {
        switch (subscription) {            
        case SubscriptionState.Unsubscribed:
            unsubscribeSwitch.checked = true
            subscribeSwitch.checked = false
            ignoreSwitch.checked = false
            break;

        case SubscriptionState.Subscribed:
            unsubscribeSwitch.checked = false
            subscribeSwitch.checked = true
            ignoreSwitch.checked = false
            break;

        default:
            unsubscribeSwitch.checked = false
            subscribeSwitch.checked = false
            ignoreSwitch.checked = true
            break;
        }
    }

    Component.onCompleted: setSubcriptionState()

    onDone: {
        if (result != DialogResult.Accepted) return

        if (unsubscribeSwitch.checked)
            subscription = SubscriptionState.Unsubscribed
        else if (subscribeSwitch.checked)
            subscription = SubscriptionState.Subscribed
        else
            subscription = SubscriptionState.SubscriptionIgnored
    }
}
