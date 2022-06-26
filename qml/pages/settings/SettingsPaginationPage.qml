import QtQuick 2.0
import Sailfish.Silica 1.0

import ".."

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
                //% "Pagination settings"
                title: qsTrId("id-pagination-settings")
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
                //% "%n Item(s)"
                valueText: qsTrId("id-pagination-items-count", value)

                Component.onCompleted: value = settings.paginationCount
            }
        }
    }

    onStatusChanged: if (status == PageStatus.Deactivating) settings.paginationCount = itemCountSlider.value
}


