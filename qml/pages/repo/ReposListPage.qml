import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: SailHub.reposModel().loading
    }

    SilicaListView {
        PullDownMenu {
            MenuItem {
                text: qsTr("Search")
                onClicked: pageStack.push(Qt.resolvedUrl("ReposSearchPage.qml"))
            }
        }

        id: listView
        model: SailHub.reposModel()

        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Repositories")
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: RepoListDelegate {
            id: delegate

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Delete");
                    onClicked: remorse.execute(delegate, qsTr("Delete repository"), function() {
                        SailHub.reposModel().removeNode()
                        SailHub.saveSettings()
                    })
                }
            }

            RemorseItem { id: remorse }

            title: model.fullName
            stargazers: model.stargazers
            language: model.language
            lastUpdate: model.updatedAt


            onClicked: pageStack.push(Qt.resolvedUrl("RepoDetailsPage.qml"), { repo: SailHub.reposModel().repoAt(idx) })
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No repositories available")
            hintText: qsTr("Pull down to search for repositories you like to watch")
        }

        VerticalScrollDecorator {}
    }
}
