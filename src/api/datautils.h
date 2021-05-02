#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/comment.h"
#include "src/entities/discussion.h"
#include "src/entities/discussioncategory.h"
#include "src/entities/discussioncomment.h"
#include "src/entities/file.h"
#include "src/entities/fundinglink.h"
#include "src/entities/gist.h"
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
    // comments
    static Comment *commentFromJson(const QJsonObject &obj);
    static QList<Comment *> commentsFromJson(const QJsonObject &obj);

    // discussions
    static Discussion *discussionFromJson(const QJsonObject &obj, Discussion *discussion = nullptr);
    static DiscussionListItem discussionListItemFromJson(const QJsonObject &obj);
    static QList<DiscussionListItem> discussionsFromJson(const QJsonObject &obj);

    // discussion categories
    static DiscussionCategoryListItem discussionCategoryListItemFromJson(const QJsonObject &obj);
    static QList<DiscussionCategoryListItem> discussionCategoriesFromJson(const QJsonObject &obj);

    // discussion comments
    static DiscussionComment *discussionCommentFromJson(const QJsonObject &obj);
    static QList<DiscussionComment *> discussionCommentsFromJson(const QJsonObject &obj);

    // gists
    static Gist *gistFromJson(const QJsonObject &obj, Gist *gist = nullptr);
    static GistListItem gistListItemFromJson(const QJsonObject &obj);
    static QList<GistListItem> gistsFromJson(const QJsonObject &obj);

    // issues
    static Issue *issueFromJson(const QJsonObject &obj, Issue *issue = nullptr);
    static IssueListItem issueListItemFromJson(const QJsonObject &obj);
    static QList<IssueListItem> issuesFromJson(const QJsonObject &obj);

    // labels
    static LabelListItem labelListItemFromJson(const QJsonObject &obj);
    static QList<LabelListItem> labelsFromJson(const QJsonObject &obj);

    // notifications
    static QList<NotificationListItem> notificationsFromJson(const QJsonArray &array);

    // organizations
    static Organization *organizationFromJson(const QJsonObject &obj, Organization *organization = nullptr);
    static OrganizationListItem organizationListItemFromJson(const QJsonObject &obj);
    static QList<OrganizationListItem> organizationsFromJson(const QJsonObject &obj);

    // owner
    static Owner *ownerFromJson(const QJsonObject &obj);

    // page info
    static PageInfo pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count = QJsonValue());

    // pull requests
    static PullRequest *pullRequestFromJson(const QJsonObject &obj);
    static QList<PullRequestListItem> pullRequestsFromJson(const QJsonObject &obj);
    static PullRequestListItem pullRequestListItemFromJson(const QJsonObject &obj);

    // releases
    static Release *releaseFromJson(const QJsonObject &obj);
    static ReleaseListItem releaseListItemFromJson(const QJsonObject &obj);
    static QList<ReleaseListItem> releasesFromJson(const QJsonObject &obj);
    static QList<ReleaseAssetListItem> releaseAssetsFromJson(const QJsonObject &obj);

    // repository
    static Repo *repoFromJson(const QJsonObject &obj);
    static QList<RepoListItem> reposFromJson(const QJsonObject &obj);
    static RepoListItem repoListItemFromJson(const QJsonObject &obj);

    // file tree
    static QList<TreeItemListItem> treeListItemsFromJson(const QJsonObject &obj);
    static TreeItemListItem treeListItemFromJson(const QJsonObject &obj);

    // user
    static User *userFromJson(const QJsonObject &obj, User *user = nullptr);
    static UserListItem userListItemFromJson(const QJsonObject &obj);
    static QList<UserListItem> usersFromJson(const QJsonObject &obj);

    // helper
    static QString timeSpanText(const QDateTime &start, bool shortText = false);

private:
    static QString getEmojiLinkFromString(const QString &string);
    static QString getLinkFromString(const QString &string);
    static quint16 getRepoFlags(const QJsonObject &obj);
    static quint8 getViewerPermission(const QString &permission);
    static quint32 getViewerAbilities(const QJsonObject &obj);
    static QJsonArray getNodes(const QJsonObject &obj);
    static void getInteractable(const QJsonObject &obj, Interactable *node);
    static quint32 getTotalCount(const QJsonObject &obj);
    static QString removeEmojiTags(const QString &text);
};

#endif // DATAUTILS_H
