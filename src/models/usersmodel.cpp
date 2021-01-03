#include "usersmodel.h"

UsersModel::UsersModel(QObject *parent) :
    PaginationModel(parent)
{

}

void UsersModel::addUser(const UserListItem &user)
{
    beginInsertRows(QModelIndex(), m_users.count(), m_users.count());
    m_users.append(user);
    endInsertRows();
}

void UsersModel::addUsers(const QList<UserListItem> &users)
{
    beginInsertRows(QModelIndex(), m_users.count(), m_users.count() + users.count() - 1);
    m_users.append(users);
    endInsertRows();
}

void UsersModel::setUsers(const QList<UserListItem> &users)
{
    beginResetModel();
    m_users.clear();
    m_users = users;
    endResetModel();
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto user = m_users.at(index.row());

    switch (role) {
    case NameRole:
        return user.name;

    case AvatarUrlRole:
        return user.avatarUrl;

    case LoginRole:
        return user.login;

    case NodeIdRole:
        return user.nodeId;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AvatarUrlRole]        = "avatarUrl";
    roles[LoginRole]            = "login";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";

    return roles;
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_users.count();
}

void UsersModel::clear()
{
    beginResetModel();
    m_users.clear();
    endResetModel();
}
