import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import ".."
import "../components/"

Page {
    property string reponame
    property string username
    property Repo repo;

    id: page
    allowedOrientations: Orientation.All

    PageBusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: repo === undefined
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: headerColumn.height

        opacity: busyIndicator.running ? 0 : 1

        Behavior on opacity { FadeAnimation {} }

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("Add Star")
                description: username + "/" + reponame
            }

            CircleImage {
                id: avatarIcon
                width: parent.width / 2
                height: width
                anchors.horizontalCenter: parent.horizontalCenter

                fallbackItemVisible: false

                source: repo.owner.avatarUrl + "?size=" + Math.round(width)

                BusyIndicator {
                    size: BusyIndicatorSize.Medium
                    anchors.centerIn: avatarIcon
                    running: avatarIcon.status !== Image.Ready
                }
            }

            Item {
                width: 1
                height: Theme.paddingMedium
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                color: Theme.highlightColor

                text: qsTr("%1 says thank you for your star!").arg(username)
            }

            SectionHeader {
                text: qsTr("Support")
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Stargazer")
                value: repo.stargazerCount
                icon: "image://theme/icon-m-favorite-selected"

                onClicked: {
                    if (repo.stargazerCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                              title: qsTr("Stargazer"),
                                              description: repo.owner.login + "/" + repo.name,
                                              identifier: repo.nodeId,
                                              userType: User.Stargazer
                                          })
                }
            }

            RelatedValueItem {
                visible: repo.hasFundingLinks
                width: parent.width

                label: qsTr("Sponsoring")
                icon: "qrc:/icons/icon-m-heart"

                showValue: false

                onClicked: {
                    pageStack.push(Qt.resolvedUrl("FundingLinksListPage.qml"), {
                                                      identifier: repo.nodeId,
                                                  })
                }
            }
        }
    }

    Connections {
        target: SailHub.api()
        onRepoAvailable: {
            if (repo === undefined) return
            page.repo = repo
            SailHub.api().addStar(repo.nodeId)
        }
    }

    Component.onCompleted: SailHub.api().getRepo(username, reponame)
}
