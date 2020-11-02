import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    Image {
        width: parent.width * 0.8
        height: width
        smooth: true
        source: "image://theme/" + Qt.application.name
        anchors.centerIn: parent
        opacity: 0.3
    }
}
