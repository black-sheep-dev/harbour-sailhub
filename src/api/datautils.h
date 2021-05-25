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
    // notifications
    static QList<NotificationListItem> notificationsFromJson(const QJsonArray &array);

    // owner
    static Owner *ownerFromJson(const QJsonObject &obj);

    // page info
    static PageInfo pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count = QJsonValue());

    // file tree
    static QList<TreeItemListItem> treeListItemsFromJson(const QJsonObject &obj);
    static TreeItemListItem treeListItemFromJson(const QJsonObject &obj);

    // helper
    static QString getEmojiLinkFromString(const QString &string);
    static QString getLinkFromString(const QString &string);
    static quint16 getRepoFlags(const QJsonObject &obj);
    static quint32 getTotalCount(const QJsonObject &obj);
    static quint32 getViewerAbilities(const QJsonObject &obj);
    static QString removeEmojiTags(const QString &text);
    static QString timeSpanText(const QDateTime &start, bool shortText = false);


};

#endif // DATAUTILS_H
