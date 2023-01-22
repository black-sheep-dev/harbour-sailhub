pragma Singleton
import QtQuick 2.0
import Sailfish.Silica 1.0

QtObject {
    // color basic
    readonly property color colorError: "#dd2c00"
    readonly property color colorSuccess: "#64dd17"
    readonly property color colorStarred: "#FFFF00"

    // color events
    readonly property color colorEventClosed: "#673AB7"
    readonly property color colorEventDefault: Theme.darkSecondaryColor
    readonly property color colorEventReopened: colorSuccess

    // color status
    readonly property color colorStatusClosed: colorError
    readonly property color colorStatusMerged: "#aa00ff"
    readonly property color colorStatusOpen: colorSuccess

    // timeline
    readonly property color colorTimeline: Theme.secondaryHighlightColor
    readonly property real opacityTimeline: 0.6
    readonly property int spacingTimeline: Theme.paddingLarge - 2
    readonly property int thicknessTimeline: 4

}
