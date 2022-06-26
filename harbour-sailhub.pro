# VERSION
VERSION = 0.1.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# The name of your application
TARGET = harbour-sailhub
DEFINES += APP_TARGET=\\\"$$TARGET\\\"

QT += dbus

CONFIG += link_pkgconfig sailfishapp
PKGCONFIG += nemonotifications-qt5 keepalive

include(extern/sailfishos-utils/compressor/compressor.pri)


SOURCES += src/harbour-sailhub.cpp \
    src/api/datautils.cpp \
    src/api/graphqlconnector.cpp \
    src/api/keys.cpp \
    src/api/mutations.cpp \
    src/api/queryobject.cpp \
    src/api/queryvars.cpp \
    src/api/restapiconnector.cpp \
    src/dbus/dbusadaptor.cpp \
    src/dbus/dbusinterface.cpp \
    src/entities/file.cpp \
    src/entities/node.cpp \
    src/entities/notificationobject.cpp \
    src/models/arraymodel.cpp \
    src/models/basemodel.cpp \
    src/models/emojimodel.cpp \
    src/models/notificationsmodel.cpp \
    src/models/treemodel.cpp \
    src/models/treesortfiltermodel.cpp \
    src/qml/networkaccessmanagerfactory.cpp

DISTFILES += qml/harbour-sailhub.qml \
    qml/SailHubStyles.qml \
    qml/components/CommitInfoItem.qml \
    qml/components/ContributionsCalendarItem.qml \
    qml/components/LanguageItem.qml \
    qml/components/StargazerItem.qml \
    qml/components/menu/SubscriptionMenuItem.qml \
    qml/components/menu/LockableMenuItem.qml \
    qml/components/views/CommentsListPage.qml \
    qml/dialogs/CloseIssueDialog.qml \
    qml/dialogs/SelectLockReasonDialog.qml \
    qml/js/datautils.js \
    qml/objects/ViewerProfile.qml \
    qml/components/AuthorItem.qml \
    qml/components/CommentItem \
    qml/components/CommentItem.qml \
    qml/components/CounterItem.qml \
    qml/components/DiscussionCommentItem.qml \
    qml/components/FilesChangedItem.qml \
    qml/components/IconLabel.qml \
    qml/components/IconRelatedItem.qml \
    qml/components/InfoItem.qml \
    qml/components/IssueCommentItem.qml \
    qml/components/LockReasonPill \
    qml/components/MarkdownLabel.qml \
    qml/components/Pill.qml \
    qml/components/ProfileStatusItem.qml \
    qml/components/ReactionGridItem.qml \
    qml/components/ReactionLabel.qml \
    qml/components/ReactionsItem.qml \
    qml/components/RelatedItem.qml \
    qml/components/RepoFlagsItem.qml \
    qml/components/menu/StarMenuItem.qml \
    qml/cover/CoverPage.qml \
    qml/delegates/AssetListDelegate.qml \
    qml/delegates/CommitListDelegate.qml \
    qml/delegates/DiscussionCategoryListDelegate.qml \
    qml/delegates/DiscussionListDelegate.qml \
    qml/delegates/GistListDelegate.qml \
    qml/delegates/IssueListDelegate.qml \
    qml/delegates/LabelListDelegate.qml \
    qml/delegates/NotificationListDelegate.qml \
    qml/delegates/OrganizationListDelegate.qml \
    qml/delegates/PullRequestListDelegate.qml \
    qml/delegates/ReleaseListDelegate.qml \
    qml/delegates/RepoListDelegate.qml \
    qml/delegates/TreeListDelegate.qml \
    qml/delegates/UserListDelegate.qml \
    qml/dialogs/AssignUserDialog.qml \
    qml/dialogs/EditCommentDialog.qml \
    qml/dialogs/EditDiscussionDialog.qml \
    qml/dialogs/EditIssueDialog.qml \
    qml/dialogs/SelectBranchDialog.qml \
    qml/dialogs/SelectDiscussionCategoryDialog.qml \
    qml/dialogs/SelectEmojiDialog.qml \
    qml/dialogs/SelectSubscriptionDialog.qml \
    qml/dialogs/SortSelectionDialog.qml \
    qml/pages/AddStarPage.qml \
    qml/pages/AssigneesListPage.qml \
    qml/pages/CommentPage \
    qml/pages/CommitPage.qml \
    qml/pages/CommitTreeListPage.qml \
    qml/pages/CommitsListPage.qml \
    qml/pages/DiscussionCommentPage.qml \
    qml/pages/DiscussionPage.qml \
    qml/pages/DiscussionsListPage.qml \
    qml/pages/DiscussionsListPage_old.qml \
    qml/pages/FundingLinksListPage.qml \
    qml/pages/GistsListPage.qml \
    qml/pages/ImageViewerPage.qml \
    qml/pages/IssuePage.qml \
    qml/pages/IssueSelectionPage.qml \
    qml/pages/IssuesListPage.qml \
    qml/pages/LabelsListPage.qml \
    qml/pages/MarkdownViewerPage.qml \
    qml/pages/NotificationsListPage.qml \
    qml/pages/OrganizationPage.qml \
    qml/pages/OrganizationsListPage.qml \
    qml/pages/OverviewPage.qml \
    qml/pages/ProfileStatusPage.qml \
    qml/pages/PullRequestPage.qml \
    qml/pages/PullRequestsListPage.qml \
    qml/pages/PullRequestsSelectionPage.qml \
    qml/pages/ReleaseAssetsListPage.qml \
    qml/pages/ReleasePage.qml \
    qml/pages/ReleasesListPage.qml \
    qml/pages/RepoPage.qml \
    qml/pages/ReposListPage.qml \
    qml/pages/SearchOrganizationPage.qml \
    qml/pages/SearchRepositoryPage.qml \
    qml/pages/SearchSelectionPage.qml \
    qml/pages/SearchUserPage.qml \
    qml/pages/TextFileViewerPage.qml \
    qml/pages/TreeListPage.qml \
    qml/pages/UserPage.qml \
    qml/pages/UserPage.qml \
    qml/pages/UsersListPage.qml \
    qml/pages/settings/SettingsAuthenticationPage.qml \
    qml/pages/settings/SettingsNotificationPage.qml \
    qml/pages/settings/SettingsPage.qml \
    qml/pages/settings/SettingsPaginationPage.qml \
    qml/pages/wizard/WizardFinalPage.qml \
    qml/pages/wizard/WizardIntroPage.qml \
    qml/pages/wizard/WizardTokenPage.qml \
    qml/qmldir \
    qml/queries/AddReactionMutation.qml \
    qml/queries/AddStarMutation.qml \
    qml/queries/assignee/AddAssigneesMutation.qml \
    qml/queries/assignee/RemoveAssigneesMutation.qml \
    qml/queries/comment/AddCommentMutation.qml \
    qml/queries/comment/DeleteCommentMutation.qml \
    qml/queries/comment/UpdateCommentMutation.qml \
    qml/queries/issue/CloseIssueMutation.qml \
    qml/queries/issue/CreateIssueMutation.qml \
    qml/queries/issue/DeleteIssueMutation.qml \
    qml/queries/FollowOrganizationMutation.qml \
    qml/queries/FollowUserMutation.qml \
    qml/queries/LockLockableMutation.qml \
    qml/queries/RemoveReactionMutation.qml \
    qml/queries/RemoveStarMutation.qml \
    qml/queries/issue/ReopenIssueMutation.qml \
    qml/queries/UnfollowOrganizationMutation.qml \
    qml/queries/UnfollowUserMutation.qml \
    qml/queries/UnlockLockableMutation.qml \
    qml/queries/issue/UpdateIssueMutation.qml \
    qml/queries/UpdateSubscriptionMutation.qml \
    qml/tools/LinkHelper.qml \
    qml/tools/MarkdownParser.qml \
    qml/tools/StringHelper.qml \
    rpm/harbour-sailhub.changes \
    rpm/harbour-sailhub.changes.run.in \
    rpm/harbour-sailhub.spec \
    rpm/harbour-sailhub.yaml \
    translations/*.ts \
    harbour-sailhub.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 512x512

#CONFIG += sailfishapp_i18n

include(translations/translations.pri)

RESOURCES += \
    ressources.qrc

HEADERS += \
    src/api/datautils.h \
    src/api/graphqlconnector.h \
    src/api/graphqlquery.h \
    src/api/keys.h \
    src/api/mutations.h \
    src/api/queries.h \
    src/api/query_items.h \
    src/api/queryobject.h \
    src/api/queryvars.h \
    src/api/restapiconnector.h \
    src/dbus/dbusadaptor.h \
    src/dbus/dbusinterface.h \
    src/entities/file.h \
    src/entities/node.h \
    src/entities/notificationobject.h \
    src/entities/treeitem.h \
    src/enums/enums.h \
    src/enums/gitsignaturestate \
    src/enums/issuestate.h \
    src/enums/lockreason.h \
    src/enums/mergestatestatus.h \
    src/enums/pullrequestmergemethod.h \
    src/enums/pullrequeststate.h \
    src/enums/repositorylockreason.h \
    src/enums/repositorypermission.h \
    src/enums/repositorytype.h \
    src/enums/subscriptionstate.h \
    src/models/arraymodel.h \
    src/models/basemodel.h \
    src/models/emojimodel.h \
    src/models/notificationsmodel.h \
    src/models/treemodel.h \
    src/models/treesortfiltermodel.h \
    src/qml/networkaccessmanagerfactory.h

twemoji.files = data/emoji.def
twemoji.path = $$INSTALL_ROOT/usr/share/harbour-sailhub/data

INSTALLS += twemoji

dbus.files = data/org.nubecula.sailhub.service
dbus.path = $$INSTALL_ROOT/usr/share/dbus-1/services

INSTALLS += dbus

openUrl.files = harbour-sailhub-open-url.desktop
openUrl.path = $$INSTALL_ROOT/usr/share/applications

INSTALLS += openUrl
