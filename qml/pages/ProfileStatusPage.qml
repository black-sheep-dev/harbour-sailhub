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
                text: qsTr("Clear status")
                onClicked: remorse.execute(qsTr("Clearing status"), function() {
                    SailHub.api().clearProfileStatus(profileStatus)
                    pageStack.navigateBack()
                })
            }
            MenuItem {
                text: qsTr("Change status")
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
                title: qsTr("Status")
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

                label: qsTr("Message")
                focus: true

                placeholderText: qsTr("Enter message")

                text: profileStatus.message

                maximumLength: 80
            }

            TextSwitch {
                id: limitedAvailabilitySwitch
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                text: qsTr("Busy")
                description: qsTr("When others mention you, assign you, or request your review, GitHub will let them know that you have limited availability.")

                checked: profileStatus.indicatesLimitedAvailability
            }

            SectionHeader {
                text: qsTr("Clear status")
            }


            ComboBox {
                id: clearStatusComboBox
                label: qsTr("Clear status")
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Never")
                    }
                    MenuItem {
                        text: qsTr("in 30 minutes")
                    }
                    MenuItem {
                        text: qsTr("in 1 hour")
                    }
                    MenuItem {
                        text: qsTr("in 4 hour")
                    }
                    MenuItem {
                        text: qsTr("today")
                    }
                    MenuItem {
                        text: qsTr("this week")
                    }
                }

                currentIndex: profileStatus.expireStatus
            }
        }
    }
}
