#include "datautils.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonArray>
#include <QJsonObject>

#include "keys.h"

Comment *DataUtils::commentFromJson(const QJsonObject &obj)
{
    Comment *comment = new Comment;

    Owner *author = ownerFromJson(obj.value(SAILHUB_API_KEY_AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(comment);
        comment->setAuthor(author);
    }

    comment->setBody(obj.value(SAILHUB_API_KEY_BODY_HTML).toString());
    comment->setCreatedAt(QDateTime::fromString(obj.value(SAILHUB_API_KEY_CREATED_AT).toString(), Qt::ISODate));
    comment->setLastEditAt(QDateTime::fromString(obj.value(SAILHUB_API_KEY_LAST_EDITED_AT).toString(), Qt::ISODate));
    comment->setViewerCanDelete(obj.value(SAILHUB_API_KEY_VIEWER_CAN_DELETE).toBool());
    comment->setViewerCanReact(obj.value(SAILHUB_API_KEY_VIEWER_CAN_REACT).toBool());
    comment->setViewerCanUpdate(obj.value(SAILHUB_API_KEY_VIEWER_CAN_UPDATE).toBool());
    comment->setViewerDidAuthor(obj.value(SAILHUB_API_KEY_VIEWER_DID_AUTHOR).toBool());


    return comment;
}

QList<Comment *> DataUtils::commentsFromJson(const QJsonObject &obj)
{
    QList<Comment *> comments;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject comment = node.toObject();
        if (comment.isEmpty())
            continue;

        comments.append(commentFromJson(comment));
    }

    return comments;
}

Issue *DataUtils::issueFromJson(const QJsonObject &obj)
{
    Issue *issue = new Issue;

    issue->setNodeId(obj.value(SAILHUB_API_KEY_ID).toString());
    issue->setTitle(obj.value(SAILHUB_API_KEY_TITLE).toString());
    issue->setStates(obj.value(SAILHUB_API_KEY_STATE).toInt());
    issue->setCommentCount(getTotalCount(obj.value(SAILHUB_API_KEY_COMMENTS).toObject()));

    Owner *author = ownerFromJson(obj.value(SAILHUB_API_KEY_AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(issue);
        issue->setAuthor(author);
    }

    return issue;
}

IssueListItem DataUtils::issueListItemFromJson(const QJsonObject &obj)
{
    IssueListItem item;

    item.nodeId = obj.value(SAILHUB_API_KEY_ID).toString();
    item.closed = obj.value(SAILHUB_API_KEY_CLOSED).toBool();
    item.commentCount = getTotalCount(obj.value(SAILHUB_API_KEY_COMMENTS).toObject());
    item.createdAt = QDateTime::fromString(obj.value(SAILHUB_API_KEY_CREATED_AT).toString(), Qt::ISODate);
    item.number = obj.value(SAILHUB_API_KEY_NUMBER).toInt();
    item.repository = obj.value(SAILHUB_API_KEY_REPOSITORY).toObject()
                         .value(SAILHUB_API_KEY_NAME_WITH_OWNER).toString();

    const QString state = obj.value(SAILHUB_API_KEY_STATE).toString();
    if (state == QLatin1Literal("OPEN"))
        item.state = Issue::StateOpen;
    else if (state == QLatin1Literal("CLOSED"))
        item.state = Issue::StateClosed;

    item.title = obj.value(SAILHUB_API_KEY_TITLE).toString();

    qDebug() << item.createdAt;

    return item;
}

QList<IssueListItem> DataUtils::issuesFromJson(const QJsonObject &obj)
{
    QList<IssueListItem> issues;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject issue = node.toObject();
        if (issue.isEmpty())
            continue;

        issues.append(issueListItemFromJson(issue));
    }

    return issues;
}

Owner *DataUtils::ownerFromJson(const QJsonObject &obj)
{
    Owner *owner = new Owner;
    owner->setNodeId(obj.value(SAILHUB_API_KEY_ID).toString());
    owner->setLogin(obj.value(SAILHUB_API_KEY_LOGIN).toString());
    owner->setAvatarUrl(obj.value(SAILHUB_API_KEY_AVATAR_URL).toString());

    return owner;
}

