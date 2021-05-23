#include "gistsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET USER GISTS
static const QString SAILHUB_QUERY_GET_USER_GISTS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: GistOrderField = UPDATED_AT, "
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
                       "            gists("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    privacy: ALL, "
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
                       "}").arg(SAILHUB_QUERY_ITEM_GIST_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

GistsModel::GistsModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(UpdatedAtRole);
    setSortOrder(Qt::DescendingOrder);
}

void GistsModel::addGist(const GistListItem &gist)
{
    beginInsertRows(QModelIndex(), m_gists.count(),  m_gists.count());
    m_gists.append(gist);
    endInsertRows();
}

void GistsModel::addGists(const QList<GistListItem> &gists)
{
    beginInsertRows(QModelIndex(), m_gists.count(),  m_gists.count() + gists.count() - 1);
    m_gists.append(gists);
    endInsertRows();
}

void GistsModel::setGists(const QList<GistListItem> &gists)
{
    beginResetModel();
    m_gists.clear();
    m_gists = gists;
    endResetModel();
}

int GistsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_gists.count();
}

QVariant GistsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &gist = m_gists[index.row()];

    switch (role) {
    case CommentCountRole:
        return gist.commentCount;

    case CreatedAtRole:
        return gist.createdAt;

    case DescriptionRole:
        return gist.description;

    case FileCountRole:
        return gist.fileCount;

    case ForkCountRole:
        return gist.forkCount;

    case IsPublicRole:
        return gist.isPublic;

    case NodeIdRole:
        return gist.nodeId;

    case OwnerLoginRole:
        return gist.ownerLogin;

    case OwnerAvatarRole:
        return gist.ownerAvatar;

    case PushedAtRole:
        return gist.pushedAt;

    case StargazerCountRole:
        return gist.stargazerCount;

    case UpdatedAtRole:
        return gist.updatedAt;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GistsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CommentCountRole]     = "commentCount";
    roles[CreatedAtRole]        = "createdAt";
    roles[DescriptionRole]      = "description";
    roles[FileCountRole]        = "fileCount";
    roles[ForkCountRole]        = "forkCount";
    roles[IsPublicRole]         = "isPublic";
    roles[NodeIdRole]           = "nodeId";
    roles[OwnerLoginRole]       = "ownerLogin";
    roles[OwnerAvatarRole]      = "ownerAvatar";
    roles[PushedAtRole]         = "pushedAt";
    roles[StargazerCountRole]   = "stargazerCount";
    roles[UpdatedAtRole]        = "updatedAt";

    return roles;
}

void GistsModel::clear()
{
    beginResetModel();
    m_gists.clear();
    endResetModel();
}

void GistsModel::parseQueryResult(const QJsonObject &data)
{
    const QJsonObject gists = data.value(ApiKey::NODE).toObject()
            .value(ApiKey::GISTS).toObject();

    const QJsonValue count = gists.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(gists, count));

    // read gist items
    QList<GistListItem> items;

    const QJsonArray nodes = gists.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject gist = node.toObject();
        if (gist.isEmpty())
            continue;

        items.append(GistListItem(gist));
    }

    addGists(items);

    setLoading(false);
}

GraphQLQuery GistsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();
    query.variables.insert(QueryVar::NODE_ID, identifier());

    query.query = SAILHUB_QUERY_GET_USER_GISTS;

    return query;
}

QString GistsModel::sortField() const
{
    switch (sortRole()) {
    case GistsModel::PushedAtRole:
        return QStringLiteral("PUSHED_AT");

    case GistsModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case GistsModel::UpdatedAtRole:
        return QStringLiteral("UPDATED_AT");

    default:
        return QString();
    }
}
