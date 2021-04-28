import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../delegates/"

Dialog {
    id: dialog
    property string selected
    property alias repoId: categoriesModel.identifier

    canAccept: selected.length > 0

    DialogHeader {
        id: header
        title: qsTr("Select Category")
        acceptText: qsTr("Select")
    }

    SilicaListView {
        id: listView
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        model: DiscussionCategoriesModel {
            id: categoriesModel
        }

        delegate: DiscussionCategoryListDelegate {
            Image {
                id: selectedIcon

                visible: false

                source: "image://theme/icon-m-acknowledge"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: {
                selected = model.nodeId
                accept();
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No categories available")
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: SailHub.api().getPaginationModel(categoriesModel)
}
