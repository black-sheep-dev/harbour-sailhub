#include "releasesmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET REPOSITORY ISSUES
static const QString SAILHUB_QUERY_GET_REPOSITORY_RELEASES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: ReleaseOrderField = CREATED_AT, "
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
                       "            releases("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
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
                       "}").arg(SAILHUB_QUERY_ITEM_RELEASE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

ReleasesModel::ReleasesModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(CreatedAtRole);
    setSortOrder(Qt::DescendingOrder);
}

void ReleasesModel::addRelease(const ReleaseListItem &release)
{
    beginInsertRows(QModelIndex(), m_releases.count(),  m_releases.count());
    m_releases.append(release);
    endInsertRows();
}

void ReleasesModel::addReleases(const QList<ReleaseListItem> &releases)
{
    beginInsertRows(QModelIndex(), m_releases.count(),  m_releases.count() + releases.count() - 1);
    m_releases.append(releases);
    endInsertRows();
}

void ReleasesModel::setReleases(const QList<ReleaseListItem> &releases)
{
    beginResetModel();
    m_releases.clear();
    m_releases = releases;
    endResetModel();
}

int ReleasesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_releases.count();
}

QVariant ReleasesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &release = m_releases[index.row()];

    switch (role) {
    case CreatedAtRole:
        return release.createdAt;

    case CreatedAtTimeSpanRole:
        return release.createdAtTimeSpan;

    case IsDraftRole:
        return release.isDraft;

    case IsLatestRole:
        return release.isLatest;

    case IsPrereleaseRole:
        return release.isPrerelease;

    case NameRole:
        return release.name;

    case NodeIdRole:
        return release.nodeId;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReleasesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CreatedAtRole]            = "createdAt";
    roles[CreatedAtTimeSpanRole]    = "createdAtTimeSpan";
    roles[IsDraftRole]              = "isDraft";
    roles[IsLatestRole]             = "isLatest";
    roles[IsPrereleaseRole]         = "isPrerelease";
    roles[NameRole]                 = "name";
    roles[NodeIdRole]               = "nodeId";

    return roles;
}

void ReleasesModel::clear()
{
    beginResetModel();
    m_releases.clear();
    endResetModel();
}

void ReleasesModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject releases = data.value(ApiKey::NODE).toObject()
                           .value(ApiKey::RELEASES).toObject();
    QJsonValue count = releases.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(releases, count));
    addReleases(DataUtils::releasesFromJson(releases));
    setLoading(false);
}

GraphQLQuery ReleasesModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();
    query.query = SAILHUB_QUERY_GET_REPOSITORY_RELEASES;

    return query;
}

QString ReleasesModel::sortField() const
{
    switch (sortRole()) {
    case ReleasesModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case ReleasesModel::NameRole:
        return QStringLiteral("NAME");

    default:
        return QString();
    }
}
