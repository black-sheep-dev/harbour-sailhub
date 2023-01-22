import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Dialog {
    property string subscription

    Column {
        width: parent.width
        spacing: Theme.paddingLarge

        DialogHeader {
            //% "Choose subscription"
            title: qsTrId("id-choose-subscription")
            //% "Select"
            acceptText: qsTrId("id-select")
        }

        TextSwitch {
            id: ignoreSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Unsubscribe"
            text: qsTrId("id-unsubscribe")
            //% "Disable all notifications"
            description: qsTrId("id-disable-all-notifications")

            checked: subscription === "IGNORED"
            onClicked: {
                checked = true
                unsubscribeSwitch.checked = false
                subscribeSwitch.checked = false
                subscription = "IGNORED"
            }
        }

        TextSwitch {
            id: unsubscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Subscribe"
            text: qsTrId("id-subscribe")
            //% "Get notified only when participating or mentioned"
            description: qsTrId("id-get-notified-subscribe-desc")

            checked: subscription === "UNSUBSCRIBED"
            onClicked: {
                checked = true
                ignoreSwitch.checked = false
                subscribeSwitch.checked = false
                subscription = "UNSUBSCRIBED"
            }
        }

        TextSwitch {
            id: subscribeSwitch
            x: Theme.horizontalPageMargin
            width: parent.width - 2*x

            //% "Subscribe (all)"
            text: qsTrId("id-subscribe-all");
            //% "Get notified of all conversation"
            description: qsTrId("id-get-notified-of-all-conversation")

            checked: subscription === "SUBSCRIBED"
            onClicked: {
                checked = true
                ignoreSwitch.checked = false
                unsubscribeSwitch.checked = false
                subscription = "SUBSCRIBED"
            }
        }
    }
}
