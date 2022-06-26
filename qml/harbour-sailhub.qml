import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Notifications 1.0
import Nemo.DBus 2.0
import Nemo.Configuration 1.0

import "objects"
import "pages"
import "tools"

import org.nubecula.harbour.sailhub 1.0

ApplicationWindow
{
    id: appWindow

//    DBusAdaptor {
//        service: 'org.nubecula.sailhub'
//        iface: 'org.nubecula.sailhub'
//        path: '/org/nubecula/sailhub'

//        xml: '<interface name="org.nubecula.sailhub">\n' +
//             '  <method name="addStar">\n' +
//             '      <arg name="username" type="s" direction="in">\n' +
//             '      </arg>\n' +
//             '      <arg name="reponame" type="s" direction="in">\n' +
//             '      </arg>\n' +
//             '  </method>\n' +
//             '  <method name="openUrl">\n' +
//             '      <arg name="arguments" type="a{sv}" direction="in">\n' +
//             '      </arg>\n' +
//             '  </method>\n' +
//             '</interface>'

//        function onAddStar(username, reponame) {
//            console.log(username + "/" +reponame)

//        }

//        function onOpenUrl(arguments) {
//            console.log(arguments)
//        }
//    }

    ConfigurationGroup {
        id: settings
        path: "/apps/harbour-sailhub/app"
        synchronous: true

        property int paginationCount: 20
    }

//    Connections {
//        target: dbus

//        onPleaseAddStar: {
//            __silica_applicationwindow_instance.activate()
//            pageStack.push(Qt.resolvedUrl("pages/AddStarPage.qml"), { reponame: reponame, username: username })
//        }

//        onPleaseOpenUrl: {
//            console.log(url)
//            __silica_applicationwindow_instance.activate()
//            linkHelper.openLink(url)
//        }
//    }

    // Viewer Profile
    ViewerProfile { id: viewerProfile }

    Notification {
        function show(message, icn) {
            replacesId = 0
            previewSummary = ""
            previewBody = message
            icon = icn || ""
            publish()
        }
        function showPopup(title, message, icn) {
            replacesId = 0
            previewSummary = title
            previewBody = message
            icon = icn
            publish()
        }

        function showCustomErrorMessage(msg) {
            replacesId = 0
            previewSummary = ""
            //% "Error"
            previewBody = qsTrId("id-error") + ": " + msg
            icon = icn || ""
            publish()
        }

        function showErrorMessage(error) {
            //% "Error"
            const msg = qsTrId("id-error") + ": "

            switch (error) {
            case QueryObject.ErrorNone:
                return

            case QueryObject.ErrorNotFound:
                //% "Not found!"
                msg += qsTrId("id-api-error-not-found")
                break

            case QueryObject.ErrorInvalidData:
                //% "Received invalid data!"
                msg += qsTrId("id-api-error-invalid-data")
                break

            case QueryObject.ErrorQuery:
                //% "Query failed with bad parameters!"
                msg += qsTrId("id-api-error-query")
                break

            case QueryObject.ErrorTimeout:
                //% "Connection timeout!"
                msg += qsTrId("id-api-error-connection-timeout")
                break

            case QueryObject.ErrorUnauthorized:
                //% "User is unauthorized!"
                msg += qsTrId("id-api-error-unauthorized")
                break

            default:
                //% "An unkown error occured!"
                msg += qsTrId("id-api-error-unknown")
                break
            }
            replacesId = 0
            previewSummary = ""
            previewBody = msg
            icon = ""
            publish()
        }

        id: notification
        appName: "SailHub"
        expireTimeout: 3000
    }

//    LinkHelper {
//        property string username
//        property string repo
//        property string destination

//        id: linkHelper

//        onPleaseOpenLink: {
//            linkHelper.username = username
//            linkHelper.repo = repo
//            linkHelper.destination = destination
//            SailHub.api().getRepoId(username, repo)
//        }

//        Connections {
//            target: SailHub.api()
//            onRepoIdAvailable: {
//                if (repo.nodeId.length === 0) {
//                    //% "Repo doesn't exist!"
//                    notification.show(qsTrId("id-repo-doesnt-exist"))
//                    return
//                }

//                if (linkHelper.destination === "repo" || linkHelper.destination === "unsupported") {
//                    //% "Endpoint unsupported!"
//                    if (linkHelper.destination === "unsupported") notification.show(qsTrId("id-endpoint-unsupported"))

//                    pageStack.push(Qt.resolvedUrl("pages/RepoPage.qml"), {
//                                       repo: repo
//                                   })
//                } else if (linkHelper.destination === "discussions") {
//                    pageStack.push(Qt.resolvedUrl("pages/DiscussionsListPage.qml"), {
//                                       description: repo.owner.login + "/" + repo.name,
//                                       identifier: repo.nodeId
//                                   })
//                } else if (linkHelper.destination === "issues") {
//                    pageStack.push(Qt.resolvedUrl("pages/IssuesListPage.qml"), {
//                                              description: repo.owner.login + "/" + repo.name,
//                                              identifier: repo.nodeId,
//                                              type: Issue.Repo,
//                                              states: IssueState.Open
//                                          })
//                } else if (linkHelper.destination === "pulls") {
//                    pageStack.push(Qt.resolvedUrl("pages/PullRequestsListPage.qml"), {
//                                              description: repo.owner.login + "/" + repo.name,
//                                              identifier: repo.nodeId,
//                                              type: PullRequest.Repo,
//                                              states: PullRequest.Open
//                                          })
//                }

//                linkHelper.username = ""
//                linkHelper.repo = ""
//                linkHelper.destination = ""
//            }
//        }
//    }

    initialPage: Component { OverviewPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Component.onCompleted: Api.init()
}
