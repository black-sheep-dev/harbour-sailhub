import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/showdown.js" as ShowDown

Item {
    property var showdown: ShowDown.showdown
    property var converter: new showdown.Converter({
                                    simplifiedAutoLink: true,
                                    excludeTrailingPunctuationFromURLs: true,
                                    strikethrough: true,
                                    tables: true,
                                    tasklists: false,
                                    parseImgDimensions: true,
                                    simpleLineBreaks: true,
                                    emoji: true })

    function parse(content) {
        const convertedText = converter.makeHtml(content)

        return "<style>\n" +
               "ul,ol,table,img { margin: " + Theme.paddingLarge + "px 0px; }\n" +
               "a:link { color: " + Theme.highlightColor + "; }\n" +
               "a.checkbox { text-decoration: none; padding: " + Theme.paddingSmall + "px; display: inline-block; }\n" +
               "li.tasklist { font-size:large; margin: " + Theme.paddingMedium + "px 0px; }\n" +
               "del { text-decoration: line-through; }\n" +
               "table { border-color: " + Theme.secondaryColor + "; }\n" +
               "blockquote { font-style: italic }\n" +
               "</style>\n" +
               convertedText +
               "<br><br>"

    }
}
