import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

Flow {
    property int flags: 0
    property int lockReason: 0

    width: parent.width
    spacing: Theme.paddingSmall

    Pill {
        visible: flags & Repo.IsPrivate
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-home"
        //% "Private"
        text: qsTrId("id-private")
    }

    Pill {
        visible: flags & Repo.IsLocked
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-s-secure"
        text: {
            switch (lockReason) {
            case RepositoryLockReason.Billing:
                //% "Billing"
                return qsTrId("id-billing")

            case RepositoryLockReason.Migrating:
                //% "Migrating"
                return qsTrId("id-migrating")

            case RepositoryLockReason.Moving:
                //% "Moving"
                return qsTrId("id-moving")

            case RepositoryLockReason.Rename:
                //% "Rename"
                return qsTrId("id-rename")

            default:
                //% "Locked"
                return qsTrId("id-locked")
            }
        }
    }

    Pill {
        visible: flags & Repo.IsArchived
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-file-archive-folder"
        //% "Archived"
        text: qsTrId("id-archived")
    }

    Pill {
        visible: flags & Repo.IsInOrganization
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-company"
        //% "Organization"
        text: qsTrId("id-organization")
    }

    Pill {
        visible: flags & Repo.IsFork
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "qrc:///icons/icon-m-fork"
        //% "Fork"
        text: qsTrId("id-fork")
    }

    Pill {
        visible: flags & Repo.IsMirror
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-flip"
        //% "Mirror"
        text: qsTrId("id-mirror")
    }

    Pill {
        visible: flags & Repo.IsTemplate
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-levels"
        //% "Template"
        text: qsTrId("id-template")
    }
}
