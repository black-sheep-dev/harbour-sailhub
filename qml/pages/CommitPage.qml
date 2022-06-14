import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.sailhub 1.0

import "../components/"
import "../delegates/"
import "../tools"
import ".."

Page {
    property bool busy: false
    property string nodeId
    property Commit commit

    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: headerColumn.height

        Column {
            id: headerColumn
            width: parent.width
            spacing: Theme.paddingSmall

            opacity: busyIndicator.running ? 0.1 : 1.0
            Behavior on opacity { FadeAnimator {} }

            PageHeader {
                //% "Commit"
                title: qsTrId("id-commit")
                description: commit.abbreviatedOid
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                height: Theme.itemSizeSmall
                spacing: Theme.paddingMedium

                CircleImage {
                    id: avatarIcon
                    width: parent.height / 2
                    height: width
                    source: commit.author.avatarUrl
                    anchors.verticalCenter: parent.verticalCenter

                    fallbackItemVisible: false

                    BusyIndicator {
                        size: BusyIndicatorSize.Medium
                        anchors.centerIn: avatarIcon
                        running: avatarIcon.status !== Image.Ready
                    }
                }

                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    anchors.verticalCenter: avatarIcon.verticalCenter

                    text: commit.author.login
                }
            }

            // signature verification
            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                Pill {
                    backgroundColor: commit.signatureIsValid ? SailHubStyles.colorSuccess : SailHubStyles.colorError
                    color: Theme.primaryColor
                    icon: commit.signatureIsValid ? "image://theme/icon-s-checkmark" : "image://theme/icon-s-high-importance"
                    text: commit.signatureIsValid ?
                              //% "Verified"
                              qsTrId("id-verified") :
                              //% "Unverified"
                              qsTrId("id-unverified")
                }
            }

            Label {
                visible: !commit.signatureIsValid
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: SailHubStyles.colorError

                text: {
                    switch (commit.signatureState) {
                    case GitSignatureState.BAD_CERT:
                        //% "The signing certificate or its chain could not be verified"
                        return qsTrId("id-state-bad-cert")

                    case GitSignatureState.BAD_EMAIL:
                        //% "Invalid email used for signing"
                        return qsTrId("id-state-bad-email")

                    case GitSignatureState.EXPIRED_KEY:
                        //% "Signing key expired"
                        return qsTrId("id-state-expired-key")

                    case GitSignatureState.GPGVERIFY_ERROR:
                        //% "Internal error - the GPG verification service misbehaved"
                        return qsTrId("id-state-gpgverify-error")

                    case GitSignatureState.GPGVERIFY_UNAVAILABLE:
                        //% "Internal error - the GPG verification service is unavailable at the moment"
                        return qsTrId("id-state-gpgverify-unavailable")

                    case GitSignatureState.INVALID:
                        //% "Invalid signature"
                        return qsTrId("id-state-invalid-signature")

                    case GitSignatureState.MALFORMED_SIG:
                        //% "Malformed signature"
                        return qsTrId("id-state-malformed-sig")

                    case GitSignatureState.NOT_SIGNING_KEY:
                        //% "The usage flags for the key that signed this don't allow signing"
                        return qsTrId("id-state-not-signing-key")

                    case GitSignatureState.NO_USER:
                        //% "Email used for signing not known to GitHub"
                        return qsTrId("id-state-no-user")

                    case GitSignatureState.OCSP_ERROR:
                        //% "Valid signature, though certificate revocation check failed"
                        return qsTrId("id-ocsp-error")

                    case GitSignatureState.OCSP_PENDING:
                        //% "Valid signature, pending certificate revocation checking"
                        return qsTrId("id-state-ocsp-pending")

                    case GitSignatureState.OCSP_REVOKED:
                        //% "One or more certificates in chain has been revoked"
                        return qsTrId("id-state-ocsp-revoke")

                    case GitSignatureState.UNKNOWN_KEY:
                        //% "Key used for signing not known to GitHub"
                        return qsTrId("id-state-unknown-key")

                    case GitSignatureState.UNKNOWN_SIG_TYPE:
                        //% "Unknown signature type"
                        return qsTrId("id-state-unknown-sig-type")

                    case GitSignatureState.UNSIGNED:
                        //% "Unsigned"
                        return qsTrId("id-stat-unsigned")

                    case GitSignatureState.UNVERIFIED_EMAIL:
                        //% "Email used for signing unverified on GitHub"
                        return qsTrId("id-state-unverified-email")

                    default:
                        //% "Unkown reason"
                        return qsTrId("id-state-unknown-reason")
                    }
                }
            }

            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parse(commit.message)
            }


            SectionHeader {
                //% "Changes"
                text: qsTrId("id-changes")
            }

            RelatedValueItem {
                width: parent.width

                //% "Changed files"
                label: qsTrId("id-changed-files")
                value: commit.changedFiles
                icon: "qrc:/icons/icon-m-files-changed"

//                onClicked: pageStack.push(Qt.resolvedUrl("CommitTreeListPage.qml"), {
//                                               commitId: commit.nodeId,
//                                               desc: commit.abbreviatedOid
//                                          })
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                spacing: Theme.paddingMedium

                Label {
                    wrapMode: Text.Wrap
                    color: SailHubStyles.colorSuccess
                    font.pixelSize: Theme.fontSizeSmall

                    //% "%n addition(s)"
                    text: qsTrId("id-additions-count", commit.additions)
                }

                Label {
                    wrapMode: Text.Wrap
                    color: SailHubStyles.colorError
                    font.pixelSize: Theme.fontSizeSmall

                    //% "%n deletion(s)"
                    text: qsTrId("id-deletions-count", commit.deletions)
                }
            }

            SectionHeader {
                //% "Relations"
                text: qsTrId("id-relations")
            }

            RelatedValueItem {
                width: parent.width

                //% "Contributors"
                label: qsTrId("id-contributors")
                value: commit.authorCount
                icon: "image://theme/icon-m-media-artists"

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {

                                          title: label,
                                          description: commit.abbreviatedOid,
                                          identifier: commit.nodeId,
                                          userType: User.CommitAuthor
                                      })
            }

            RelatedValueItem {
                width: parent.width

                //% "Parents"
                label: qsTrId("id-parents")
                value: commit.parentCount
                icon: "qrc:/icons/icon-m-commit"

                onClicked: {
                    if (commit.parentCount === 0) return;

                    pageStack.push(Qt.resolvedUrl("CommitsListPage.qml"), {
                                              identifier: commit.nodeId,
                                              type: Commit.Parent
                                          })
                }
            }
        }
    }

    Connections {
        target: SailHub.api()
        onCommitAvailable: {
            if (commit.nodeId !== page.nodeId) return

            page.commit = commit;
        }
    }

    Component.onCompleted: SailHub.api().getCommit(page.nodeId)
}
