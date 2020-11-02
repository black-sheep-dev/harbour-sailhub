import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../../components/"

Page {
    property Repo repo

    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                enabled: repo !== undefined
                text: qsTr("Watch")
                onClicked: SailHub.followRepo(repo.fullName)
            }
        }

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            x: Theme.horizontalPageMargin
            width: parent.width - 2*x
            spacing: Theme.paddingSmall

            PageHeader {
                title: repo.name
            }

        }
    }
}

