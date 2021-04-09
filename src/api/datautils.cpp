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

    auto author = ownerFromJson(obj.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(comment);
        comment->setAuthor(author);
    }

    comment->setNodeId(obj.value(ApiKey::ID).toString());
    comment->setBody(obj.value(ApiKey::BODY_HTML).toString());

    const QString excerpt = obj.value(ApiKey::BODY_TEXT).toString().mid(0, 160);
    comment->setBodyExcerpt(excerpt.mid(0, excerpt.lastIndexOf(' ')).simplified());

    comment->setCreatedAt(QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    comment->setCreatedAtTimeSpan(timeSpanText(comment->createdAt(), true));
    comment->setLastEditAt(QDateTime::fromString(obj.value(ApiKey::LAST_EDITED_AT).toString(), Qt::ISODate));
    comment->setViewerCanDelete(obj.value(ApiKey::VIEWER_CAN_DELETE).toBool());
    comment->setViewerCanReact(obj.value(ApiKey::VIEWER_CAN_REACT).toBool());
    comment->setViewerCanUpdate(obj.value(ApiKey::VIEWER_CAN_UPDATE).toBool());
    comment->setViewerDidAuthor(obj.value(ApiKey::VIEWER_DID_AUTHOR).toBool());

    comment->setEdited(comment->createdAt() < comment->lastEditAt());

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

    issue->setNodeId(obj.value(ApiKey::ID).toString());
    issue->setTitle(obj.value(ApiKey::TITLE).toString());
    issue->setBody(obj.value(ApiKey::BODY_HTML).toString());
    issue->setCreatedAt(QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    issue->setCreatedAtTimeSpan(timeSpanText(issue->createdAt(), true));
    issue->setNumber(obj.value(ApiKey::NUMBER).toInt());
    issue->setRepository(obj.value(ApiKey::REPOSITORY).toObject()
                         .value(ApiKey::NAME_WITH_OWNER).toString());
    issue->setStates(obj.value(ApiKey::STATE).toInt());
    issue->setCommentCount(getTotalCount(obj.value(ApiKey::COMMENTS).toObject()));
    issue->setUpdatedAt(QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate));
    issue->setEdited(issue->updatedAt() > issue->createdAt());
    issue->setViewerCanUpdate(obj.value(ApiKey::VIEWER_CAN_UPDATE).toBool());

    Owner *author = ownerFromJson(obj.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(issue);
        issue->setAuthor(author);
    }

    return issue;
}

IssueListItem DataUtils::issueListItemFromJson(const QJsonObject &obj)
{
    IssueListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();
    item.closed = obj.value(ApiKey::CLOSED).toBool();
    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.number = obj.value(ApiKey::NUMBER).toInt();
    item.repository = obj.value(ApiKey::REPOSITORY).toObject()
                         .value(ApiKey::NAME_WITH_OWNER).toString();

    const QString state = obj.value(ApiKey::STATE).toString();
    if (state == QLatin1Literal("OPEN"))
        item.state = Issue::StateOpen;
    else if (state == QLatin1Literal("CLOSED"))
        item.state = Issue::StateClosed;

    item.title = obj.value(ApiKey::TITLE).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);

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

Organization *DataUtils::organizationFromJson(const QJsonObject &obj, Organization *organization)
{
    if (organization == nullptr)
        organization = new Organization;

    organization->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());
    organization->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    organization->setEmail(obj.value(ApiKey::EMAIL).toString());
    organization->setLocation(obj.value(ApiKey::LOCATION).toString());
    organization->setLogin(obj.value(ApiKey::LOGIN).toString());
    organization->setMembers(getTotalCount(obj.value(ApiKey::MEMBERS_WITH_ROLE).toObject()));
    organization->setName(obj.value(ApiKey::NAME).toString());
    organization->setNodeId(obj.value(ApiKey::ID).toString());
    organization->setProjects(getTotalCount(obj.value(ApiKey::PROJECTS).toObject()));
    organization->setRepositories(getTotalCount(obj.value(ApiKey::REPOSITORIES).toObject()));
    organization->setTeams(getTotalCount(obj.value(ApiKey::TEAMS).toObject()));
    organization->setTwitterUsername(obj.value(ApiKey::TWITTER_USERNAME).toString());
    organization->setViewerIsMember(obj.value(ApiKey::VIEWER_IS_MEMBER).toBool());
    organization->setViewerIsSponsoring(obj.value(ApiKey::VIEWER_IS_SPONSORING).toBool());
    organization->setWebsiteUrl(obj.value(ApiKey::WEBSITE_URL).toString());

    return organization;
}

