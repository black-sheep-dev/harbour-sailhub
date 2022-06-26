import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import '..'

Dialog {
    property var emoji

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
            width: Theme.iconSizeMedium
            height: width

            Image {
                id: emojiIcon
                anchors.centerIn: parent
                width: Theme.iconSizeSmall
                height: width

                sourceSize.width: width
                sourceSize.height: width

                source: "https://cdn.nubecula.org/twemoji/svg/" + model.name + ".svg"
            }

            onClicked: {
                const parts = model.name.split("-")
                const code = ""

                parts.forEach(function (value, index, array) {
                    code +=  Twemoji.twemoji.convert.fromCodePoint(value)
                })

                emoji = code
                console.log(code)
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
