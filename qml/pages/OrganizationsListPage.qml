import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string title
    property string identifier
    property int organizationType: Organization.Undefined

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader { title: page.title }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: organizationsModel.loading
            MenuItem {
                text: qsTr("Refresh")
                onClicked: refresh()
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: organizationsModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No organizations available")
        }

        VerticalScrollDecorator {}

        model: OrganizationsModel {
            id: organizationsModel
            identifier: page.identifier
            modelType: page.organizationType
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

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
                onClicked: getOrganizations()
            }
        }
    }

    function getOrganizations() {
        SailHub.api().getPaginationModel(organizationsModel)
    }

    function refresh() {
        organizationsModel.reset()
        getOrganizations()
    }

    Component.onCompleted: refresh()
    Component.onDestruction: delete organizationsModel
}
