#include "releaseassetsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET RELEASE ASSETS
static const QString SAILHUB_QUERY_GET_RELEASE_ASSETS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Release {"
                       "            id"
                       "            releaseAssets("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor "
                       "                ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_RELEASE_ASSET_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

ReleaseAssetsModel::ReleaseAssetsModel(QObject *parent) :
    PaginationModel(parent)
{

}

void ReleaseAssetsModel::addReleaseAsset(const ReleaseAssetListItem &asset)
{
    beginInsertRows(QModelIndex(), m_assets.count(),  m_assets.count());
    m_assets.append(asset);
    endInsertRows();
}

void ReleaseAssetsModel::addReleaseAssets(const QList<ReleaseAssetListItem> &assets)
{
    beginInsertRows(QModelIndex(), m_assets.count(),  m_assets.count() + assets.count() - 1);
    m_assets.append(assets);
    endInsertRows();
}

void ReleaseAssetsModel::setReleaseAssets(const QList<ReleaseAssetListItem> &assets)
{
    beginResetModel();
    m_assets.clear();
    m_assets = assets;
    endResetModel();
}

int ReleaseAssetsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_assets.count();
}

QVariant ReleaseAssetsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &asset = m_assets[index.row()];

    switch (role) {
    case ContentTypeRole:
        return asset.contentType;

    case CreatedAtRole:
        return asset.createdAt;

    case DownloadCountRole:
        return asset.downloadCount;

    case DownloadUrlRole:
        return asset.downloadUrl;

    case NameRole:
        return asset.name;

    case SizeRole:
        return asset.size;

    case UpdatedAtRole:
        return asset.updatedAt;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReleaseAssetsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ContentTypeRole]      = "contentType";
    roles[CreatedAtRole]        = "createdAt";
    roles[DownloadCountRole]    = "downloadCount";
    roles[DownloadUrlRole]      = "downloadUrl";
    roles[NameRole]             = "name";
    roles[SizeRole]             = "size";
    roles[UpdatedAtRole]        = "updatedAt";

    return roles;
}

void ReleaseAssetsModel::clear()
{
    beginResetModel();
    m_assets.clear();
    endResetModel();
}

void ReleaseAssetsModel::parseQueryResult(const QJsonObject &data)
{
    const QJsonObject assets = data.value(ApiKey::NODE).toObject()
                                   .value(ApiKey::RELEASE_ASSETS).toObject();

    const QJsonValue count = assets.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(assets, count));

    // read release asset items
    QList<ReleaseAssetListItem> items;

    const QJsonArray nodes = assets.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject asset = node.toObject();
        if (asset.isEmpty())
            continue;

        items.append(ReleaseAssetListItem(asset));
    }

    addReleaseAssets(items);

    setLoading(false);
}

GraphQLQuery ReleaseAssetsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();
    query.query = SAILHUB_QUERY_GET_RELEASE_ASSETS;

    return query;
}
