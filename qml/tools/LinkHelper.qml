import QtQuick 2.0

import '..'

Item {
    signal openRepo(string username, string repo)

    function openLink(link) {
        if (link.lastIndexOf('https://github.com/') !== 0) {
            Qt.openUrlExternally(link)
            return
        }

        const parts = link.split('/')
        if (parts.length === 5) {
            openRepo(parts[3], parts[4])
        } else {
            Qt.openUrlExternally(link)
        }
    }
}
