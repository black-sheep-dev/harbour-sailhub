import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    id: page

    allowedOrientations: Orientation.All

    PageBusyIndicator {
        anchors.centerIn: parent
        running: searchModel.loading
        size: Theme.itemSizeLarge
    }

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                //% "Search repository"
                title: qsTrId("id-search-repository")
            }

            SearchField {
                id: searchField
                width: parent.width

                focus: true

                EnterKey.enabled: text.length > 2
                EnterKey.iconSource: "image://theme/icon-m-search"
                EnterKey.onClicked: {
                    focus = false
                    searchModel.reset()
                    searchModel.searchPattern = searchField.text
                    SailHub.api().getPaginationModel(searchModel)
                }

                onTextChanged: {
                    if (text.length === 0) {
                        focus = true
                        searchModel.reset()
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

            //opacity: searchModel.loading ? 0 : 1
            //Behavior on opacity { FadeAnimation {} }

            ViewPlaceholder {
                enabled: listView.count == 0
                //% "No repositories found"
                text: qsTrId("id-no-repositories-found")
                //% "Type in search pattern to find repositories"
                hintText: qsTrId("id-no-repositories-found-hint")

            }

            model: ReposModel {
                id: searchModel
                modelType: Repo.Search
            }


            delegate: RepoListDelegate {
                id: delegate

                name: model.name

                onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                              nodeId: model.nodeId
                                          })
            }

            PushUpMenu {
                busy: searchModel.loading
                visible: searchModel.hasNextPage

                MenuItem {
                    //% "Load more (%n to go)"
                    text: qsTrId("id-load-more", searchModel.totalCount - listView.count)
                    onClicked: SailHub.api().getPaginationModel(searchModel)
                }
            }
            VerticalScrollDecorator {}
        }
    }

    Component.onDestruction: delete searchModel
}

