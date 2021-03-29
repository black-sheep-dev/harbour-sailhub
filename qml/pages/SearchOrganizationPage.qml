import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Search Organization")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.enabled: text.length > 2
                EnterKey.iconSource: "image://theme/icon-m-search"
                EnterKey.onClicked: {
                    focus = false
                    SailHub.api().searchOrganization(searchField.text, organizationsModel)
                }

                onTextChanged: {
                    if (text.length === 0) {
                        focus = true
                        organizationsModel.reset()
                    }
                }
            }
        }

        SilicaListView {
            id: listView

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom

            clip: true

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No organization found")
                hintText: qsTr("Type in search pattern to find organizations")

            }

            model: OrganizationsModel {
                id: organizationsModel
                modelType: Organization.Search
            }

            delegate: OrganizationListDelegate {
                id: delegate

                onClicked: pageStack.push(Qt.resolvedUrl("OrganizationPage.qml"), {
                                              nodeId: model.nodeId
                                          })
            }

            PushUpMenu {
                busy: organizationsModel.loading
                visible: organizationsModel.hasNextPage

                MenuItem {
                    text: qsTr("Load more (%n to go)", "", organizationsModel.totalCount - listView.count)
                    onClicked: SailHub.api().searchOrganization(searchField.text, organizationsModel)
                }
            }
            VerticalScrollDecorator {}
        }
    }
}


