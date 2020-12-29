import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string identifier
    property int repoType

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Repositories")
            description: identifier
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: reposModel.loading
            MenuItem {
                text: qsTr("Refresh")
                onClicked: SailHub.api().getRepos(reposModel)
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

            name: model.name
            description: model.description
            stargazerCount: model.stargazerCount
            //language: model.language
            languageColor: model.languageColor
            languageName: model.languageName

            onClicked: pageStack.push(Qt.resolvedUrl("RepoPage.qml"), {
                                          nodeId: model.nodeId
                                      })
        }

        PushUpMenu {
            busy: loading
            visible: reposModel.hasNextPage

            MenuItem {
                text: qsTr("Load more")
                onClicked: SailHub.api().getRepos(reposModel)
            }
        }
    }

    Component.onCompleted: {
        SailHub.api().getRepos(reposModel)
    }
}
