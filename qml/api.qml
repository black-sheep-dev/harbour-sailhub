pragma Singleton
import QtQuick 2.0

Item {
    property string accessToken
    property bool debug: false

    function request(query, callback) {
        if (query === undefined) return

        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if (myxhr.readyState !== 4) return

                if (debug) console.log(myxhr.responseText)

                const data = JSON.parse(myxhr.responseText).data

//                try {
//                    data =

//                } catch (e) {
//                    data = JSON.parse(myxhr.responseText).data
//                    if (debug) {
//                        console.log("failed to parse JSON")
//                        console.log(e)
//                    }
//                }

                callback(data, myxhr.status)
            }
        })(xhr)

        if (debug) console.log(JSON.stringify(query).replace(/[\n\r] +(?= )/g, ''))

        xhr.open("POST", "https://api.github.com/graphql")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.setRequestHeader("Authorization", "token " + accessToken)
        xhr.setRequestHeader("X-Github-Next-Global-ID", 1)
        xhr.send(JSON.stringify(query))
    }
}

