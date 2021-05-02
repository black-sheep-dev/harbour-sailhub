#include "pullrequestsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET REPOSITORY PULL REQUESTS
static const QString SAILHUB_QUERY_GET_REPOSITORY_PULL_REQUESTS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $states: [PullRequestState!]!, "
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
                       "            pullRequests("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER PULL REQUESTS
static const QString SAILHUB_QUERY_GET_USER_PULL_REQUESTS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $states: [PullRequestState!]!, "
                       "        $orderField: IssueOrderField = UPDATED_AT, "
                       "        $orderDirection: OrderDirection = DESC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            id"
                       "            pullRequests("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    states: $states, "
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField "
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER ASSIGNED PULL REQUESTS
static const QString SAILHUB_QUERY_GET_USER_ASSIGNED_PULL_REQUEST =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [PullRequestState!]!, "
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
                       "            pullRequests("
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
                       "}").arg(SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER CREATED PULL REQUESTS
static const QString SAILHUB_QUERY_GET_USER_CREATED_PULL_REQUEST =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [PullRequestState!]!, "
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
                       "            pullRequests("
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
                       "}").arg(SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER MENTIONED PULL REQUESTS
static const QString SAILHUB_QUERY_GET_USER_MENTIONED_PULL_REQUEST =
        QStringLiteral("query("
                       "        $userLogin: String!, "
                       "        $states: [PullRequestState!]!, "
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
                       "            pullRequests("
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
                       "}").arg(SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();


PullRequestsModel::PullRequestsModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(UpdatedAtRole);
    setSortOrder(Qt::DescendingOrder);
}

void PullRequestsModel::addPullRequest(const PullRequestListItem &repo)
{
    beginInsertRows(QModelIndex(), m_pullRequests.count(), m_pullRequests.count());
    m_pullRequests.append(repo);
    endInsertRows();
}

void PullRequestsModel::addPullRequests(const QList<PullRequestListItem> &repos)
{
    beginInsertRows(QModelIndex(), m_pullRequests.count(), m_pullRequests.count() + repos.count() - 1);
    m_pullRequests.append(repos);
    endInsertRows();
}

void PullRequestsModel::setPullRequests(const QList<PullRequestListItem> &repos)
{
    beginResetModel();
    m_pullRequests.clear();
    m_pullRequests = repos;
    endResetModel();
}

int PullRequestsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_pullRequests.count();
}

QVariant PullRequestsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto pr = m_pullRequests.at(index.row());

    switch (role) {
    case CommentCountRole:
        return pr.commentCount;

    case CreatedAtRole:
        return pr.createdAt;

    case CreatedAtTimeSpanRole:
        return pr.createdAtTimeSpan;

    case NodeIdRole:
        return pr.nodeId;

    case NumberRole:
        return pr.number;

    case RepositoryRole:
        return pr.repository;

    case SortRole:
        return sortRole();

    case StateRole:
        return pr.state;

    case TitleRole:
        return pr.title;

    case UpdatedAtRole:
        return pr.createdAt;

    case UpdatedAtTimeSpanRole:
        return pr.updatedAtTimeSpan;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PullRequestsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CommentCountRole]         = "commentCount";
    roles[CreatedAtRole]            = "createdAt";
    roles[CreatedAtTimeSpanRole]    = "createdAtTimeSpan";
    roles[NodeIdRole]               = "nodeId";
    roles[NumberRole]               = "number";
    roles[RepositoryRole]           = "repository";
    roles[SortRole]                 = "sortRole";
    roles[StateRole]                = "state";
    roles[TitleRole]                = "title";
    roles[UpdatedAtRole]            = "updatedAt";
    roles[UpdatedAtTimeSpanRole]    = "updatedAtTimeSpan";

    return roles;
}

void PullRequestsModel::clear()
{
    beginResetModel();
    m_pullRequests.clear();
    endResetModel();
}

void PullRequestsModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject prs;

    switch (modelType()) {
    case Issue::Assigned:
    case Issue::CreatedBy:
    case Issue::Mentioned:
        prs = data.value(ApiKey::USER).toObject()
                     .value(ApiKey::PULL_REQUESTS).toObject();
        break;

    default:
        prs = data.value(ApiKey::NODE).toObject()
                     .value(ApiKey::PULL_REQUESTS).toObject();
        break;
    }

    const QJsonValue count = prs.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(prs, count));
    addPullRequests(DataUtils::pullRequestsFromJson(prs));
    setLoading(false);

}

GraphQLQuery PullRequestsModel::query() const
{
    GraphQLQuery query;

    // variables
    query.variables = defaultQueryVariables();

    // query
    switch (modelType()) {
    case PullRequest::Repo:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_PULL_REQUESTS;
        break;

    case PullRequest::User:
        query.query = SAILHUB_QUERY_GET_USER_PULL_REQUESTS;
        break;

    case PullRequest::Assigned:
        query.query = SAILHUB_QUERY_GET_USER_ASSIGNED_PULL_REQUEST;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case PullRequest::CreatedBy:
        query.query = SAILHUB_QUERY_GET_USER_CREATED_PULL_REQUEST;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    case PullRequest::Mentioned:
        query.query = SAILHUB_QUERY_GET_USER_MENTIONED_PULL_REQUEST;
        query.variables.insert(QueryVar::USER_LOGIN, identifier());
        break;

    default:
        break;
    }


    QJsonArray states;
    if (state() & PullRequest::StateOpen)
        states.append(QStringLiteral("OPEN"));
    if (state() & PullRequest::StateClosed)
        states.append(QStringLiteral("CLOSED"));
    if (state() & PullRequest::StateMerged)
        states.append(QStringLiteral("MERGED"));
    query.variables.insert(QueryVar::STATES, states);

    return query;
}

QString PullRequestsModel::sortField() const
{
    switch (sortRole()) {
    case PullRequestsModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case PullRequestsModel::UpdatedAtRole:
        return QStringLiteral("UPDATED_AT");

    default:
        return QString();
    }
}