OrganizationListItem DataUtils::organizationListItemFromJson(const QJsonObject &obj)
{
    OrganizationListItem item;

    item.avatarUrl = obj.value(ApiKey::AVATAR_URL).toString();
    item.description = obj.value(ApiKey::DESCRIPTION).toString();
    item.login = obj.value(ApiKey::LOGIN).toString();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();

    return item;
}

QList<OrganizationListItem> DataUtils::organizationsFromJson(const QJsonObject &obj)
{
    QList<OrganizationListItem>  organizations;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject organization = node.toObject();
        if (organization.isEmpty())
            continue;

        organizations.append(organizationListItemFromJson(organization));
    }

    return organizations;
}

Owner *DataUtils::ownerFromJson(const QJsonObject &obj)
{
    Owner *owner = new Owner;
    owner->setNodeId(obj.value(ApiKey::ID).toString());
    owner->setLogin(obj.value(ApiKey::LOGIN).toString());
    owner->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());

    return owner;
}

PageInfo DataUtils::pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count)
{
    PageInfo info;

    const QJsonObject item = obj.value(ApiKey::PAGE_INFO).toObject();
    if (item.isEmpty())
        return info;

    info.hasNextPage = item.value(ApiKey::HAS_NEXT_PAGE).toBool();
    info.totalCount = count.toInt();
    info.lastItemCursor = item.value(ApiKey::END_CURSOR).toString();

    return info;
}

QList<PullRequestListItem> DataUtils::pullRequestsFromJson(const QJsonObject &obj)
{
    QList<PullRequestListItem>  prs;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject pr = node.toObject();
        if (pr.isEmpty())
            continue;

        prs.append(pullRequestListItemFromJson(pr));
    }

    return prs;
}

PullRequestListItem DataUtils::pullRequestListItemFromJson(const QJsonObject &obj)
{
    PullRequestListItem item;

    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.number = quint32(obj.value(ApiKey::NUMBER).toInt());
    item.repository = obj.value(ApiKey::REPOSITORY).toObject()
            .value(ApiKey::NAME_WITH_OWNER).toString();

    const QString state = obj.value(ApiKey::STATE).toString();
    if (state == QLatin1Literal("OPEN"))
        item.state = PullRequest::StateOpen;
    else if (state == QLatin1Literal("CLOSED"))
        item.state = PullRequest::StateClosed;
    else if (state == QLatin1Literal("MERGED"))
        item.state = PullRequest::StateMerged;

    item.timeSpan = timeSpanText(item.createdAt, true);
    item.title = obj.value(ApiKey::TITLE).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);

    return item;
}

