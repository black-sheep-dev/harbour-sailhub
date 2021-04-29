#ifndef DISCUSSIONCATEGORY_H
#define DISCUSSIONCATEGORY_H

#include <QObject>

struct DiscussionCategoryListItem {
    QString description;
    QString emoji;
    QString name;
    QString nodeId;
};

class DiscussionCategory : public QObject
{
    Q_OBJECT
public:
    explicit DiscussionCategory(QObject *parent = nullptr);

signals:

};

#endif // DISCUSSIONCATEGORY_H
