import QtQuick 2.0
import Sailfish.Silica 1.0

Flow {
    property bool isArchived: false
    property bool isDisabled: false
    property bool isEmpty: false
    property bool isFork: false
    property bool isInOrganization: false
    property bool isLocked: false
    property bool isMirror: false
    property bool isPrivate: false
    property bool isTemplate: false
    property string lockReason: ""

    width: parent.width
    spacing: Theme.paddingSmall

    Pill {
        visible: isPrivate
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-home"
        //% "Private"
        text: qsTrId("id-private")
    }

    Pill {
        visible: isLocked
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-s-secure"
        text: {
            switch (lockReason) {
            case "BILLING":
                //% "Billing"
                return qsTrId("id-billing")

            case "MIGRATING":
                //% "Migrating"
                return qsTrId("id-migrating")

            case "MOVING":
                //% "Moving"
                return qsTrId("id-moving")

            case "RENAME":
                //% "Rename"
                return qsTrId("id-rename")

            default:
                //% "Locked"
                return qsTrId("id-locked")
            }
        }
    }

    Pill {
        visible: isArchived
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-file-archive-folder"
        //% "Archived"
        text: qsTrId("id-archived")
    }

    Pill {
        visible: isInOrganization
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-company"
        //% "Organization"
        text: qsTrId("id-organization")
    }

    Pill {
        visible: isFork
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "/usr/share/harbour-sailhub/icons/icon-m-fork.svg"
        //% "Fork"
        text: qsTrId("id-fork")
    }

    Pill {
        visible: isMirror
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-flip"
        //% "Mirror"
        text: qsTrId("id-mirror")
    }

    Pill {
        visible: isTemplate
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-levels"
        //% "Template"
        text: qsTrId("id-template")
    }

    Pill {
        visible: isDisabled
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-levels"
        //% "Disabled"
        text: qsTrId("id-disabled")
    }

    Pill {
        visible: isEmpty
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-levels"
        //% "Empty"
        text: qsTrId("id-empty")
    }
}
