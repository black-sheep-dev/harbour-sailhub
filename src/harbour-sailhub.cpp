#include <QtQuick>

#include <sailfishapp.h>

#include "sailhub.h"
#include "enums/enums.h"
#include "entities/file.h"
#include "entities/reaction.h"
#include "models/treesortfiltermodel.h"
//#include "entities/language.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(QStringLiteral("nubecula.org"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("nubecula.org"));


    qmlRegisterUncreatableType<Downloader>("org.nubecula.harbour.sailhub", 1, 0, "Downloader", "");
    qmlRegisterUncreatableType<FundingLink>("org.nubecula.harbour.sailhub", 1, 0, "FundingLink", "");

    // enums
    qmlRegisterUncreatableType<LockReason>("org.nubecula.harbour.sailhub", 1, 0, "LockReason", "");
    qmlRegisterUncreatableType<RepositoryLockReason>("org.nubecula.harbour.sailhub", 1, 0, "RepositoryLockReason", "");
    qmlRegisterUncreatableType<SubscriptionState>("org.nubecula.harbour.sailhub", 1, 0, "SubscriptionState", "");

    // object
    qmlRegisterType<ApiInterface>("org.nubecula.harbour.sailhub", 1, 0, "Api");
    qmlRegisterType<Comment>("org.nubecula.harbour.sailhub", 1, 0, "Comment");
    qmlRegisterType<CommentsModel>("org.nubecula.harbour.sailhub", 1, 0, "CommentsModel");
    qmlRegisterType<Discussion>("org.nubecula.harbour.sailhub", 1, 0, "Discussion");
    qmlRegisterType<DiscussionsModel>("org.nubecula.harbour.sailhub", 1, 0, "DiscussionsModel");
    qmlRegisterType<DiscussionCategoriesModel>("org.nubecula.harbour.sailhub", 1, 0, "DiscussionCategoriesModel");
    qmlRegisterType<DiscussionComment>("org.nubecula.harbour.sailhub", 1, 0, "DiscussionComment");
    qmlRegisterType<DiscussionCommentsModel>("org.nubecula.harbour.sailhub", 1, 0, "DiscussionCommentsModel");
    qmlRegisterType<File>("org.nubecula.harbour.sailhub", 1, 0, "File");
    qmlRegisterType<FundingLinksModel>("org.nubecula.harbour.sailhub", 1, 0, "FundingLinksModel");
    qmlRegisterType<Gist>("org.nubecula.harbour.sailhub", 1, 0, "Gist");
    qmlRegisterType<GistsModel>("org.nubecula.harbour.sailhub", 1, 0, "GistsModel");
    qmlRegisterType<Interactable>("org.nubecula.harbour.sailhub", 1, 0, "Interactable");
    qmlRegisterType<Issue>("org.nubecula.harbour.sailhub", 1, 0, "Issue");
    qmlRegisterType<IssuesModel>("org.nubecula.harbour.sailhub", 1, 0, "IssuesModel");
    qmlRegisterType<Label>("org.nubecula.harbour.sailhub", 1, 0, "LabelEntity");
    qmlRegisterType<LabelsModel>("org.nubecula.harbour.sailhub", 1, 0, "LabelsModel");
    qmlRegisterType<License>("org.nubecula.harbour.sailhub", 1, 0, "License");
    qmlRegisterType<NotificationObject>("org.nubecula.harbour.sailhub", 1, 0, "Notification");
    qmlRegisterType<NotificationsModel>("org.nubecula.harbour.sailhub", 1, 0, "NotificationsModel");   
    qmlRegisterType<Organization>("org.nubecula.harbour.sailhub", 1, 0, "Organization");
    qmlRegisterType<OrganizationsModel>("org.nubecula.harbour.sailhub", 1, 0, "OrganizationsModel");
    qmlRegisterType<Owner>("org.nubecula.harbour.sailhub", 1, 0, "Owner");
    qmlRegisterType<PullRequest>("org.nubecula.harbour.sailhub", 1, 0, "PullRequest");
    qmlRegisterType<PullRequestsModel>("org.nubecula.harbour.sailhub", 1, 0, "PullRequestsModel");
    qmlRegisterType<Reaction>("org.nubecula.harbour.sailhub", 1, 0, "Reaction");
    qmlRegisterType<Release>("org.nubecula.harbour.sailhub", 1, 0, "Release");
    qmlRegisterType<ReleasesModel>("org.nubecula.harbour.sailhub", 1, 0, "ReleasesModel");
    qmlRegisterType<ReleaseAssetsModel>("org.nubecula.harbour.sailhub", 1, 0, "ReleaseAssetsModel");
    qmlRegisterType<Repo>("org.nubecula.harbour.sailhub", 1, 0, "Repo");
    qmlRegisterType<ReposModel>("org.nubecula.harbour.sailhub", 1, 0, "ReposModel");
    qmlRegisterType<TreeItem>("org.nubecula.harbour.sailhub", 1, 0, "TreeItem");
    qmlRegisterType<TreeModel>("org.nubecula.harbour.sailhub", 1, 0, "TreeModel");
    qmlRegisterType<TreeSortFilterModel>("org.nubecula.harbour.sailhub", 1, 0, "TreeSortFilterModel");
    qmlRegisterType<User>("org.nubecula.harbour.sailhub", 1, 0, "User");
    qmlRegisterType<UsersModel>("org.nubecula.harbour.sailhub", 1, 0, "UsersModel");
    qmlRegisterType<Viewer>("org.nubecula.harbour.sailhub", 1, 0, "Viewer");

    qmlRegisterSingletonType<SailHub>("org.nubecula.harbour.sailhub",
                                              1,
                                              0,
                                              "SailHub",
                                              [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {

        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        auto app = new SailHub();

        return app;
    });


    return SailfishApp::main(argc, argv);
}
