#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/comment.h"
#include "src/entities/commit.h"
#include "src/entities/discussion.h"
#include "src/entities/discussioncategory.h"
#include "src/entities/discussioncomment.h"
#include "src/entities/file.h"
#include "src/entities/fundinglink.h"
#include "src/entities/gist.h"
#include "src/entities/issue.h"
#include "src/entities/label.h"
#include "src/entities/organization.h"
#include "src/entities/profilestatus.h"
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

    // discussion comments
    static DiscussionComment *discussionCommentFromJson(const QJsonObject &obj);
    static QList<DiscussionComment *> discussionCommentsFromJson(const QJsonObject &obj);

    // gists
    static Gist *gistFromJson(const QJsonObject &obj, Gist *gist = nullptr);

    // issues
    static Issue *issueFromJson(const QJsonObject &obj, Issue *issue = nullptr);

    // notifications
    static QList<NotificationListItem> notificationsFromJson(const QJsonArray &array);

    // organizations
    static Organization *organizationFromJson(const QJsonObject &obj, Organization *organization = nullptr);

    // owner
    static Owner *ownerFromJson(const QJsonObject &obj);

    // page info
    static PageInfo pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count = QJsonValue());

    // profile status
    static ProfileStatus *profileStatusFromJson(const QJsonObject &obj, ProfileStatus *status = nullptr);

    // pull requests
    static PullRequest *pullRequestFromJson(const QJsonObject &obj);

    // releases
    static Release *releaseFromJson(const QJsonObject &obj);

    // repository
    static Repo *repoFromJson(const QJsonObject &obj);

    // file tree
    static QList<TreeItemListItem> treeListItemsFromJson(const QJsonObject &obj);
    static TreeItemListItem treeListItemFromJson(const QJsonObject &obj);

    // user
    static User *userFromJson(const QJsonObject &obj, User *user = nullptr);

    // helper
    static QString getEmojiLinkFromString(const QString &string);
    static quint16 getRepoFlags(const QJsonObject &obj);
    static quint32 getTotalCount(const QJsonObject &obj);
    static quint32 getViewerAbilities(const QJsonObject &obj);
    static QString removeEmojiTags(const QString &text);
    static QString timeSpanText(const QDateTime &start, bool shortText = false);


private:

    static QString getLinkFromString(const QString &string);
    static QJsonArray getNodes(const QJsonObject &obj);
    static void getInteractable(const QJsonObject &obj, Interactable *node);

};

#endif // DATAUTILS_H
