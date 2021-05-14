#include "issuesmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET REPOSITORY ISSUES
static const QString SAILHUB_QUERY_GET_REPOSITORY_ISSUES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            issues("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();


// GET USER ISSUES
static const QString SAILHUB_QUERY_GET_USER_ISSUES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            issues("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER CREATED ISSUES
static const QString SAILHUB_QUERY_GET_USER_ASSIGNED_ISSUES =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    user(login: $userLogin) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            issues("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    filterBy: {"
                       "                        assignee: $userLogin"
                       "                    }"
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER CREATED ISSUES
static const QString SAILHUB_QUERY_GET_USER_CREATED_ISSUES =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    user(login: $userLogin) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            issues("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    filterBy: {"
                       "                        createdBy: $userLogin"
                       "                    }"
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER MENTIONED ISSUES
static const QString SAILHUB_QUERY_GET_USER_MENTIONED_ISSUES =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    user(login: $userLogin) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            issues("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    filterBy: {"
                       "                        mentioned: $userLogin"
                       "                    }"
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER REPOSITORIES ISSUES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES_ISSUES =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [IssueState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    user(login: $userLogin) {"
                       "        ... on User {"
                       "            repositories(affiliations: [OWNER], first: 100) {"
                       "                nodes {"
                       "                    id"
                       "                    issues("
                       "                        first: $itemCount, "
                       "                        after: $itemCursor, "
                       "                        states: $states, "
                       "                        orderBy: { "
                       "                            direction: $orderDirection, "
                       "                            field: $orderField"
                       "                        } ) {"
                       "                        nodes {"
                       "                            %1"
                       "                        }"
                       "                        totalCount"
                       "                        %2"
                       "                    }"
                       "                }"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

IssuesModel::IssuesModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(UpdatedAtRole);
    setSortOrder(Qt::DescendingOrder);
}

void IssuesModel::addIssue(const IssueListItem &issue)
{
    beginInsertRows(QModelIndex(), m_issues.count(),  m_issues.count());
    m_issues.append(issue);
    endInsertRows();
}

void IssuesModel::addIssues(const QList<IssueListItem> &issues)
{
    beginInsertRows(QModelIndex(), m_issues.count(),  m_issues.count() + issues.count() - 1);
    m_issues.append(issues);
    endInsertRows();
}

void IssuesModel::setIssues(const QList<IssueListItem> &issues)
{
    beginResetModel();
    m_issues.clear();
    m_issues = issues;
    endResetModel();
}

void IssuesModel::parseUserReposIssues(const QJsonObject &obj)
{
    const QJsonArray repos = obj.value(ApiKey::USER).toObject()
            .value(ApiKey::REPOSITORIES).toObject()
            .value(ApiKey::NODES).toArray();

    // sort issues by created at
    QMultiMap<QDateTime, IssueListItem> sortedIssues;

    for (const auto &repo : repos) {
        const QList<IssueListItem> issues = DataUtils::issuesFromJson(repo.toObject().value(ApiKey::ISSUES).toObject());
        for (const auto &issue : issues) {
            sortedIssues.insertMulti(issue.createdAt, issue);
        }
    }


    QList<IssueListItem> issues;

    for (const auto &issue: sortedIssues.values()) {
        issues.prepend(issue);
    }

    //setPageInfo(DataUtils::pageInfoFromJson(issues, count));
    addIssues(issues);
    setLoading(false);
}

int IssuesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_issues.count();
}

QVariant IssuesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto issue = m_issues.at(index.row());

    switch (role) {
    case ClosedRole:
        return issue.closed;

    case CommentCountRole:
        return issue.commentCount;

    case CreatedAtRole:
        return issue.createdAt;

    case CreatedAtTimeSpanRole:
        return issue.createdAtTimeSpan;

    case NodeIdRole:
        return issue.nodeId;

    case NumberRole:
        return issue.number;

    case RepositoryRole:
        return issue.repository;

    case TitleRole:
        return issue.title;

    case SortRole:
        return sortRole();

    case StateRole:
        return issue.state;

    case UpdatedAtRole:
        return issue.updatedAt;

    case UpdatedAtTimeSpanRole:
        return issue.updatedAtTimeSpan;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> IssuesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ClosedRole]                   = "closed";
    roles[CommentCountRole]             = "commentCount";
    roles[CreatedAtRole]                = "createdAt";
    roles[CreatedAtTimeSpanRole]        = "createdAtTimeSpan";
    roles[NodeIdRole]                   = "nodeId";
    roles[NumberRole]                   = "number";
    roles[RepositoryRole]               = "repository";
    roles[TitleRole]                    = "title";
    roles[SortRole]                     = "sortRole";
    roles[StateRole]                    = "state";
    roles[UpdatedAtRole]                = "updatedAt";
    roles[UpdatedAtTimeSpanRole]        = "updatedAtTimeSpan";

    return roles;
}

void IssuesModel::clear()
{
    beginResetModel();
    m_issues.clear();
    endResetModel();
}

void IssuesModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject issues;

    switch (modelType()) {
    case Issue::Assigned:
    case Issue::CreatedBy:
    case Issue::Mentioned:
        issues = data.value(ApiKey::USER).toObject()
                     .value(ApiKey::ISSUES).toObject();
        break;

    // special case
    case Issue::Repos:
        parseUserReposIssues(data);
        return;

    default:
        issues = data.value(ApiKey::NODE).toObject()
                     .value(ApiKey::ISSUES).toObject();
        break;
    }

    const QJsonValue count = issues.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(issues, count));
    addIssues(DataUtils::issuesFromJson(issues));
    setLoading(false);
}

GraphQLQuery IssuesModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    // query
    switch (modelType()) {
    case Issue::Assigned:
        query.query = SAILHUB_QUERY_GET_USER_ASSIGNED_ISSUES;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case Issue::CreatedBy:
        query.query = SAILHUB_QUERY_GET_USER_CREATED_ISSUES;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case Issue::Mentioned:
        query.query = SAILHUB_QUERY_GET_USER_MENTIONED_ISSUES;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case Issue::Repo:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_ISSUES;
        break;

    case Issue::Repos:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES_ISSUES;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case Issue::User:
        query.query = SAILHUB_QUERY_GET_USER_ISSUES;
        break;

    default:
        break;
    }

    QJsonArray states;
    if (state() & Issue::StateOpen)
        states.append(QStringLiteral("OPEN"));
    if (state() & Issue::StateClosed)
        states.append(QStringLiteral("CLOSED"));
    query.variables.insert(QueryVar::STATES, states);

    return query;
}

QString IssuesModel::sortField() const
{
    switch (sortRole()) {
    case IssuesModel::CommentCountRole:
        return QStringLiteral("COMMENTS");

    case IssuesModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case IssuesModel::UpdatedAtRole:
        return QStringLiteral("UPDATED_AT");

    default:
        return QString();
    }
}
