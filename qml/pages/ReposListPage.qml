import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string login
    property alias identifier: reposModel.identifier
    property alias repoType: reposModel.modelType
    property alias sortRole: reposModel.sortRole
    property alias sortOrder: reposModel.sortOrder

    ConfigurationGroup {
        id: config
        path: "/apps/harbour-sailhub/repos"

        property alias sortRole: reposModel.sortRole
        property alias sortOrder: reposModel.sortOrder
    }

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
                onClicked: refresh()
            }

            MenuItem {
                text: qsTr("Sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: config.sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        qsTr("Name"),
                                                        qsTr("Created at"),
                                                        qsTr("Pushed at"),
                                                        qsTr("Updated at"),
                                                        qsTr("Stargazers")
                                                    ]
                                                })

                    dialog.accepted.connect(function() {
                        config.sortOrder = dialog.order
                        config.sortRole = getSortRoleFromIndex(dialog.field)

                        refresh()
                    })
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

        model: ReposModel { id: reposModel }

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
                onClicked: getRepos()
            }
        }
    }

    function getRepos() {
        SailHub.api().getPaginationModel(reposModel)
    }

    function getSortRoleFromIndex(index) {
        switch (index) {
        case 0:
            return ReposModel.NameRole

        case 1:
            return ReposModel.CreatedAtRole

        case 2:
            return ReposModel.PushedAtRole

        case 3:
            return ReposModel.UpdatedAtRole

        case 4:
            return ReposModel.StargazerCountRole

        default:
            return ReposModel.NameRole
        }
    }

    function getSortFieldIndex() {
        switch (config.sortRole) {
        case ReposModel.NameRole:
            return 0;

        case ReposModel.CreatedAtRole:
            return 1;

        case ReposModel.PushedAtRole:
            return 2;

        case ReposModel.UpdatedAtRole:
            return 3;

        case ReposModel.StargazerCountRole:
            return 4;

        default:
            return 0
        }
    }

    function refresh() {
        reposModel.reset()
        getRepos()
    }

    Component.onCompleted: refresh()
}
