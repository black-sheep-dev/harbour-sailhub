#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/comment.h"
#include "src/entities/file.h"
#include "src/entities/issue.h"
#include "src/entities/label.h"
#include "src/entities/organization.h"
#include "src/entities/pullrequest.h"
#include "src/entities/release.h"
#include "src/entities/releaseasset.h"
#include "src/entities/repo.h"
#include "src/entities/treeitem.h"
#include "src/entities/user.h"
#include "src/models/notificationsmodel.h"
#include "src/models/paginationmodel.h"

class DataUtils
{
public:
    // entities
    static Comment *commentFromJson(const QJsonObject &obj);
    static QList<Comment *> commentsFromJson(const QJsonObject &obj);
    static Issue *issueFromJson(const QJsonObject &obj, Issue *issue = nullptr);
    static IssueListItem issueListItemFromJson(const QJsonObject &obj);
    static QList<IssueListItem> issuesFromJson(const QJsonObject &obj);
    static LabelListItem labelListItemFromJson(const QJsonObject &obj);
    static QList<LabelListItem> labelsFromJson(const QJsonObject &obj);
    static QList<NotificationListItem> notificationsFromJson(const QJsonArray &array);
    static Organization *organizationFromJson(const QJsonObject &obj, Organization *organization = nullptr);
    static OrganizationListItem organizationListItemFromJson(const QJsonObject &obj);
    static QList<OrganizationListItem> organizationsFromJson(const QJsonObject &obj);
    static Owner *ownerFromJson(const QJsonObject &obj);
    static PageInfo pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count = QJsonValue());
    static PullRequest *pullRequestFromJson(const QJsonObject &obj);
    static QList<PullRequestListItem> pullRequestsFromJson(const QJsonObject &obj);
    static PullRequestListItem pullRequestListItemFromJson(const QJsonObject &obj);
    static Release *releaseFromJson(const QJsonObject &obj);
    static ReleaseListItem releaseListItemFromJson(const QJsonObject &obj);
    static QList<ReleaseListItem> releaseListItemsFromJson(const QJsonObject &obj);
    static QList<ReleaseAssetListItem> releaseAssetListItemsFromJson(const QJsonObject &obj);
    static Repo *repoFromJson(const QJsonObject &obj);
    static QList<RepoListItem> reposFromJson(const QJsonObject &obj);
    static RepoListItem repoListItemFromJson(const QJsonObject &obj);
    static QList<TreeItemListItem> treeListItemsFromJson(const QJsonObject &obj);
    static TreeItemListItem treeListItemFromJson(const QJsonObject &obj);
    static User *userFromJson(const QJsonObject &obj, User *user = nullptr);
    static UserListItem userListItemFromJson(const QJsonObject &obj);
    static QList<UserListItem> usersFromJson(const QJsonObject &obj);

    // helper
    static QString timeSpanText(const QDateTime &start, bool shortText = false);

private:
    static quint8 getViewerPermission(const QString &permission);
    static quint32 getViewerAbilities(const QJsonObject &obj);
    static QJsonArray getNodes(const QJsonObject &obj);
    static void getInteractable(const QJsonObject &obj, Interactable *node);
    static quint32 getTotalCount(const QJsonObject &obj);
};

#endif // DATAUTILS_H
