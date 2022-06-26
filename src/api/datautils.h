#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/file.h"
#include "src/entities/treeitem.h"
#include "src/models/notificationsmodel.h"
class DataUtils
{
public:
    // notifications
    static QList<NotificationListItem> notificationsFromJson(const QJsonArray &array);

    // file tree
    static QList<TreeItemListItem> treeListItemsFromJson(const QJsonObject &obj);
    static TreeItemListItem treeListItemFromJson(const QJsonObject &obj);

    // helper
    static QString getEmoji(const QString &string);
    static QString getEmojiLinkFromString(const QString &string);
    static QString getLinkFromString(const QString &string);
    static quint32 getTotalCount(const QJsonObject &obj);
    static quint32 getViewerAbilities(const QJsonObject &obj);
    static QString removeEmojiTags(const QString &text);
    static QString timeSpanText(const QDateTime &start, bool shortText = false);


};

#endif // DATAUTILS_H
