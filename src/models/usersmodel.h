#ifndef USERSMODEL_H
#define USERSMODEL_H

#include "nodesmodel.h"

#include "src/entities/user.h"

class UsersModel : public NodesModel
{
    Q_OBJECT

public:
    enum UserRoles {
        AvatarUrlRole        = NodesModel::CustomRole + 1,
        BioRole,
        BlogRole,
        CompanyRole,
        EmailRole,
        FollowersRole,
        FollowingRole,
        GravatarIdRole,
        HireableRole,
        LocationRole,
        LoginRole,
        PublicReposRole,
        PublicGistsRole,
        ScoreRole,
        TwitterUsernameRole,
        UserTypeRole
    };
    Q_ENUM(UserRoles)

    explicit UsersModel(QObject *parent = nullptr);

    Q_INVOKABLE User *userAt(int index);
    Q_INVOKABLE User *userById(quint32 id);
    Q_INVOKABLE User *userById(const QString &id);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // USERSMODEL_H
