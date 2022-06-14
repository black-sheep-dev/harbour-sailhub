import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import '..'

Dialog {
    property string emoji
    property var emojiUnicode

    DialogHeader {
        id: header
        //% "Choose Emoji"
        title: qsTrId("id-choose-emoji")
        //% "Select"
        acceptText: qsTrId("id-select")
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
                anchors.margins: Theme.paddingSmall
                width: Theme.iconSizeMedium
                height: width

                sourceSize.width: width
                sourceSize.height: width

                source: "/usr/share/harbour-sailhub/twemoji/svg/" + model.name + ".svg"
            }

            onClicked: {
                emoji = model.name
                emojiUnicode = Twemoji.twemoji.convert.fromCodePoint(model.name)
                accept()
            }
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            //% "No emoji available"
            text: qsTrId("id-no-emoji-available")
        }

        VerticalScrollDecorator {}
    }
}
