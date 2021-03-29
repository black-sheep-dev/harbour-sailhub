#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <QList>

#include "src/entities/issue.h"
#include "src/entities/organization.h"
#include "src/entities/repo.h"
#include "src/entities/user.h"
#include "src/models/paginationmodel.h"

class DataUtils
{
public:
    static Comment *commentFromJson(const QJsonObject &obj);
    static QList<Comment *> commentsFromJson(const QJsonObject &obj);
    static Issue *issueFromJson(const QJsonObject &obj);
    static IssueListItem issueListItemFromJson(const QJsonObject &obj);
    static QList<IssueListItem> issuesFromJson(const QJsonObject &obj);
    static Organization *organizationFromJson(const QJsonObject &obj, Organization *organization = nullptr);
    static OrganizationListItem organizationListItemFromJson(const QJsonObject &obj);
    static QList<OrganizationListItem> organizationsFromJson(const QJsonObject &obj);
    static Owner *ownerFromJson(const QJsonObject &obj);
    static PageInfo pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count = QJsonValue());
    static Repo *repoFromJson(const QJsonObject &obj);
    static QList<RepoListItem> reposFromJson(const QJsonObject &obj);
    static RepoListItem repoListItemFromJson(const QJsonObject &obj);
    static User *userFromJson(const QJsonObject &obj, User *user = nullptr);
    static UserListItem userListItemFromJson(const QJsonObject &obj);
    static QList<UserListItem> usersFromJson(const QJsonObject &obj);

private:
    static QJsonArray getNodes(const QJsonObject &obj);
    static quint32 getTotalCount(const QJsonObject &obj);
};

#endif // DATAUTILS_H