PageInfo DataUtils::pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count)
{
    PageInfo info;

    const QJsonObject item = obj.value(SAILHUB_API_KEY_PAGE_INFO).toObject();
    if (item.isEmpty())
        return info;

    info.hasNextPage = item.value(SAILHUB_API_KEY_HAS_NEXT_PAGE).toBool();
    info.totalCount = count.toInt();
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
    repo->setViewerCanSubscribe(obj.value(SAILHUB_API_KEY_VIEWER_CAN_SUBSCRIBE).toBool());
    repo->setViewerHasStarred(obj.value(SAILHUB_API_KEY_VIEWER_HAS_STARRED).toBool());
    repo->setViewerSubscription(obj.value(SAILHUB_API_KEY_VIEWER_SUBSCRIPTION).toInt());
    repo->setWatcherCount(getTotalCount(obj.value(SAILHUB_API_KEY_WATCHERS).toObject()));

    const QJsonObject lic = obj.value(SAILHUB_API_KEY_LICENSE_INFO).toObject();
    License *license = new License(repo);
    license->setName(lic.value(SAILHUB_API_KEY_SPDX_ID).toString());
    license->setUrl(lic.value(SAILHUB_API_KEY_URL).toString());
    repo->setLicense(license);


    Owner *owner = ownerFromJson(obj.value(SAILHUB_API_KEY_OWNER).toObject());
    if (owner != nullptr) {
        owner->setParent(repo);
        repo->setOwner(owner);
    }

    // subscription
    const QString subscription = obj.value(SAILHUB_API_KEY_VIEWER_SUBSCRIPTION).toString();
    if (subscription == QLatin1String("IGNORED")) {
        repo->setViewerSubscription(Repo::SubscriptionIgnored);
    } else if (subscription == QLatin1String("SUBSCRIBED")) {
        repo->setViewerSubscription(Repo::Subscribed);
    } else if (subscription == QLatin1String("UNSUBSCRIBED")) {
        repo->setViewerSubscription(Repo::Unsubscribed);
    }

    return repo;
}

QList<RepoListItem> DataUtils::reposFromJson(const QJsonObject &obj)
{
    QList<RepoListItem>  repos;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject repo = node.toObject();
        if (repo.isEmpty())
            continue;

        repos.append(repoListItemFromJson(repo));
    }

    return repos;
}


RepoListItem DataUtils::repoListItemFromJson(const QJsonObject &obj)
{
    RepoListItem item;

    item.description = obj.value(SAILHUB_API_KEY_SHORT_DESCRIPTION_HTML).toString();
    item.isPrivate = obj.value(SAILHUB_API_KEY_IS_PRIVATE).toBool();
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

User *DataUtils::userFromJson(const QJsonObject &obj, User *user)
{
    if (user == nullptr)
        user = new User;

    user->setAvatarUrl(obj.value(SAILHUB_API_KEY_AVATAR_URL).toString());
    user->setBio(obj.value(SAILHUB_API_KEY_BIO).toString());
    user->setCompany(obj.value(SAILHUB_API_KEY_COMPANY).toString());
    user->setFollowers(getTotalCount(obj.value(SAILHUB_API_KEY_FOLLOWERS).toObject()));
    user->setFollowing(getTotalCount(obj.value(SAILHUB_API_KEY_FOLLOWING).toObject()));
    user->setLocation(obj.value(SAILHUB_API_KEY_LOCATION).toString());
    user->setLogin(obj.value(SAILHUB_API_KEY_LOGIN).toString());
    user->setIsViewer(obj.value(SAILHUB_API_KEY_IS_VIEWER).toBool());
    user->setName(obj.value(SAILHUB_API_KEY_NAME).toString());
    user->setNodeId(obj.value(SAILHUB_API_KEY_ID).toString());
    user->setOrganizations(getTotalCount(obj.value(SAILHUB_API_KEY_ORGANIZATIONS).toObject()));
    user->setRepositories(getTotalCount(obj.value(SAILHUB_API_KEY_REPOSITORIES).toObject()));
    user->setStarredRepositories(getTotalCount(obj.value(SAILHUB_API_KEY_STARRED_REPOSITORIES).toObject()));
    user->setTwitterUsername(obj.value(SAILHUB_API_KEY_TWITTER_USERNAME).toString());
    user->setViewerIsFollowing(obj.value(SAILHUB_API_KEY_VIEWER_IS_FOLLOWING).toBool());
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
        const QJsonObject user = node.toObject();
        if (user.isEmpty())
            continue;

        users.append(userListItemFromJson(user));
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
