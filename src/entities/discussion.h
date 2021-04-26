#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "interactable.h"

#include <QDateTime>

struct DiscussionListItem {
    QString authorAvatar;
    QString authorLogin;
    QString category;
    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
    QString nodeId;
    QString title;
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class Discussion : public Interactable
{
    Q_OBJECT
public:
    explicit Discussion(QObject *parent = nullptr);

signals:

};

#endif // DISCUSSION_H
