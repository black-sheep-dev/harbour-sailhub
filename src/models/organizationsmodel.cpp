#include "organizationsmodel.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET USER ORGANIZATIONS
static const QString SAILHUB_QUERY_GET_USER_ORGANIZATIONS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            organizations(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ORGANIZATION_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// SEARCH ORGANIZATION
static const QString SAILHUB_QUERY_SEARCH_ORGANIZATION =
        QStringLiteral("query searchOrgs($queryString: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    search(query: $queryString, type: USER, first: $itemCount, after: $itemCursor) {"
                       "        %1"
                       "        userCount"
                       "        nodes {"
                       "            ... on Organization {"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PAGE_INFO, SAILHUB_QUERY_ITEM_ORGANIZATION_LIST_ITEM).simplified();

OrganizationsModel::OrganizationsModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(NameRole);
    setSortOrder(Qt::AscendingOrder);
}

void OrganizationsModel::addOrganization(const OrganizationListItem &organization)
{
    beginInsertRows(QModelIndex(), m_organizations.count(), m_organizations.count());
    m_organizations.append(organization);
    endInsertRows();
}

void OrganizationsModel::addOrganizations(const QList<OrganizationListItem> &organizations)
{
    beginInsertRows(QModelIndex(), m_organizations.count(), m_organizations.count() + organizations.count() - 1);
    m_organizations.append(organizations);
    endInsertRows();
}

void OrganizationsModel::setOrganizations(const QList<OrganizationListItem> &organizations)
{
    beginResetModel();
    m_organizations.clear();
    m_organizations = organizations;
    endResetModel();
}

QVariant OrganizationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto organization = m_organizations.at(index.row());

    switch (role) {
    case NameRole:
        return organization.name;

    case AvatarUrlRole:
        return organization.avatarUrl;

    case DescriptionRole:
        return organization.description;

    case LoginRole:
        return organization.login;

    case NodeIdRole:
        return organization.nodeId;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> OrganizationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AvatarUrlRole]        = "avatarUrl";
    roles[DescriptionRole]      = "description";
    roles[LoginRole]            = "login";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";

    return roles;
}

int OrganizationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_organizations.count();
}

void OrganizationsModel::clear()
{
    beginResetModel();
    m_organizations.clear();
    endResetModel();
}

void OrganizationsModel::parseQueryResult(const QJsonObject &data)
{
    QJsonValue count;
    QJsonObject organizations;

    switch (modelType()) {
    case Organization::IsMember:
        organizations = data.value(ApiKey::NODE).toObject()
                            .value(ApiKey::ORGANIZATIONS).toObject();
        count = data.value(ApiKey::TOTAL_COUNT);
        break;

    case Organization::Search:
        organizations = data.value(ApiKey::SEARCH).toObject();
        count = organizations.value(ApiKey::USER_COUNT);
        break;

    default:
        break;
    }

    setPageInfo(DataUtils::pageInfoFromJson(organizations, count));
    addOrganizations(DataUtils::organizationsFromJson(organizations));
    setLoading(false);
}

GraphQLQuery OrganizationsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case Organization::IsMember:
        query.query = SAILHUB_QUERY_GET_USER_ORGANIZATIONS;
        break;

    case Organization::Search:
        query.query = SAILHUB_QUERY_SEARCH_ORGANIZATION;
        query.variables.insert(QueryVar::QUERY_STRING, searchPattern());
        break;

    default:
        break;
    }

    return query;
}
