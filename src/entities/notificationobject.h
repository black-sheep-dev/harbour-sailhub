#ifndef NOTIFICATIONOBJECT_H
#define NOTIFICATIONOBJECT_H

#include <QObject>
#include <QDateTime>

struct NotificationListItem {
    NotificationListItem() = default;
    NotificationListItem(const QJsonObject &data);

    QString id;
    QDateTime lastReadAt;
    quint32 number{0};
    quint8 reason{0};
    QString repoId;
    QString repoName;
    QString title;
    quint8 type{0};
    bool unread{false};
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class NotificationObject : public QObject
{
    Q_OBJECT

public:
    enum NotificationReason {
        UndefinedReason,
        Assign,
        Author,
        Comment,
        Invitation,
        Manual,
        Mention,
        ReviewRequest,
        SecurityAlert,
        StateChange,
        Subscribed,
        TeamMention
    };
    Q_ENUM(NotificationReason)

    enum NotificationType {
        UnknownType,
        Issue,
        PullRequest,
        RepositoryVulnerabilityAlert
    };
    Q_ENUM(NotificationType)

    explicit NotificationObject(QObject *parent = nullptr);

};

#endif // NOTIFICATIONOJECT_H
