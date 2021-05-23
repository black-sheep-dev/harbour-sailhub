#ifndef DISCUSSIONCATEGORY_H
#define DISCUSSIONCATEGORY_H

#include "node.h"

struct DiscussionCategoryListItem : public NodeListItem {
    DiscussionCategoryListItem() = default;
    DiscussionCategoryListItem(const QJsonObject &obj);

    QString description;
    QString emoji;
};

class DiscussionCategory : public QObject
{
    Q_OBJECT
public:
    explicit DiscussionCategory(QObject *parent = nullptr);

signals:

};

#endif // DISCUSSIONCATEGORY_H
