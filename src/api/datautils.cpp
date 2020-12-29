#include "datautils.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonArray>
#include <QJsonObject>

#include "keys.h"

PageInfo DataUtils::pageInfoFromJson(const QJsonObject &obj)
{
    PageInfo info;

    const QJsonObject item = obj.value(SAILHUB_API_KEY_PAGE_INFO).toObject();
    if (item.isEmpty())
        return info;

    info.hasNextPage = item.value(SAILHUB_API_KEY_HAS_NEXT_PAGE).toBool();
    info.totalCount = getTotalCount(obj);
    info.lastItemCursor = item.value(SAILHUB_API_KEY_END_CURSOR).toString();

    return info;
}

Repo *DataUtils::repoFromJson(const QJsonObject &obj)
{
    if (obj.isEmpty())
        return nullptr;

    Repo *repo = new Repo;
    repo->setContributorCount(getTotalCount(obj.value(SAILHUB_API_KEY_MENTIONABLE_USERS).toObject()));
    repo->setDescription(obj.value(SAILHUB_API_KEY_DESCRIPTION).toString());
    repo->setForkCount(obj.value(SAILHUB_API_KEY_FORK_COUNT).toInt());
    repo->setHomepageUrl(obj.value(SAILHUB_API_KEY_HOMEPAGE_URL).toString());
    repo->setIsPrivate(obj.value(SAILHUB_API_KEY_IS_PRIVATE).toBool());
    repo->setIssuesCount(getTotalCount(obj.value(SAILHUB_API_KEY_ISSUES).toObject()));
    repo->setName(obj.value(SAILHUB_API_KEY_NAME).toString());
    repo->setNodeId(obj.value(SAILHUB_API_KEY_ID).toString());
    repo->setPullRequestsCount(getTotalCount(obj.value(SAILHUB_API_KEY_PULL_REQUESTS).toObject()));
    //repo->setReadme(obj.value(SAILHUB_API_KEY_OBJECT).toObject().value(SAILHUB_API_KEY_TEXT).toString());
    repo->setStargazerCount(obj.value(SAILHUB_API_KEY_STARGAZER_COUNT).toInt());
    repo->setWatcherCount(getTotalCount(obj.value(SAILHUB_API_KEY_WATCHERS).toObject()));

    const QJsonObject lic = obj.value(SAILHUB_API_KEY_LICENSE_INFO).toObject();
    License *license = new License(repo);
    license->setName(lic.value(SAILHUB_API_KEY_SPDX_ID).toString());
    license->setUrl(lic.value(SAILHUB_API_KEY_URL).toString());
    repo->setLicense(license);

    const QJsonObject own = obj.value(SAILHUB_API_KEY_OWNER).toObject();
    Owner *owner = new Owner(repo);
    owner->setNodeId(own.value(SAILHUB_API_KEY_ID).toString());
    owner->setLogin(own.value(SAILHUB_API_KEY_LOGIN).toString());
    owner->setAvatarUrl(own.value(SAILHUB_API_KEY_AVATAR_URL).toString());
    repo->setOwner(owner);

    return repo;
}

QList<RepoListItem> DataUtils::reposFromJson(const QJsonObject &obj)
{
    QList<RepoListItem>  repos;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        repos.append(repoListItemFromJson(node.toObject()));
    }

    return repos;
}


RepoListItem DataUtils::repoListItemFromJson(const QJsonObject &obj)
{
    RepoListItem item;

    item.description = obj.value(SAILHUB_API_KEY_SHORT_DESCRIPTION_HTML).toString();
    item.name = obj.value(SAILHUB_API_KEY_NAME).toString();
    item.nodeId = obj.value(SAILHUB_API_KEY_ID).toString();
    item.owner = obj.value(SAILHUB_API_KEY_OWNER).toObject()
                 .value(SAILHUB_API_KEY_LOGIN).toString();
    item.stargazerCount = quint32(obj.value(SAILHUB_API_KEY_STARGAZER_COUNT).toInt());

    const QJsonObject lang = obj.value(SAILHUB_API_KEY_PRIMARY_LANGUAGE).toObject();
    item.language.name = lang.value(SAILHUB_API_KEY_NAME).toString();
    item.language.color = lang.value(SAILHUB_API_KEY_COLOR).toString();

    return item;
}

User *DataUtils::userFromJson(const QJsonObject &obj)
{
    User *user = new User;

    user->setAvatarUrl(obj.value(SAILHUB_API_KEY_AVATAR_URL).toString());
    user->setBio(obj.value(SAILHUB_API_KEY_BIO).toString());
    user->setCompany(obj.value(SAILHUB_API_KEY_COMPANY).toString());
    user->setFollowers(getTotalCount(obj.value(SAILHUB_API_KEY_FOLLOWERS).toObject()));
    user->setFollowing(getTotalCount(obj.value(SAILHUB_API_KEY_FOLLOWING).toObject()));
    user->setLocation(obj.value(SAILHUB_API_KEY_LOCATION).toString());
    user->setLogin(obj.value(SAILHUB_API_KEY_LOGIN).toString());
    user->setName(obj.value(SAILHUB_API_KEY_NAME).toString());
    user->setNodeId(obj.value(SAILHUB_API_KEY_ID).toString());
    user->setOrganizations(getTotalCount(obj.value(SAILHUB_API_KEY_ORGANIZATIONS).toObject()));
    user->setRepositories(getTotalCount(obj.value(SAILHUB_API_KEY_REPOSITORIES).toObject()));
    user->setStarredRepositories(getTotalCount(obj.value(SAILHUB_API_KEY_STARRED_REPOSITORIES).toObject()));
    user->setTwitterUsername(obj.value(SAILHUB_API_KEY_TWITTER_USERNAME).toString());
    user->setWebsiteUrl(obj.value(SAILHUB_API_KEY_WEBSITE_URL).toString());

    // user status
    const QJsonObject status = obj.value(SAILHUB_API_KEY_STATUS).toObject();

    UserStatus sta;
    sta.emoji = status.value(SAILHUB_API_KEY_EMOJI).toString();
    sta.message = status.value(SAILHUB_API_KEY_MESSAGE).toString();

    user ->setStatus(sta);

    return user;
}

UserListItem DataUtils::userListItemFromJson(const QJsonObject &obj)
{
    UserListItem item;

    item.avatarUrl = obj.value(SAILHUB_API_KEY_AVATAR_URL).toString();
    item.login = obj.value(SAILHUB_API_KEY_LOGIN).toString();
    item.name = obj.value(SAILHUB_API_KEY_NAME).toString();
    item.nodeId = obj.value(SAILHUB_API_KEY_ID).toString();

    return item;
}

QList<UserListItem> DataUtils::usersFromJson(const QJsonObject &obj)
{
    QList<UserListItem>  users;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        users.append(userListItemFromJson(node.toObject()));
    }

    return users;
}

QJsonArray DataUtils::getNodes(const QJsonObject &obj)
{
    return obj.value(SAILHUB_API_KEY_NODES).toArray();
}

quint32 DataUtils::getTotalCount(const QJsonObject &obj)
{
    return quint32(obj.value(SAILHUB_API_KEY_TOTAL_COUNT).toInt());
}
