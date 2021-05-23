#include <QtQuick>

#include <sailfishapp.h>

#include "sailhub.h"
#include "enums/enums.h"
#include "entities/file.h"
#include "entities/reaction.h"
#include "models/emojimodel.h"
#include "models/treesortfiltermodel.h"
//#include "entities/language.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(QStringLiteral("nubecula.org"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("nubecula.org"));

#ifdef QT_DEBUG
    #define uri "org.nubecula.harbour.sailhub"
#else
    const auto uri = "org.nubecula.harbour.sailhub";
#endif

    qmlRegisterUncreatableType<Downloader>(uri, 1, 0, "Downloader", "");
    qmlRegisterUncreatableType<FundingLink>(uri, 1, 0, "FundingLink", "");

    // enums
    qmlRegisterUncreatableType<IssueState>(uri, 1, 0, "IssueState", "");
    qmlRegisterUncreatableType<LockReason>(uri, 1, 0, "LockReason", "");
    qmlRegisterUncreatableType<MergeStateStatus>(uri, 1, 0, "MergeStateStatus", "");
    qmlRegisterUncreatableType<PullRequestMergeMethod>(uri, 1, 0, "PullRequestMergeMethod", "");
    qmlRegisterUncreatableType<PullRequestState>(uri, 1, 0, "PullRequestState", "");
    qmlRegisterUncreatableType<RepositoryLockReason>(uri, 1, 0, "RepositoryLockReason", "");
    qmlRegisterUncreatableType<RepositoryPermission>(uri, 1, 0, "RepositoryPermission", "");
    qmlRegisterUncreatableType<SubscriptionState>(uri, 1, 0, "SubscriptionState", "");

    // object
    qmlRegisterType<ApiInterface>(uri, 1, 0, "Api");
    qmlRegisterType<Comment>(uri, 1, 0, "Comment");
    qmlRegisterType<CommentsModel>(uri, 1, 0, "CommentsModel");
    qmlRegisterType<Commit>(uri, 1, 0, "Commit");
    qmlRegisterType<CommitsModel>(uri, 1, 0, "CommitsModel");
    qmlRegisterType<Discussion>(uri, 1, 0, "Discussion");
    qmlRegisterType<DiscussionsModel>(uri, 1, 0, "DiscussionsModel");
    qmlRegisterType<DiscussionCategoriesModel>(uri, 1, 0, "DiscussionCategoriesModel");
    qmlRegisterType<DiscussionComment>(uri, 1, 0, "DiscussionComment");
    qmlRegisterType<DiscussionCommentsModel>(uri, 1, 0, "DiscussionCommentsModel");
    qmlRegisterType<EmojiModel>(uri, 1, 0, "EmojiModel");
    qmlRegisterType<File>(uri, 1, 0, "File");
    qmlRegisterType<FundingLinksModel>(uri, 1, 0, "FundingLinksModel");
    qmlRegisterType<Gist>(uri, 1, 0, "Gist");
    qmlRegisterType<GistsModel>(uri, 1, 0, "GistsModel");
    qmlRegisterType<Interactable>(uri, 1, 0, "Interactable");
    qmlRegisterType<Issue>(uri, 1, 0, "Issue");
    qmlRegisterType<IssuesModel>(uri, 1, 0, "IssuesModel");
    qmlRegisterType<Label>(uri, 1, 0, "LabelEntity");
    qmlRegisterType<LabelsModel>(uri, 1, 0, "LabelsModel");
    qmlRegisterType<License>(uri, 1, 0, "License");
    qmlRegisterType<NotificationObject>(uri, 1, 0, "Notification");
    qmlRegisterType<NotificationsModel>(uri, 1, 0, "NotificationsModel");
    qmlRegisterType<Organization>(uri, 1, 0, "Organization");
    qmlRegisterType<OrganizationsModel>(uri, 1, 0, "OrganizationsModel");
    qmlRegisterType<Owner>(uri, 1, 0, "Owner");
    qmlRegisterType<ProfileStatus>(uri, 1, 0, "ProfileStatus");
    qmlRegisterType<PullRequest>(uri, 1, 0, "PullRequest");
    qmlRegisterType<PullRequestsModel>(uri, 1, 0, "PullRequestsModel");
    qmlRegisterType<Reaction>(uri, 1, 0, "Reaction");
    qmlRegisterType<Release>(uri, 1, 0, "Release");
    qmlRegisterType<ReleasesModel>(uri, 1, 0, "ReleasesModel");
    qmlRegisterType<ReleaseAssetsModel>(uri, 1, 0, "ReleaseAssetsModel");
    qmlRegisterType<Repo>(uri, 1, 0, "Repo");
    qmlRegisterType<ReposModel>(uri, 1, 0, "ReposModel");
    qmlRegisterType<TreeItem>(uri, 1, 0, "TreeItem");
    qmlRegisterType<TreeModel>(uri, 1, 0, "TreeModel");
    qmlRegisterType<TreeSortFilterModel>(uri, 1, 0, "TreeSortFilterModel");
    qmlRegisterType<User>(uri, 1, 0, "User");
    qmlRegisterType<UsersModel>(uri, 1, 0, "UsersModel");
    qmlRegisterType<Viewer>(uri, 1, 0, "Viewer");

    qmlRegisterSingletonType<SailHub>(uri,
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
