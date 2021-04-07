import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("Settings")
            }

            PasswordField {
                id: tokenField
                width: parent.width

                label: qsTr("Access Token")

                placeholderText: qsTr("Enter access token")
            }

            SectionHeader {
                text: qsTr("Pagination")
            }
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap

                text: qsTr("Choose the number of items to fetch in a single query. This value should be between 1-100.")
                color: Theme.highlightColor
            }

            Slider {
                id: itemCountSlider
                width: parent.width
                minimumValue: 1
                maximumValue: 100
                value: 20
                valueText: qsTr("%n Item(s)", "", value)

                Component.onCompleted: value = SailHub.api().paginationCount

                onValueChanged: SailHub.api().paginationCount = value
            }
        }
    }

    onStatusChanged: {
        if (status == PageStatus.Deactivating) {
            if (tokenField.text.length > 0) SailHub.accessToken = tokenField.text

            SailHub.saveSettings()
        }
    }
}

