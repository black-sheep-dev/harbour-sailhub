import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import ".."

Page {
    id: page

    allowedOrientations: Orientation.All

    function apply() {
        viewerProfile.profileStatus.message = messageField.text
        viewerProfile.profileStatus.indicatesLimitedAvailability = limitedAvailabilitySwitch.checked

        if (clearStatusComboBox.currentIndex !== 0) {
            viewerProfile.profileStatus.expiresAt = clearStatusComboBox.expiresAt.toISOString()
        } else {
            viewerProfile.profileStatus.expiresAt =  ""
        }

        viewerProfile.updateStatus()
    }

    RemorsePopup { id: remorse }

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                visible: viewerProfile.profileStatus.message.length > 0
                //% "Clear status"
                text: qsTrId("id-clear-status")
                //% "Clearing status"
                onClicked: remorse.execute(qsTrId("id-clearing-status"), function() {
                    viewerProfile.clearStatus()
                    pageStack.navigateBack()
                })
            }
            MenuItem {
                //% "Change status"
                text: qsTrId("id-change-status")
                onClicked: apply()
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                //% "Status"
                title: qsTrId("id-status")
            }

            BackgroundItem {
                x: Theme.horizontalPageMargin
                width: emojiImage.height + Theme.paddingSmall
                height: width

                Image {
                    id: emojiImage
                    anchors.centerIn: parent
                    width: Theme.iconSizeMedium
                    height: width
                    sourceSize.width: width
                    sourceSize.height: width

                    source: {
                        if (viewerProfile.profileStatus !== null)
                            return DataUtils.getEmojiUrl(viewerProfile.profileStatus.emoji)
                        else
                            return "qrc:///emoji/default"
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectEmojiDialog.qml"))

                    dialog.accepted.connect(function() {
                        if (viewerProfile.profileStatus === null) viewerProfile.profileStatus = {}
                        viewerProfile.profileStatus.emoji = dialog.emoji
                        emojiImage.source = DataUtils.getEmojiUrl(dialog.emoji)
                    })
                }
            }

            TextField {
                id: messageField
                width: parent.width

                //% "Message"
                label: qsTrId("id-message")
                focus: true

                //% "Enter message"
                placeholderText: qsTrId("id-enter-message")

                text: viewerProfile.profileStatus.message

                maximumLength: 80
            }

            TextSwitch {
                id: limitedAvailabilitySwitch
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                //% "Busy"
                text: qsTrId("id-busy")
                //% "When others mention you, assign you, or request your review, GitHub will let them know that you have limited availability."
                description: qsTrId("id-busy-switch-desc")

                checked: viewerProfile.profileStatus.indicatesLimitedAvailability
            }

            SectionHeader {
                //% "Clear status"
                text: qsTrId("id-clear-status")
            }

            DetailItem {
                visible: viewerProfile.profileStatus !== null &&
                         (new Date(viewerProfile.profileStatus.expiresAt) > new Date() || clearStatusComboBox.currentIndex !== 0)
                //% "Expires at"
                label: qsTrId("id-expires-at")
                value: clearStatusComboBox.currentIndex !== 0 ?
                           clearStatusComboBox.expiresAt.toLocaleString() :
                           new Date(viewerProfile.profileStatus.expiresAt).toLocaleString()
            }

            ComboBox {
                property date expiresAt

                id: clearStatusComboBox
                //% "Clear status"
                label: qsTrId("id-clear-status")
                menu: ContextMenu {
                    MenuItem {
                        //% "Never"
                        text: qsTrId("id-never")
                    }
                    MenuItem {
                        //% "in 30 minutes"
                        text: qsTrId("id-in-thirty-minutes")
                    }
                    MenuItem {
                        //% "in 1 hour"
                        text: qsTrId("id-in-one-hour")
                    }
                    MenuItem {
                        //% "in 4 hours"
                        text: qsTrId("id-in-four-hours")
                    }
                    MenuItem {
                        //% "today"
                        text: qsTrId("id-today")
                    }
                    MenuItem {
                        //% "this week"
                        text: qsTrId("id-this-week")
                    }
                }

                onCurrentIndexChanged: {
                    const currentDate = new Date()

                    switch (currentIndex) {

                    case 1:
                        expiresAt = new Date(currentDate.getTime() + 30*60000)
                        break;

                    case 2:
                        expiresAt = new Date(currentDate.getTime() + 60*60000)
                        break;

                    case 3:
                        expiresAt = new Date(currentDate.getTime() + 4*60*60000)
                        break;

                    case 4:
                        const currentDay = currentDate
                        currentDay.setHours(23, 59, 59, 999)
                        expiresAt = currentDay
                        break;

                    case 5:
                        const currentSunday = currentDate
                        currentSunday.setHours(23, 59, 59, 999)
                        currentSunday.setDate(currentSunday.getDate() - currentSunday.getDay() + 7);
                        expiresAt = currentSunday
                        break;

                    default:
                        expiresAt = new Date().setTime(0)
                        break;
                    }

                    console.log(expiresAt)
                }
            }
        }
    }

    Component {
        id: pickerComponent
        DatePickerDialog {}
    }
}
