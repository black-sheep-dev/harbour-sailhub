import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string login
    property string identifier
    property int repoType

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: {
                switch (repoType) {
                case Repo.User:
                    return qsTr("Repositories");

                case Repo.Fork:
                    return qsTr("Forks");

                case Repo.Starred:
                    return qsTr("Starred Repositories")

                default:
                    return qsTr("Repositories");
                }
            }
            description: login
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: reposModel.loading
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    reposModel.reset()
                    SailHub.api().getRepos(reposModel)
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: reposModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No repositories available")
        }

        VerticalScrollDecorator {}

        model: ReposModel {
            id: reposModel
            identifier: page.identifier
            modelType: page.repoType
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: RepoListDelegate {
            id: delegate

            name: {
                switch (repoType) {
                case Repo.User:
                    return model.name

                default:
                    return model.owner + "/" + model.name
                }
            }
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
                onClicked: SailHub.api().getRepos(reposModel)
            }
        }
    }

    Component.onCompleted: {
        SailHub.api().getRepos(reposModel)
    }
}
