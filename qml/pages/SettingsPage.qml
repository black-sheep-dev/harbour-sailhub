import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        MenuItem {
            //% "Reset authentication"
            text: qsTrId("id-reset-authentication")
            //% "Resetting credentials and close app"
            onClicked: remorse.execute(qsTrId("id-resseting-credentials"), function() {
                settings.accessToken = ""
                Qt.quit()
            })
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                //% "Settings"
                title: qsTrId("id-settings")
            }

            SectionHeader {
                //% "Notifications"
                text: qsTrId("id-notifications")
            }

            TextSwitch {
                id: notifySwitch
                //% "Notifications"
                text: qsTrId("id-notifications")
                //% "Get notified of activities on your GitHub account. The update interval is set to 2.5 minutes by default due to GitHub api requirements."
                description: qsTrId("id-settings-notifications-desc")

                onCheckedChanged: settings.notify = checked

                Component.onCompleted: checked = settings.notify
            }

            SectionHeader {
                //% "Pagination"
                text: qsTrId("id-pagination")
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap

                //% "Choose the number of items to fetch in a single query. This value should be between 10-100."
                text: qsTrId("id-pagination-settings-desc")
                color: Theme.highlightColor
            }

            Slider {
                id: itemCountSlider
                width: parent.width
                minimumValue: 10
                maximumValue: 100
                value: 20
                //% "%n item(s)"
                valueText: qsTrId("id-pagination-items-count", value)

                Component.onCompleted: value = settings.paginationCount
            }

//            SectionHeader {
//                //% "Authentication"
//                text: qsTrId("id-authentication")
//            }

//            PasswordField {
//                id: tokenField
//                width: parent.width
//                focus: true
//                validator: RegExpValidator {
//                    regExp: /^ghp_+/
//                }
//                //% "Access token"
//                label: qsTrId("id-access-token")
//                //% "Enter access token"
//                placeholderText: qsTrId("id-enter-access-token")
//            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                visible: !tokenField.acceptableInput && tokenField.length > 4
                //% "This token does not appear to be a GitHub token!"
                text: qsTrId("id-no-github-token")
                color: Theme.errorColor
                font.pixelSize: Theme.fontSizeExtraSmall
            }

            SectionHeader {
                //% "Develop"
                text: qsTrId("id-develop")
            }

            TextSwitch {
                id: apiDebugSwitch
                //% "API Debug"
                text: qsTrId("id-api-debug")
                //% "Turn on API debugging. All API requests and replies are print to console."
                description: qsTrId("id-settings-api-debug-desc")

                onCheckedChanged: settings.apiDebug = checked

                Component.onCompleted: checked = settings.apiDebug
            }
        }
    }
}

