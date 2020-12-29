#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/repo.h"
#include "src/entities/user.h"
#include "src/models/paginationmodel.h"

class DataUtils
{
public:
    static PageInfo pageInfoFromJson(const QJsonObject &obj);
    static Repo *repoFromJson(const QJsonObject &obj);
    static QList<RepoListItem> reposFromJson(const QJsonObject &obj);
    static RepoListItem repoListItemFromJson(const QJsonObject &obj);
    static User *userFromJson(const QJsonObject &obj);
    static UserListItem userListItemFromJson(const QJsonObject &obj);
    static QList<UserListItem> usersFromJson(const QJsonObject &obj);

private:
    static QJsonArray getNodes(const QJsonObject &obj);
    static quint32 getTotalCount(const QJsonObject &obj);
};

#endif // DATAUTILS_H
