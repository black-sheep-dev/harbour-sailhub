#include "notificationsmodel.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QUuid>

#include "src/api/keys.h"

NotificationsModel::NotificationsModel(QObject *parent) :
    QAbstractListModel(parent),
    m_uuid(QUuid::createUuid().toByteArray())
{

}

NotificationsModel::~NotificationsModel()
{
    m_notifications.clear();
}

void NotificationsModel::addNotifications(const QList<NotificationListItem> &items)
{
    beginInsertRows(QModelIndex(), m_notifications.count(), m_notifications.count() + items.count() - 1);
    m_notifications.append(items);
    endInsertRows();

    setLoading(false);
}

void NotificationsModel::setNotifications(const QList<NotificationListItem> &items)
{
    beginResetModel();
    m_notifications.clear();
    m_notifications = items;
    endResetModel();

    setLoading(false);
}

bool NotificationsModel::loading() const
{
    return m_loading;
}

QByteArray NotificationsModel::uuid() const
{
    return m_uuid;
}

void NotificationsModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

int NotificationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_notifications.count();
}

QVariant NotificationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto notification = m_notifications.at(index.row());

    switch (role) {
    case IdRole:
        return notification.id;

    case LastReadAtRole:
        return notification.lastReadAt;

    case NumberRole:
        return notification.number;

    case ReasonRole:
        return notification.reason;

    case RepoIdRole:
        return notification.repoId;

    case RepoNameRole:
        return notification.repoName;

    case TitleRole:
        return notification.title;

    case TypeRole:
        return notification.type;

    case UnreadRole:
        return notification.unread;

    case UpdatedAtRole:
        return notification.updatedAt;

    case UpdatedAtTimeSpanRole:
        return notification.updatedAtTimeSpan;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NotificationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole]                   = "id";
    roles[LastReadAtRole]           = "lastReadAt";
    roles[NumberRole]               = "number";
    roles[ReasonRole]               = "reason";
    roles[RepoIdRole]               = "repoId";
    roles[RepoNameRole]             = "repoName";
    roles[TitleRole]                = "title";
    roles[TypeRole]                 = "type";
    roles[UnreadRole]               = "unread";
    roles[UpdatedAtRole]            = "updatedAt";
    roles[UpdatedAtTimeSpanRole]    = "updatedAtTimeSpan";

    return roles;
}
