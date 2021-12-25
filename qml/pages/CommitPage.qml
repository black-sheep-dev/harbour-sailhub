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
                title: qsTr("Commit")
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
                    text: commit.signatureIsValid ? qsTr("Verified") : qsTr("Unverified")
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
                        return qsTr("The signing certificate or its chain could not be verified")

                    case GitSignatureState.BAD_EMAIL:
                        return qsTr("Invalid email used for signing")

                    case GitSignatureState.EXPIRED_KEY:
                        return qsTr("Signing key expired")

                    case GitSignatureState.GPGVERIFY_ERROR:
                        return qsTr("Internal error - the GPG verification service misbehaved")

                    case GitSignatureState.GPGVERIFY_UNAVAILABLE:
                        return qsTr("Internal error - the GPG verification service is unavailable at the moment")

                    case GitSignatureState.INVALID:
                        return qsTr("Invalid signature")

                    case GitSignatureState.MALFORMED_SIG:
                        return qsTr("Malformed signature")

                    case GitSignatureState.NOT_SIGNING_KEY:
                        return qsTr("The usage flags for the key that signed this don't allow signing")

                    case GitSignatureState.NO_USER:
                        return qsTr("Email used for signing not known to GitHub")

                    case GitSignatureState.OCSP_ERROR:
                        return qsTr("Valid signature, though certificate revocation check failed")

                    case GitSignatureState.OCSP_PENDING:
                        return qsTr("Valid signature, pending certificate revocation checking")

                    case GitSignatureState.OCSP_REVOKED:
                        return qsTr("One or more certificates in chain has been revoked")

                    case GitSignatureState.UNKNOWN_KEY:
                        return qsTr("Key used for signing not known to GitHub")

                    case GitSignatureState.UNKNOWN_SIG_TYPE:
                        return qsTr("Unknown signature type")

                    case GitSignatureState.UNSIGNED:
                        return qsTr("Unsigned")

                    case GitSignatureState.UNVERIFIED_EMAIL:
                        return qsTr("Email used for signing unverified on GitHub")

                    default:
                        return qsTr("Unkown reason")
                    }
                }
            }

            MarkdownLabel {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: MarkdownParser.parse(commit.message)
            }


            SectionHeader {
                text: qsTr("Changes")
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Changed files")
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

                    text: qsTr("%n addition(s)", "", commit.additions)
                }

                Label {
                    wrapMode: Text.Wrap
                    color: SailHubStyles.colorError
                    font.pixelSize: Theme.fontSizeSmall

                    text: qsTr("%n deletion(s)", "", commit.deletions)
                }
            }

            SectionHeader {
                text: qsTr("Relations")
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Contributors")
                value: commit.authorCount
                icon: "image://theme/icon-m-media-artists"

                onClicked: pageStack.push(Qt.resolvedUrl("UsersListPage.qml"), {
                                          title: qsTr("Contributors"),
                                          description: commit.abbreviatedOid,
                                          identifier: commit.nodeId,
                                          userType: User.CommitAuthor
                                      })
            }

            RelatedValueItem {
                width: parent.width

                label: qsTr("Parents")
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
