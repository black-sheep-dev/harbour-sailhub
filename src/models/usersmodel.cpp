#include "usersmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET ISSUE ASSIGNEES
static const QString SAILHUB_QUERY_GET_ISSUE_ASSIGNEES =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Issue {"
                       "            id"
                       "            assignees(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET ISSUE PARTICIPANTS
static const QString SAILHUB_QUERY_GET_ISSUE_PARTICIPANTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Issue {"
                       "            id"
                       "            participants(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET ORGANIZATION MEMBERS
static const QString SAILHUB_QUERY_GET_ORGANIZATION_MEMBERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Organization {"
                       "            id"
                       "            membersWithRole(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET PULL REQEUST ASSIGNEES
static const QString SAILHUB_QUERY_GET_PULL_REQUEST_ASSIGNEES =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on PullRequest {"
                       "            id"
                       "            assignees(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();


// GET PULL REQEUST PARTICIPANTS
static const QString SAILHUB_QUERY_GET_PULL_REQUEST_PARTICIPANTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on PullRequest {"
                       "            id"
                       "            participants(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY CONTRIBUTORS
static const QString SAILHUB_QUERY_GET_REPOSITORY_ASSIGNABLE_USERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            assignableUsers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY CONTRIBUTORS
static const QString SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            mentionableUsers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY STARGAZERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            stargazers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY WATCHERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_WATCHERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            watchers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            followers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER FOLLOWING
static const QString SAILHUB_QUERY_GET_USER_FOLLOWING =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            following(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// SEARCH USER
static const QString SAILHUB_QUERY_SEARCH_USER =
        QStringLiteral("query searchUsers($queryString: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    search(query: $queryString, type: USER, first: $itemCount, after: $itemCursor) {"
                       "        %1"
                       "        userCount"
                       "        nodes {"
                       "            ... on User {"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PAGE_INFO, SAILHUB_QUERY_ITEM_USER_LIST_ITEM).simplified();

UsersModel::UsersModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(NameRole);
    setSortOrder(Qt::AscendingOrder);
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

void UsersModel::parseQueryResult(const QJsonObject &data)
{
    QJsonValue count;
    QJsonObject users;

    switch (modelType()) {
    case User::Assignable:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::ASSIGNABLE_USERS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Contributor:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::MENTIONABLE_USERS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Stargazer:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::STARGAZERS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Watcher:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::WATCHERS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Follower:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::FOLLOWERS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Following:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::FOLLOWING).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::OrganizationMember:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::MEMBERS_WITH_ROLE).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::IssueAssignee:
    case User::PullRequestAssignee:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::ASSIGNEES).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::IssueParticipant:
    case User::PullRequestParticipant:
        users = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::PARTICIPANTS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Search:
        users = data.value(ApiKey::SEARCH).toObject();
        count = users.value(ApiKey::USER_COUNT);
        break;

    default:
        break;
    }

    setPageInfo(DataUtils::pageInfoFromJson(users, count));

    // read user items
    QList<UserListItem> items;

    const QJsonArray nodes = users.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject user = node.toObject();
        if (user.isEmpty())
            continue;

        items.append(UserListItem(user));
    }

    addUsers(items);

    setLoading(false);
}

GraphQLQuery UsersModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case User::Follower:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWERS;
        break;

    case User::Following:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWING;
        break;

    case User::OrganizationMember:
        query.query = SAILHUB_QUERY_GET_ORGANIZATION_MEMBERS;
        break;

    case User::Assignable:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_ASSIGNABLE_USERS;
        break;

    case User::Contributor:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS;
        break;

    case User::Stargazer:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS;
        break;

    case User::Watcher:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_WATCHERS;
        break;

    case User::IssueAssignee:
        query.query = SAILHUB_QUERY_GET_ISSUE_ASSIGNEES;
        break;

    case User::IssueParticipant:
        query.query = SAILHUB_QUERY_GET_ISSUE_PARTICIPANTS;
        break;

    case User::PullRequestAssignee:
        query.query = SAILHUB_QUERY_GET_PULL_REQUEST_ASSIGNEES;
        break;

    case User::PullRequestParticipant:
        query.query = SAILHUB_QUERY_GET_PULL_REQUEST_PARTICIPANTS;
        break;

    case User::Search:
        query.query = SAILHUB_QUERY_SEARCH_USER;
        query.variables.insert(QueryVar::QUERY_STRING, searchPattern());
        break;

    default:
        break;
    }

    return query;
}
