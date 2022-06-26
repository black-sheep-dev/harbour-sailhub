#include <QtQuick>

#include <sailfishapp.h>

#include "enums/enums.h"
#include "entities/file.h"
#include "models/arraymodel.h"
#include "models/emojimodel.h"
#include "models/treemodel.h"
#include "models/treesortfiltermodel.h"
#include "qml/networkaccessmanagerfactory.h"
//#include "entities/language.h"

#include "api/graphqlconnector.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setApplicationVersion(APP_VERSION);
    app->setApplicationName("sailhub");
    app->setOrganizationDomain("org.nubecula");
    app->setOrganizationName("org.nubecula");

    QScopedPointer<QQuickView> v(SailfishApp::createView());

    NetworkAccessManagerFactory factory;
    v->engine()->setNetworkAccessManagerFactory(&factory);

#ifdef QT_DEBUG
    #define uri "org.nubecula.harbour.sailhub"
#else
    const auto uri = "org.nubecula.harbour.sailhub";
#endif

    // enums
    qmlRegisterUncreatableType<GitSignatureState>(uri, 1, 0, "GitSignatureState", "");
    qmlRegisterUncreatableType<IssueState>(uri, 1, 0, "IssueState", "");
    qmlRegisterUncreatableType<LockReason>(uri, 1, 0, "LockReason", "");
    qmlRegisterUncreatableType<MergeStateStatus>(uri, 1, 0, "MergeStateStatus", "");
    qmlRegisterUncreatableType<PullRequestMergeMethod>(uri, 1, 0, "PullRequestMergeMethod", "");
    qmlRegisterUncreatableType<PullRequestState>(uri, 1, 0, "PullRequestState", "");
    qmlRegisterUncreatableType<RepositoryLockReason>(uri, 1, 0, "RepositoryLockReason", "");
    qmlRegisterUncreatableType<RepositoryPermission>(uri, 1, 0, "RepositoryPermission", "");
    qmlRegisterUncreatableType<RepositoryType>(uri, 1, 0, "RepositoryType", "");
    qmlRegisterUncreatableType<SubscriptionState>(uri, 1, 0, "SubscriptionState", "");

    // object
    //qmlRegisterType<ApiInterface>(uri, 1, 0, "Api");
    qmlRegisterType<ArrayModel>(uri, 1, 0, "ArrayModel");
    qmlRegisterType<EmojiModel>(uri, 1, 0, "EmojiModel");
    qmlRegisterType<File>(uri, 1, 0, "File");
    qmlRegisterType<QueryObject>(uri, 1, 0, "QueryObject");
    qmlRegisterType<TreeItem>(uri, 1, 0, "TreeItem");
    qmlRegisterType<TreeModel>(uri, 1, 0, "TreeModel");
    qmlRegisterType<TreeSortFilterModel>(uri, 1, 0, "TreeSortFilterModel");

    auto context = v.data()->rootContext();

    auto api = new GraphQLConnector;
    context->setContextProperty("Api", api);

//    auto dbus = instance->getDBusAdaptor();
//    context->setContextProperty("dbus", dbus);

    v->setSource(SailfishApp::pathTo("qml/harbour-sailhub.qml"));
    v->show();

    return app->exec();
}
