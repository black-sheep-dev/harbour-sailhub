import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        size: BusyIndicatorSize.Large
        running: SailHub.reposSearchModel().loading
    }

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Search Repositories")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.onClicked: {
                    focus = false
                    SailHub.searchRepos(text)
                }

                onTextChanged: if (text.length == 0) SailHub.reposSearchModel().reset()
            }
        }

        SilicaListView {
            id: listView

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            clip: true

            opacity: busyIndicator.running ? 0.3 : 1.0
            Behavior on opacity { FadeAnimator {} }

            model: SailHub.reposSearchModel()

            delegate: RepoListDelegate {
                id: delegate

                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Watch");
                        onClicked: remorse.execute(delegate, qsTr("Watch repository"), function() {
                            SailHub.followRepo(model.fullName)
                        })
                    }
                }

                RemorseItem { id: remorse }

                title: model.fullName
                stargazers: model.stargazers
                language: model.language
                lastUpdate: model.updatedAt


                onClicked: pageStack.push(Qt.resolvedUrl("RepoDetailsPage.qml"), { repo: SailHub.reposSearchModel().repoAt(idx) })
            }

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No repositories found")
            }

            VerticalScrollDecorator {}
        }
    }

    Component.onCompleted: SailHub.reposSearchModel().reset()
}

