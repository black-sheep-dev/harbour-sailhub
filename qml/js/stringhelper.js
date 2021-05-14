.pragma library

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

function count(count) {
    if (count < 1000)
        return count
    else
        return Math.round(count / 100) / 10 + "K"
}
