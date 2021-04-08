#ifndef USERSMODEL_H
#define USERSMODEL_H

#include "paginationmodel.h"

#include "src/entities/user.h"

class UsersModel : public PaginationModel
{
    Q_OBJECT

public:
    enum UserRoles {
        AvatarUrlRole        = Qt::UserRole,
        LoginRole,
        NameRole,
        NodeIdRole,
    };
    Q_ENUM(UserRoles)

    explicit UsersModel(QObject *parent = nullptr);

    void addUser(const UserListItem &user);
    void addUsers(const QList<UserListItem> &users);
    void setUsers(const QList<UserListItem> &users);

private:
    QList<UserListItem> m_users;

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;


    // PaginationModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
};

#endif // USERSMODEL_H
