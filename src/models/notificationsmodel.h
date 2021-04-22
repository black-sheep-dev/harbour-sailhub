#ifndef NOTIFICATIONSMODEL_H
#define NOTIFICATIONSMODEL_H

#include <QAbstractListModel>

#include "src/entities/notificationobject.h"

class NotificationsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(QByteArray uuid READ uuid NOTIFY uuidChanged)

public:
    enum NotificationRoles {
        IdRole              = Qt::UserRole + 1,
        LastReadAtRole,
        NumberRole,
        ReasonRole,
        RepoIdRole,
        RepoNameRole,
        TitleRole,
        TypeRole,
        UnreadRole,
        UpdatedAtRole,
        UpdatedAtTimeSpanRole
    };
    Q_ENUM(NotificationRoles)

    explicit NotificationsModel(QObject *parent = nullptr);

    void addNotifications(const QList<NotificationListItem> &items);
    void setNotifications(const QList<NotificationListItem> &items);

    // properties
    bool loading() const;
    QByteArray uuid() const;

signals:
    // properties
    void loadingChanged(bool loading);
    void uuidChanged(const QByteArray &uuid);

public slots:
    // properties
    void setLoading(bool loading);

private:
    QList<NotificationListItem> m_notifications;

    // properties
    bool m_loading{false};
    QByteArray m_uuid;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // NOTIFICATIONSMODEL_H
