import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    property ProfileStatus profileStatus

    id: page

    allowedOrientations: Orientation.All

    function apply() {
        profileStatus.message = messageField.text
        profileStatus.indicatesLimitedAvailability = limitedAvailabilitySwitch.checked
        profileStatus.expireStatus = clearStatusComboBox.currentIndex
    }

    RemorsePopup { id: remorse }

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                visible: profileStatus.message.length > 0
                //% "Clear status"
                text: qsTrId("id-clear-status")
                //% "Clearing status"
                onClicked: remorse.execute(qsTrId("id-clearing-status"), function() {
                    SailHub.api().clearProfileStatus(profileStatus)
                    pageStack.navigateBack()
                })
            }
            MenuItem {
                //% "Change status"
                text: qsTrId("id-change-status")
                onClicked: {
                    apply()
                    SailHub.api().updateProfileStatus(profileStatus)
                }
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
                        if (profileStatus.emojiImage.length > 0)
                            return profileStatus.emojiImage
                        else
                            return "qrc:///emoji/default"
                    }
                }

                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SelectEmojiDialog.qml"))

                    dialog.accepted.connect(function() {
                        profileStatus.emoji = dialog.emojiUnicode
                        profileStatus.emojiImage = "/usr/share/harbour-twemoji/72x72/" + dialog.emoji + ".png"
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

                text: profileStatus.message

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

                checked: profileStatus.indicatesLimitedAvailability
            }

            SectionHeader {
                //% "Clear status"
                text: qsTrId("id-clear-status")
            }


            ComboBox {
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

                currentIndex: profileStatus.expireStatus
            }
        }
    }
}