Repo *DataUtils::repoFromJson(const QJsonObject &obj)
{
    if (obj.isEmpty())
        return nullptr;

    Repo *repo = new Repo;

    QStringList branches;

    const QJsonArray nodes = getNodes(obj.value(ApiKey::REFS).toObject());

    for (const auto &node : nodes) {
        branches.append(node.toObject().value(ApiKey::NAME).toString());
    }
    repo->setBranches(branches);

    repo->setContributorCount(getTotalCount(obj.value(ApiKey::MENTIONABLE_USERS).toObject()));
    repo->setDefaultBranch(obj.value(ApiKey::DEFAULT_BRANCH_REF).toObject()
                           .value(ApiKey::NAME).toString());
    repo->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    repo->setForkCount(obj.value(ApiKey::FORK_COUNT).toInt());
    repo->setHomepageUrl(obj.value(ApiKey::HOMEPAGE_URL).toString());
    repo->setIsPrivate(obj.value(ApiKey::IS_PRIVATE).toBool());
    repo->setIssuesCount(getTotalCount(obj.value(ApiKey::ISSUES).toObject()));
    repo->setName(obj.value(ApiKey::NAME).toString());
    repo->setNodeId(obj.value(ApiKey::ID).toString());
    repo->setProjects(getTotalCount(obj.value(ApiKey::PROJECTS).toObject()));
    repo->setReleases(getTotalCount(obj.value(ApiKey::RELEASES).toObject()));
    repo->setPullRequestsCount(getTotalCount(obj.value(ApiKey::PULL_REQUESTS).toObject()));
    //repo->setReadme(obj.value(ApiKey::OBJECT).toObject().value(ApiKey::TEXT).toString());
    repo->setReleases(getTotalCount(obj.value(ApiKey::RELEASES).toObject()));
    repo->setStargazerCount(obj.value(ApiKey::STARGAZER_COUNT).toInt());
    repo->setViewerCanSubscribe(obj.value(ApiKey::VIEWER_CAN_SUBSCRIBE).toBool());
    repo->setViewerHasStarred(obj.value(ApiKey::VIEWER_HAS_STARRED).toBool());
    repo->setViewerSubscription(obj.value(ApiKey::VIEWER_SUBSCRIPTION).toInt());
    repo->setWatcherCount(getTotalCount(obj.value(ApiKey::WATCHERS).toObject()));

    const QJsonObject lic = obj.value(ApiKey::LICENSE_INFO).toObject();
    License *license = new License(repo);
    license->setName(lic.value(ApiKey::SPDX_ID).toString());
    license->setUrl(lic.value(ApiKey::URL).toString());
    repo->setLicense(license);


    Owner *owner = ownerFromJson(obj.value(ApiKey::OWNER).toObject());
    if (owner != nullptr) {
        owner->setParent(repo);
        repo->setOwner(owner);
    }

    // subscription
    const QString subscription = obj.value(ApiKey::VIEWER_SUBSCRIPTION).toString();
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

    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.description = obj.value(ApiKey::SHORT_DESCRIPTION_HTML).toString();
    item.isPrivate = obj.value(ApiKey::IS_PRIVATE).toBool();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();
    item.owner = obj.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::LOGIN).toString();
    item.pushedAt = QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    item.stargazerCount = quint32(obj.value(ApiKey::STARGAZER_COUNT).toInt());

    const QJsonObject lang = obj.value(ApiKey::PRIMARY_LANGUAGE).toObject();
    item.language.name = lang.value(ApiKey::NAME).toString();
    item.language.color = lang.value(ApiKey::COLOR).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

    return item;
}

QList<TreeItemListItem> DataUtils::treeListItemsFromJson(const QJsonObject &obj)
{
    QList<TreeItemListItem> items;

    const QJsonArray entries = obj.value(ApiKey::NODE).toObject()
            .value(ApiKey::REF).toObject()
            .value(ApiKey::TARGET).toObject()
            .value(ApiKey::FILE).toObject()
            .value(ApiKey::OBJECT).toObject()
            .value(ApiKey::ENTRIES).toArray();

    for (const auto &entry : entries) {
        items.append(treeListItemFromJson(entry.toObject()));
    }


    return items;
}

TreeItemListItem DataUtils::treeListItemFromJson(const QJsonObject &obj)
{
    TreeItemListItem item;

    item.name = obj.value(ApiKey::NAME).toString();
    item.path = obj.value(ApiKey::PATH).toString();
    item.extension = obj.value(ApiKey::EXTENSION).toString();

    const QString type = obj.value(ApiKey::TYPE).toString();

    if (type == QLatin1String("tree")) {
        item.type = TreeItem::Tree;
        return item;
    }

    if (type == QLatin1String("blob")) {
        item.type = TreeItem::Blob;

        if (obj.value(ApiKey::OBJECT).toObject().value(ApiKey::IS_BINARY).toBool()) {

            // image files
            QRegExp regex;
            regex.setPattern(".(jpg|png|gif|jpeg|ico|bmp)");

            if (regex.exactMatch(item.extension)) {
                item.fileType = File::Image;
                return item;
            }

            // else binary
            item.fileType = File::Binary;
            return item;
        }

        // SVG file
        QRegExp regex;
        regex.setPattern(".(svg)");

        if (regex.exactMatch(item.extension)) {
            item.fileType = File::Image;
            return item;
        }

        item.fileType = File::Text;
    }

    return item;
}

