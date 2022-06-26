import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../views/"
import "../delegates/"

ListPage {
    id: page
    allowedOrientations: Orientation.All

    itemsPath: ["node", "fundingLinks"]

    itemsQuery: '
    query($nodeId: ID!) {
        node(id: $nodeId) {
            ... on Repository {
                fundingLinks {
                    platform
                    url
                }
            }
        }
    }'

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

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No funding links available"
            text: qsTrId("id-no-funding-links-available")
        }

        VerticalScrollDecorator {}

        model: itemsModel

        opacity: loading ? 0.0 : 1.0
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
                        switch (item.platform) {
                        case "COMMUNITY_BRIDGE":
                            return "https://mentorship.lfx.linuxfoundation.org/assets/favicons/mstile-144x144.png"

                        case "GITHUB":
                            return "qrc:///icons/git"

                        case "ISSUEHUNT":
                            return "https://issuehunt.io/static/logo.png"

                        case "KO_FI":
                            return "https://ko-fi.com/apple-touch-icon.png"

                        case "LIBERAPAY":
                            return "qrc:///icons/liberpay"

                        case "OPEN_COLLECTIVE":
                            return "https://opencollective.com/static/images/opencollective-icon.svg"

                        case "OTECHIE":
                            return "https://cdn.otechie.com/attachments/Yf6W1eiVZ/image.png"

                        case "PATREON":
                            return "https://c5.patreon.com/external/favicon/apple-touch-icon.png?v=jw6AR4Rg74"

                        case "TIDELIFT":
                            return "https://cdn2.hubspot.net/hubfs/4008838/website/icons/Tidelift_Favicon.png"

                        default:
                            return "image://theme/icon-m-presence"
                        }
                    }
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter

                    text: item.platform
                }
            }

            onClicked: Qt.openUrlExternally(item.url)
        }

    }

    Component.onCompleted: refresh()
}

