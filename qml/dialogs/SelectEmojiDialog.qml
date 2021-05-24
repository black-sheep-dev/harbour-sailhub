import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import '..'

Dialog {
    property string emoji
    property var emojiUnicode

    DialogHeader {
        id: header
        title: qsTr("Choose Emoji")
        acceptText: qsTr("Select")
    }

    SilicaGridView {
        id: listView
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        model: EmojiModel {}

        delegate: BackgroundItem {
            width: Theme.iconSizeMedium + Theme.paddingMedium
            height: width

            Image {
                id: emojiIcon
                anchors.centerIn: parent
                width: Theme.iconSizeMedium
                height: width

                sourceSize.width: width
                sourceSize.height: width

                source: "/usr/share/harbour-twemoji/svg/" + model.name + ".svg"
            }

            onClicked: {
                emoji = model.name
                emojiUnicode = Twemoji.twemoji.convert.fromCodePoint(model.name)
                accept()
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: qsTr("No emoji available")
        }

        VerticalScrollDecorator {}
    }
}
