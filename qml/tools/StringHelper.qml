pragma Singleton

import QtQuick 2.0

Item {
    function fileSize(size) {
        var value = Math.round(size / 1000)

        if (value < 1000)
            return value + " KB"

        value = Math.round(value / 1000)

        if (value < 1000)
            return value + " MB"

        value = Math.round(value / 1000)
        return value + " GB"
    }

    function timespan(date, small) {
        if (small === undefined) small = false
        const current = new Date().getTime()
        const ts = new Date(date).getTime()

        if ((current- ts) < 60000) {
            //% "now"
            return qsTrId("id-now")
        }

        if ((current - ts) < (60000 * 60)) {
            const mins = Math.round((current - ts) / 60000)
            return small ?
                        //% "%1m"
                        qsTrId("id-minutes-ago-count-small", mins) :
                        //% "%n minute(s) ago"
                        qsTrId("id-minutes-ago-count", mins)
        }

        if ((current - ts) < (60000 * 60 * 24)) {
            const hours = Math.round((current - ts) / (60000 * 60))
            return small ?
                        //% "%1h"
                        qsTrId("id-hours-ago-count-small", hours) :
                        //% "%n hours(s) ago"
                        qsTrId("id-hours-ago-count", hours)
        }

        if ((current - ts) < (60000 * 60 * 24 * 30)) {
            const days = Math.round((current - ts) / (60000 * 60 * 24))
            return small ?
                        //% "%1d"
                        qsTrId("id-months-ago-count-small", days) :
                        //% "%n hours(s) ago"
                        qsTrId("id-months-ago-count", days)
        }

        if ((current - ts) < (60000 * 60 * 24 * 365)) {
            const months = Math.round((current - ts) / (60000 * 60 * 24 * 30))
            return small ?
                        //% "%1mo"
                        qsTrId("id-months-ago-count-small", months) :
                        //% "%n hours(s) ago"
                        qsTrId("id-months-ago-count", months)
        }

        const years = Math.round((current - ts) / (60000 * 60 * 24 * 365))
        return small ?
                    //% "%1y"
                    qsTrId("id-years-ago-count-small", years) :
                    //% "%n years(s) ago"
                    qsTrId("id-years-ago-count", years)
    }

    function count(count) {
        if (count < 1000)
            return count
        else
            return Math.round(count / 100) / 10 + "K"
    }
}

