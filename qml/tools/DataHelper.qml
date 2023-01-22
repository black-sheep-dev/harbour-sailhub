pragma Singleton

import QtQuick 2.0

Item {
    function getEmojiFromHtml(html) {
        //console.log(html)
        //var emojiRegex = /(?<=unicode)(.*)(?=.png)/g;
        var emojiRegex = /unicode\/(.*)(?=.png)/
        //console.log(html.match(emojiRegex))
        return "https://cdn.nubecula.org/twemoji/svg/" + html.match(emojiRegex)[1] + ".svg"
    }
}
