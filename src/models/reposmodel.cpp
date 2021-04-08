#include "reposmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET ORGANIZATION REPOSITORIES
static const QString SAILHUB_QUERY_GET_ORGANIZATION_REPOSITORIES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: RepositoryOrderField = NAME, "
                       "        $orderDirection: OrderDirection = ASC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Organization {"
                       "            login"
                       "            repositories("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    orderBy: {"
                       "                        direction: $orderDirection"
                       "                        field: $orderField"
                       "                    }) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY FORKS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FORKS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: RepositoryOrderField = NAME, "
                       "        $orderDirection: OrderDirection = ASC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            forks("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor,"
                       "                    orderBy: {"
                       "                        direction: $orderDirection"
                       "                        field: $orderField"
                       "                    }) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: RepositoryOrderField = NAME, "
                       "        $orderDirection: OrderDirection = ASC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            login"
                       "            repositories("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    orderBy: {"
                       "                        direction: $orderDirection"
                       "                        field: $orderField"
                       "                    }) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER STARRED REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES_STARRED =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: RepositoryOrderField = NAME, "
                       "        $orderDirection: OrderDirection = ASC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            login"
                       "            starredRepositories("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor,"
                       "                    orderBy: {"
                       "                        direction: $orderDirection"
                       "                        field: $orderField"
                       "                    }) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// SEARCH USER
static const QString SAILHUB_QUERY_SEARCH_REPOSITORY =
        QStringLiteral("query searchRepos($queryString: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    search(query: $queryString, type: REPOSITORY, first: $itemCount, after: $itemCursor) {"
                       "        %1"
                       "        repositoryCount"
                       "        nodes {"
                       "            ... on Repository {"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PAGE_INFO, SAILHUB_QUERY_ITEM_REPO_LIST_ITEM).simplified();

ReposModel::ReposModel(QObject *parent) :
    PaginationModel(parent)
{

}

void ReposModel::addRepo(const RepoListItem &repo)
{
    beginInsertRows(QModelIndex(), m_repos.count(), m_repos.count());
    m_repos.append(repo);
    endInsertRows();
}

void ReposModel::addRepos(const QList<RepoListItem> &repos)
{
    beginInsertRows(QModelIndex(), m_repos.count(), m_repos.count() + repos.count() - 1);
    m_repos.append(repos);
    endInsertRows();
}

void ReposModel::setRepos(const QList<RepoListItem> &repos)
{
    beginResetModel();
    m_repos.clear();
    m_repos = repos;
    endResetModel();
}

QVariant ReposModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto repo = m_repos.at(index.row());

    switch (role) {
    case CreatedAtRole:
        return repo.createdAt;

    case DescriptionRole:
        return repo.description;

    case IsPrivateRole:
        return repo.isPrivate;

    case LanguageColorRole:
        return repo.language.color;

    case LanguageNameRole:
        return repo.language.name;

    case NameRole:
        return repo.name;

    case NodeIdRole:
        return repo.nodeId;

    case OwnerRole:
        return repo.owner;

    case PushedAtRole:
        return repo.pushedAt;

    case SortRole:
        return sortRole();

    case StargazerCountRole:
        return repo.stargazerCount;

    case UpdatedAtRole:
        return repo.updatedAt;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReposModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CreatedAtRole]        = "createdAt";
    roles[DescriptionRole]      = "description";
    roles[IsPrivateRole]        = "isPrivate";
    //roles[LanguageRole]         = "language";
    roles[LanguageColorRole]    = "languageColor";
    roles[LanguageNameRole]     = "languageName";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";
    roles[OwnerRole]            = "owner";
    roles[PushedAtRole]         = "pushedAt";
    roles[SortRole]             = "sortRole";
    roles[StargazerCountRole]   = "stargazerCount";
    roles[UpdatedAtRole]        = "updatedAt";


    return roles;
}

int ReposModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_repos.count();
}

void ReposModel::clear()
{
    beginResetModel();
    m_repos.clear();
    endResetModel();
}

void ReposModel::parseQueryResult(const QJsonObject &data)
{
    // get identifier and repos
    QJsonValue count;
    QJsonObject repos;

    switch (modelType()) {
    case Repo::User:
    case Repo::Organization:
        repos = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::REPOSITORIES).toObject();
        count = repos.value(ApiKey::TOTAL_COUNT);
        break;

    case Repo::Fork:
        repos = data.value(ApiKey::NODE).toObject()
                    .value(ApiKey::FORKS).toObject();
        count = repos.value(ApiKey::TOTAL_COUNT);
        break;

    case Repo::Search:
        repos = data.value(ApiKey::SEARCH).toObject();
        count = repos.value(ApiKey::REPOSITORY_COUNT);
        break;

    case Repo::Starred:
        repos = data.value(ApiKey::NODE).toObject()
                   .value(ApiKey::STARRED_REPOSITORIES).toObject();
        count = repos.value(ApiKey::REPOSITORY_COUNT);
        break;

    default:
        return;
    }

    setPageInfo(DataUtils::pageInfoFromJson(repos, count));
    addRepos(DataUtils::reposFromJson(repos));
    setLoading(false);
}

GraphQLQuery ReposModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case Repo::User:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES;
        break;

    case Repo::Organization:
        query.query = SAILHUB_QUERY_GET_ORGANIZATION_REPOSITORIES;
        break;

    case Repo::Fork:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_FORKS;
        break;

    case Repo::Starred:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES_STARRED;
        break;

    case Repo::Search:
        query.query = SAILHUB_QUERY_SEARCH_REPOSITORY;
        query.variables.insert(QueryVar::QUERY_STRING, searchPattern());
        break;

    default:
        break;
    }

    return query;
}

QString ReposModel::sortField() const
{
    switch (sortRole()) {
    case ReposModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case ReposModel::NameRole:
        return QStringLiteral("NAME");

    case ReposModel::PushedAtRole:
        return QStringLiteral("PUSHED_AT");

    case ReposModel::UpdatedAtRole:
        return QStringLiteral("UPDATED_AT");

    case ReposModel::StargazerCountRole:
        return QStringLiteral("STARGAZERS");

    default:
        return QString();
    }
}
