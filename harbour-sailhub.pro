# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# VERSION
VERSION = 0.0.8
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# The name of your application
TARGET = harbour-sailhub
DEFINES += APP_TARGET=\\\"$$TARGET\\\"

# custom defines
#DEFINES += DISABLE_SAILFISH_SECRETS

QT += dbus

CONFIG += link_pkgconfig sailfishapp
PKGCONFIG += sailfishsecrets nemonotifications-qt5

LIBS += -lz

SOURCES += src/harbour-sailhub.cpp \
    src/api/apiinterface.cpp \
    src/api/datautils.cpp \
    src/api/graphqlconnector.cpp \
    src/api/keys.cpp \
    src/api/queryvars.cpp \
    src/entities/comment.cpp \
    src/entities/file.cpp \
    src/entities/issue.cpp \
    src/entities/label.cpp \
    src/entities/license.cpp \
    src/entities/node.cpp \
    src/entities/organization.cpp \
    src/entities/owner.cpp \
    src/entities/pullrequest.cpp \
    src/entities/repo.cpp \
    src/entities/user.cpp \
    src/models/commentsmodel.cpp \
    src/models/issuesmodel.cpp \
    src/models/labelsmodel.cpp \
    src/models/organizationsmodel.cpp \
    src/models/paginationmodel.cpp \
    src/models/pullrequestsmodel.cpp \
    src/models/reposmodel.cpp \
    src/models/treemodel.cpp \
    src/models/treesortfiltermodel.cpp \
    src/models/usersmodel.cpp \
    src/sailhub.cpp

DISTFILES += qml/harbour-sailhub.qml \
    qml/components/AuthorItem.qml \
    qml/components/CommentItem \
    qml/components/CommentItem.qml \
    qml/components/CounterItem.qml \
    qml/components/IconLabel.qml \
    qml/components/IconRelatedItem.qml \
    qml/components/InfoItem.qml \
    qml/components/RelatedItem.qml \
    qml/cover/CoverPage.qml \
    qml/delegates/CommentListDelegate.qml \
    qml/delegates/IssueListDelegate.qml \
    qml/delegates/LabelListDelegate.qml \
    qml/delegates/OrganizationListDelegate.qml \
    qml/delegates/PullRequestListDelegate.qml \
    qml/delegates/RepoListDelegate.qml \
    qml/delegates/UserListDelegate.qml \
    qml/dialogs/EditCommentDialog.qml \
    qml/dialogs/EditIssueDialog.qml \
    qml/dialogs/ReactionDialog.qml \
    qml/dialogs/SelectBranchDialog.qml \
    qml/dialogs/SelectSubscriptionDialog.qml \
    qml/dialogs/SortSelectionDialog.qml \
    qml/pages/CommentPage \
    qml/pages/CommentPage.qml \
    qml/pages/CommentsListPage.qml \
    qml/pages/ImageViewerPage.qml \
    qml/pages/IssuePage.qml \
    qml/pages/IssuesListPage.qml \
    qml/pages/LabelsListPage.qml \
    qml/pages/OrganizationPage.qml \
    qml/pages/OrganizationsListPage.qml \
    qml/pages/OverviewPage.qml \
    qml/pages/PullRequestsListPage.qml \
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
    qml/pages/settings/SettingsPage.qml \
    qml/pages/settings/SettingsPaginationPage.qml \
    qml/pages/wizard/WizardFinalPage.qml \
    qml/pages/wizard/WizardIntroPage.qml \
    qml/pages/wizard/WizardTokenPage.qml \
    rpm/harbour-sailhub.changes \
    rpm/harbour-sailhub.changes.run.in \
    rpm/harbour-sailhub.spec \
    rpm/harbour-sailhub.yaml \
    translations/*.ts \
    harbour-sailhub.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 512x512

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += \
    translations/harbour-sailhub-de.ts \
    translations/harbour-sailhub-pl.ts \
    translations/harbour-sailhub-zh_Hans.ts

RESOURCES += \
    ressources.qrc

HEADERS += \
    src/api/apiinterface.h \
    src/api/datautils.h \
    src/api/graphqlconnector.h \
    src/api/graphqlquery.h \
    src/api/keys.h \
    src/api/mutations.h \
    src/api/queries.h \
    src/api/query_items.h \
    src/api/queryvars.h \
    src/api/ratelimit.h \
    src/entities/comment.h \
    src/entities/file.h \
    src/entities/issue.h \
    src/entities/label.h \
    src/entities/language.h \
    src/entities/license.h \
    src/entities/node.h \
    src/entities/organization.h \
    src/entities/owner.h \
    src/entities/pullrequest.h \
    src/entities/reaction.h \
    src/entities/repo.h \
    src/entities/treeitem.h \
    src/entities/user.h \
    src/models/commentsmodel.h \
    src/models/issuesmodel.h \
    src/models/labelsmodel.h \
    src/models/organizationsmodel.h \
    src/models/paginationmodel.h \
    src/models/pullrequestsmodel.h \
    src/models/reposmodel.h \
    src/models/treemodel.h \
    src/models/treesortfiltermodel.h \
    src/models/usersmodel.h \
    src/sailhub.h

dbus.files = data/harbour.sailhub.service
dbus.path = $$INSTALL_ROOT/usr/share/dbus-1/services

INSTALLS += dbus

#icons.files = icons/scalable/*
#icons.path = $$INSTALL_ROOT/usr/share/icons/hicolor/scalable/apps/harbour-sailhub/

#INSTALLS += icons
