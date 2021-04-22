import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.DBus 2.0

import "pages"

import org.nubecula.harbour.sailhub 1.0

ApplicationWindow
{
    initialPage: Component { OverviewPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Component.onCompleted: SailHub.initialize()

    DBusAdaptor {
        service: "harbour.sailhub.service"
        iface: "harbour.sailhub.service"
        path: "/harbour/sailhub/service"
        xml: '\
              <interface name="harbour.sailhub.service">
                <method name="token">
                </method>
              </interface>'

        function token() {
            __silica_applicationwindow_instance.activate()
            pageStack.push(Qt.resolvedUrl("pages/settings/SettingsAuthenticationPage.qml"))
        }

        function open() {
            __silica_applicationwindow_instance.activate()
            pageStack.push(Qt.resolvedUrl("pages/NotificationsListPage.qml"))
        }
    }
}
