import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width

            PageHeader {
                title: qsTr("About")
            }

            Image {
                id: logo
                source: "/usr/share/icons/hicolor/512x512/apps/" + Qt.application.name + ".png"
                smooth: true
                height: parent.width / 2
                width: parent.width / 2
                sourceSize.height: 512
                sourceSize.width:  512
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 0.7
            }

            Item {
                height: Theme.paddingLarge
                width: 1
            }

            Label {
                width: parent.width
                x : Theme.horizontalPageMargin
                font.pixelSize: Theme.fontSizeExtraLarge
                color: Theme.secondaryHighlightColor

                text: qsTr("SailHub")
            }

            Label {
                width: parent.width
                x : Theme.horizontalPageMargin
                text: Qt.application.version
            }

            Item {
                height: Theme.paddingLarge
                width: 1
            }

            Label {
                width: parent.width - 2 * x
                x : Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall

                text: qsTr("SailHub is an inoffical GitHub app for Sailfish OS")
            }

            SectionHeader{
                text: qsTr("Sources")
            }
            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium

                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:///icons/git"
                    }

                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall

                        text: "https://github.com/black-sheep-dev/" + Qt.application.name
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor

                    }
                }
                onClicked: Qt.openUrlExternally("https://github.com/black-sheep-dev/" + Qt.application.name)
            }

            SectionHeader{
                text: qsTr("Donations")
            }

            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:///icons/paypal"
                    }
                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        text: qsTr("If you like my work you can buy me a beer.")
                    }
                }
                onClicked: Qt.openUrlExternally("https://www.paypal.com/paypalme/nubecula/1")
            }
        }
    }
}
