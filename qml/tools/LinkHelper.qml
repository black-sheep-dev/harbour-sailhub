import QtQuick 2.0

import '..'

Item {
    signal pleaseOpenLink(string username, string repo, string destination)

    function openLink(link) {
        var githubRegex = /https\:\/\/\w*\.*github\.com\//;

        if (!link.match(githubRegex)) {
            Qt.openUrlExternally(link)
            return
        }

        const url = link.split('github.com/')[1];
        const parts = url.split('/')
        if (parts.length === 2) {
            pleaseOpenLink(parts[0], parts[1], "repo")
        } else if (parts.length > 2)  {
            if (parts[2] === "discussions") {
                pleaseOpenLink(parts[0], parts[1], "discussions")
            } else  if (parts[2] === "issues") {
                pleaseOpenLink(parts[0], parts[1], "issues")
            } else  if (parts[2] === "pulls") {
                pleaseOpenLink(parts[0], parts[1], "pulls")
            } else {
                pleaseOpenLink(parts[0], parts[1], "unsupported")
            }
        }
    }
}
