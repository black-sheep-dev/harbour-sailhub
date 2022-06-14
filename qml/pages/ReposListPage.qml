import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"
import "../tools/"
import ".."

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
                    //% "Repositories"
                    return qsTrId("id-repositories");

                case Repo.Fork:
                    //% "Forks"
                    return qsTrId("id-forks");

                case Repo.Starred:
                    //% "Starred repositories"
                    return qsTrId("id-starred-repositories")

                default:
                    //% "Repositories"
                    return qsTrId("id-repositories");
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
                //% "Refresh"
                text: qsTrId("id-refresh")
                onClicked: refresh()
            }

            MenuItem {
                //% "Sorting"
                text: qsTrId("id-sorting")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/SortSelectionDialog.qml"), {
                                                    order: config.sortOrder,
                                                    field: getSortFieldIndex(),
                                                    fields: [
                                                        //% "Name"
                                                        qsTrId("id-name"),
                                                        //% "Created at"
                                                        qsTrId("id-created-at"),
                                                        //% "Pushed at"
                                                        qsTrId("id-pushed-at"),
                                                        //% "Updated at"
                                                        qsTrId("id-updated-at"),
                                                        //% "Stargazers"
                                                        qsTrId("id-stargazers")
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
            //% "No repositories available"
            text: qsTrId("id-no-repositories-available")
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
                    return model.ownerLogin + "/" + model.name
                }
            }
            description: MarkdownParser.parseRaw(model.description)

            onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: reposModel.loading
            visible: reposModel.hasNextPage

            MenuItem {
                //% "Load more (%n to go)"
                text: qsTrId("id-load-more",  reposModel.totalCount - listView.count)
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
    Component.onDestruction: delete reposModel
}
