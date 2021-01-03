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
                title: qsTr("Search Repository")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.enabled: text.length > 3
                EnterKey.iconSource: "image://theme/icon-m-search"
                EnterKey.onClicked: {
                    focus = false
                    SailHub.api().searchRepo(searchField.text, reposModel)
                }

                onTextChanged: {
                    if (text.length === 0) {
                        focus = true
                        reposModel.reset()
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
                text: qsTr("No repositories found")
                hintText: qsTr("Type in search pattern to find repositories")

            }

            model: ReposModel {
                id: reposModel
                modelType: Repo.Search
            }


            delegate: RepoListDelegate {
                id: delegate

                name: model.name
                description: model.description
                stargazerCount: model.stargazerCount
                //language: model.language
                languageColor: model.languageColor
                languageName: model.languageName
                lastItem: index == (listView.count - 1)

                onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                              nodeId: model.nodeId
                                          })
            }

            PushUpMenu {
                busy: reposModel.loading
                visible: reposModel.hasNextPage

                MenuItem {
                    text: qsTr("Load more (%n to go)", "", reposModel.totalCount - listView.count)
                    onClicked: SailHub.api().searchRepo(searchField.text, reposModel)
                }
            }
            VerticalScrollDecorator {}
        }
    }
}

