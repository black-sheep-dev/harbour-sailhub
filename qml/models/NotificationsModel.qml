import QtQuick 2.0

import "../."

ListModel {
    property int currentPage: 1
    property string lastModified
    property bool loading: false
    property int pollInterval: 60 * 1000
    property int unread: 0
    property var notifiedMessages: []

    id: notificationsModel

    function setAsReadAll() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if (myxhr.readyState !== 4) return
                if (settings.apiDebug) console.log(myxhr.responseText)

                console.log(myxhr.status)
                console.log(myxhr.responseText)

                if (myxhr.status === 202 || myxhr.status === 205 ) {
                    for (var i=0; i < count; i++) {
                        setProperty(i, "unread", false)
                    }
                    unread = 0
                } else {
                    //% "Could not mark all as read"
                    notification.show(qsTrId("id-could-not-mark-all-as-read"))
                }
            }
        })(xhr)

        const payload = {
            //last_read_at: new Date().toISOString().split('.')[0]+"Z",
            read: true
        }

        //if (settings.apiDebug)
            console.log(JSON.stringify(payload))

        xhr.open("PUT", "https://api.github.com/notifications")
        xhr.setRequestHeader("Accept", "application/vnd.github+json")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.setRequestHeader("X-GitHub-Api-Version", "2022-11-28")
        xhr.setRequestHeader("Authorization", "token " + settings.accessToken)
        xhr.setRequestHeader("X-Github-Next-Global-ID", 1)
        xhr.send(JSON.stringify(payload))
    }

    function setAsRead(index) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if (myxhr.readyState !== 4) return
                if (settings.apiDebug) console.log(myxhr.responseText)

                console.log(myxhr.status)
                console.log(myxhr.responseText)

                if (myxhr.status !== 205) {
                    //% "Could not mark as read"
                    notification.show(qsTrId("id-could-not-mark-as-read"))
                    return
                }

                get(index).setProperty("unread", false)
                if (unread > 0) unread--
            }
        })(xhr)

        xhr.open("PUT", "https://api.github.com/notifications/threads/" + get(index).id)
        xhr.setRequestHeader("Accept", "application/vnd.github+json")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.setRequestHeader("X-GitHub-Api-Version", "2022-11-28")
        xhr.setRequestHeader("Authorization", "token " + settings.accessToken)
        xhr.setRequestHeader("X-Github-Next-Global-ID", 1)
        xhr.send()
    }

    function refresh() {
        if (count > 0) clear()
        currentPage = 1
        unread = 0
        loadMore()
    }

    function loadMore() {
        loading = true
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                loading = false
                if (myxhr.readyState !== 4) return

                if (myxhr.status === "304") return // no new notifications

                if (settings.apiDebug) console.log(myxhr.responseText)

                lastModified = myxhr.getResponseHeader("Last-Modified")
                pollInterval = myxhr.getResponseHeader("X-Poll-Interval")

                parseData(JSON.parse(myxhr.responseText))
            }
        })(xhr)

        const url = "https://api.github.com/notifications?page=" + currentPage + "&per_page=50"

        xhr.open("GET", url)
        xhr.setRequestHeader("Accept", "application/vnd.github+json")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.setRequestHeader("X-GitHub-Api-Version", "2022-11-28")
        xhr.setRequestHeader("X-Github-Next-Global-ID", 1)
        xhr.setRequestHeader("Authorization", "token " + settings.accessToken)
        //if (lastModified.length > 0) xhr.setRequestHeader("If-Modified-Since", lastModified)
        xhr.send()
    }

    function parseData(data) {
        if (data.length === 0) return

        data.forEach(function(item) {
            if (item.unread) unread++
            append(item)
            //notification.showNotification(item)
        })

        currentPage++
    }
}

