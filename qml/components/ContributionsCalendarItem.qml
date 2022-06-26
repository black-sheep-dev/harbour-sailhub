import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property var calendarData

    id: contributionCalendar
    width: parent.width
    height: parent.width

    onCalendarDataChanged: {
        var idx = 1
        console.log(calendarData.length)
        console.log(calendarData[0].length)
        for (var i=0; i < calendarData.length; i++) {
            for (var j=0; j < calendarData[i].contributionDays.length; j++) {
                const obj = Qt.createQmlObject('
                    import QtQuick 2.0
                    import Sailfish.Silica 1.0

                    Rectangle {
                        width: ' + grid.width / grid.columns + '
                        height: width
                        radius: 2
                        border.color: Theme.primaryColor
                        color: Theme.highlightColor
                    }
                ', grid, "rect" + idx)

                idx++
            }
        }
    }

    Grid {
        id: grid
        width: parent.width
        spacing: Theme.paddingSmall
        columns: 56
        rows: 7
        flow: Grid.TopToBottom
    }
}
