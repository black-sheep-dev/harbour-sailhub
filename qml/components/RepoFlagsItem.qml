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
        text: qsTr("Private")
    }

    Pill {
        visible: flags & Repo.IsLocked
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-s-secure"
        text: {
            switch (lockReason) {
            case RepositoryLockReason.Billing:
                return qsTr("Billing")

            case RepositoryLockReason.Migrating:
                return qsTr("Migrating")

            case RepositoryLockReason.Moving:
                return qsTr("Moving")

            case RepositoryLockReason.Rename:
                return qsTr("Rename")

            default:
                return qsTr("Locked")
            }
        }
    }

    Pill {
        visible: flags & Repo.IsArchived
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-file-archive-folder"
        text: qsTr("Archived")
    }

    Pill {
        visible: flags & Repo.IsInOrganization
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-company"
        text: qsTr("Organization")
    }

    Pill {
        visible: flags & Repo.IsFork
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "qrc:///icons/icon-m-fork"
        text: qsTr("Fork")
    }

    Pill {
        visible: flags & Repo.IsMirror
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-flip"
        text: qsTr("Mirror")
    }

    Pill {
        visible: flags & Repo.IsTemplate
        backgroundColor: Theme.highlightColor
        color: Theme.primaryColor
        icon: "image://theme/icon-m-levels"
        text: qsTr("Template")
    }
}
