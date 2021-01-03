import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Page {
    property string repoName
    property string identifier
    property int states: Issue.StateOpen

    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: PageHeader {
            title: qsTr("Issues")
            description: page.repoName
        }

        footer: Item {
            width: parent.width
            height: Theme.horizontalPageMargin
        }

        PullDownMenu {
            busy: issuesModel.loading
            MenuItem {
                text: {
                    if (page.states & Issue.StateOpen)
                        return qsTr("Show closed issues")
                    else if (page.states & Issue.StateClosed)
                        return qsTr("Show open issues")
                }

                onClicked: {
                    if (page.states & Issue.StateOpen)
                        page.states = Issue.StateClosed
                    else if (page.states & Issue.StateClosed)
                        page.states = Issue.StateOpen

                    issuesModel.modelType = page.states
                    issuesModel.reset()
                    SailHub.api().getIssues(issuesModel)
                }

            }

            MenuItem {
                text: qsTr("Create new Issue")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/EditIssueDialog.qml"))

                    dialog.accepted.connect(function() {
                        SailHub.api().createIssue(dialog.title, dialog.body, issuesModel)
                    })
                }
            }

            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    issuesModel.reset()
                    SailHub.api().getIssues(issuesModel)
                }
            }
        }

        BusyIndicator {
            id: busyIndicator
            visible: running
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: issuesModel.loading
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No issues available")
        }

        VerticalScrollDecorator {}

        model: IssuesModel {
            id: issuesModel
            identifier: page.identifier
            modelType: page.states
        }

        opacity: busyIndicator.running ? 0.3 : 1.0
        Behavior on opacity { FadeAnimator {} }

        delegate: IssueListDelegate {
            id: delegate

            commentCount: model.commentCount
            createdAt: model.createdAt
            number: model.number
            repoName: model.repository
            title: model.title
            state: model.state
            lastItem: index == (listView.count - 1)

            onClicked: pageStack.push(Qt.resolvedUrl("IssuePage.qml"), {
                                          nodeId: model.nodeId
                                      })

        }

        PushUpMenu {
            busy: issuesModel.loading
            visible: issuesModel.hasNextPage

            MenuItem {
                text: qsTr("Load more (%n to go)", "", issuesModel.totalCount - listView.count)
                onClicked: SailHub.api().getIssues(issuesModel)
            }
        }
    }

    Connections {
        target: SailHub.api()
        onIssueCreated: {
            issuesModel.reset()
            SailHub.api().getIssues(issuesModel)
        }
    }

    Component.onCompleted: SailHub.api().getIssues(issuesModel)
}

