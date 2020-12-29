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
VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# The name of your application
TARGET = harbour-sailhub
DEFINES += APP_TARGET=\\\"$$TARGET\\\"

CONFIG += sailfishapp

LIBS += -lz

SOURCES += src/harbour-sailhub.cpp \
    src/api/apiinterface.cpp \
    src/api/datautils.cpp \
    src/api/graphqlconnector.cpp \
    src/entities/license.cpp \
    src/entities/node.cpp \
    src/entities/owner.cpp \
    src/entities/repo.cpp \
    src/entities/user.cpp \
    src/models/paginationmodel.cpp \
    src/models/reposmodel.cpp \
    src/models/usersmodel.cpp \
    src/sailhub.cpp

DISTFILES += qml/harbour-sailhub.qml \
    qml/components/CounterItem.qml \
    qml/components/IconLabel.qml \
    qml/components/IconRelatedItem.qml \
    qml/components/InfoItem.qml \
    qml/components/RelatedItem.qml \
    qml/cover/CoverPage.qml \
    qml/delegates/RepoListDelegate.qml \
    qml/delegates/UserListDelegate.qml \
    qml/pages/OverviewPage.qml \
    qml/pages/RepoPage.qml \
    qml/pages/ReposListPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/UserPage.qml \
    qml/pages/UserPage.qml \
    qml/pages/UsersListPage.qml \
    rpm/harbour-sailhub.changes.in \
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
TRANSLATIONS += translations/harbour-sailhub-de.ts

RESOURCES += \
    ressources.qrc

HEADERS += \
    src/api/apiinterface.h \
    src/api/datautils.h \
    src/api/graphqlconnector.h \
    src/api/keys.h \
    src/api/queries.h \
    src/api/ratelimit.h \
    src/entities/language.h \
    src/entities/license.h \
    src/entities/node.h \
    src/entities/owner.h \
    src/entities/repo.h \
    src/entities/user.h \
    src/models/paginationmodel.h \
    src/models/reposmodel.h \
    src/models/usersmodel.h \
    src/sailhub.h
