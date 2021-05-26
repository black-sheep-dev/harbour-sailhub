pragma Singleton
import QtQuick 2.0

QtObject {
    // color basic
    readonly property color colorError: "#dd2c00"
    readonly property color colorSuccess: "#64dd17"
    readonly property color colorStarred: "#FFFF00"

    // color status
    readonly property color colorStatusClosed: colorError
    readonly property color colorStatusMerged: "#aa00ff"
    readonly property color colorStatusOpen: colorSuccess
}