User *DataUtils::userFromJson(const QJsonObject &obj, User *user)
{
    if (user == nullptr)
        user = new User;

    user->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());
    user->setBio(obj.value(ApiKey::BIO).toString());
    user->setCompany(obj.value(ApiKey::COMPANY).toString());
    user->setFollowers(getTotalCount(obj.value(ApiKey::FOLLOWERS).toObject()));
    user->setFollowing(getTotalCount(obj.value(ApiKey::FOLLOWING).toObject()));
    user->setLocation(obj.value(ApiKey::LOCATION).toString());
    user->setLogin(obj.value(ApiKey::LOGIN).toString());
    user->setIsViewer(obj.value(ApiKey::IS_VIEWER).toBool());
    user->setName(obj.value(ApiKey::NAME).toString());
    user->setNodeId(obj.value(ApiKey::ID).toString());
    user->setOrganizations(getTotalCount(obj.value(ApiKey::ORGANIZATIONS).toObject()));
    user->setRepositories(getTotalCount(obj.value(ApiKey::REPOSITORIES).toObject()));
    user->setStarredRepositories(getTotalCount(obj.value(ApiKey::STARRED_REPOSITORIES).toObject()));
    user->setTwitterUsername(obj.value(ApiKey::TWITTER_USERNAME).toString());
    user->setViewerIsFollowing(obj.value(ApiKey::VIEWER_IS_FOLLOWING).toBool());
    user->setWebsiteUrl(obj.value(ApiKey::WEBSITE_URL).toString());

    // user status
    const QJsonObject status = obj.value(ApiKey::STATUS).toObject();

    UserStatus sta;
    sta.emoji = status.value(ApiKey::EMOJI).toString();
    sta.message = status.value(ApiKey::MESSAGE).toString();

    user ->setStatus(sta);

    return user;
}

UserListItem DataUtils::userListItemFromJson(const QJsonObject &obj)
{
    UserListItem item;

    item.avatarUrl = obj.value(ApiKey::AVATAR_URL).toString();
    item.login = obj.value(ApiKey::LOGIN).toString();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();

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

QString DataUtils::timeSpanText(const QDateTime &start, bool shortText)
{
    const QDateTime now = QDateTime::currentDateTimeUtc();

    if (start.addSecs(3600) > now) {
        const quint64 minutes = start.secsTo(now) / 60;
        return shortText ? QStringLiteral("%1m").arg(minutes) : QObject::tr("%n minute(s) ago", "", minutes);
    }

    if (start.addSecs(86400) > now) {
        const quint64 hours = start.secsTo(now) / 3600;
        return shortText ? QStringLiteral("%1h").arg(hours) : QObject::tr("%n hour(s) ago", "", hours);
    }

    if (start.addMonths(1) > now) {
        const quint64 days = start.daysTo(now);
        return shortText ? QStringLiteral("%1d").arg(days) : QObject::tr("%n day(s) ago", "", days);
    }

    if (start.addMonths(12) > now ) {
        const quint64 months = start.daysTo(now) / 30;
        return shortText ? QStringLiteral("%1mo").arg(months) : QObject::tr("%n month(s) ago", "", months);
    }

    const quint64 years = start.daysTo(now) / 365;
    return shortText ? QStringLiteral("%1y").arg(years) : QObject::tr("%n year(s) ago", "", years);
}

QJsonArray DataUtils::getNodes(const QJsonObject &obj)
{
    return obj.value(ApiKey::NODES).toArray();
}

quint32 DataUtils::getTotalCount(const QJsonObject &obj)
{
    return quint32(obj.value(ApiKey::TOTAL_COUNT).toInt());
}
