import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string description
    property alias identifier: fundingLinksModel.identifier

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            //% "Sponsor"
            title: qsTrId("id-sponsor")
            description: page.description
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: fundingLinksModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No funding links available"
            text: qsTrId("id-no-funding-links-available")
        }

        VerticalScrollDecorator {}

        model: FundingLinksModel { id: fundingLinksModel }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: ListItem {
            id: delegate
            width: parent.width
            contentHeight: Theme.itemSizeMedium

            Row {
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.horizontalPageMargin
                width: parent.width - 2
                spacing: Theme.paddingMedium

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    height: Theme.iconSizeMedium
                    width: Theme.iconSizeMedium

                    source: {
                        switch (model.platform) {
                        case FundingLink.CommunityBridge:
                            return "https://mentorship.lfx.linuxfoundation.org/assets/favicons/mstile-144x144.png"

                        case FundingLink.GitHub:
                            return "qrc:///icons/git"

                        case FundingLink.IssueHunt:
                            return "https://issuehunt.io/static/logo.png"

                        case FundingLink.KoFi:
                            return "https://ko-fi.com/apple-touch-icon.png"

                        case FundingLink.Liberpay:
                            return "qrc:///icons/liberpay"

                        case FundingLink.OpenCollective:
                            return "https://opencollective.com/static/images/opencollective-icon.svg"

                        case FundingLink.Otechie:
                            return "https://cdn.otechie.com/attachments/Yf6W1eiVZ/image.png"

                        case FundingLink.Patreon:
                            return "https://c5.patreon.com/external/favicon/apple-touch-icon.png?v=jw6AR4Rg74"

                        case FundingLink.Tidelift:
                            return "https://cdn2.hubspot.net/hubfs/4008838/website/icons/Tidelift_Favicon.png"

                        default:
                            return "image://theme/icon-m-presence"
                        }
                    }
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter

                    text: model.name
                }
            }

            onClicked: Qt.openUrlExternally(model.url)
        }

    }

    Component.onCompleted: SailHub.api().getModel(fundingLinksModel)
    Component.onDestruction: delete fundingLinksModel
}

