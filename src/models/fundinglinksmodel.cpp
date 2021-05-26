#include "fundinglinksmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"

// GET REPOSITORY FUNDING LINKS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FUNDING_LINKS =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            fundingLinks {"
                       "                platform"
                       "                url"
                       "            }"
                       "        }"
                       "    }"
                       "}").simplified();

FundingLinksModel::FundingLinksModel(QObject *parent) :
    BaseModel(parent)
{

}

void FundingLinksModel::setFundingLinks(const QList<FundingLinkListItem> &links)
{
    beginResetModel();
    m_links.clear();
    m_links = links;
    endResetModel();
}

int FundingLinksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_links.count();
}

QVariant FundingLinksModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &link = m_links[index.row()];

    switch (role) {
    case NameRole:
        return link.name;

    case PlatformRole:
        return link.platform;

    case UrlRole:
        return link.url;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FundingLinksModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole]         = "name";
    roles[PlatformRole]     = "platform";
    roles[UrlRole]          = "url";

    return roles;
}

void FundingLinksModel::clear()
{
    beginResetModel();
    m_links.clear();
    endResetModel();
}

void FundingLinksModel::parseQueryResult(const QJsonObject &data)
{
    const QJsonArray links = data.value(ApiKey::NODE).toObject()
            .value(ApiKey::FUNDING_LINKS).toArray();

    QList<FundingLinkListItem> items;

    for (const auto &value : links) {
        const QJsonObject obj = value.toObject();

        items.append(FundingLinkListItem(obj));
    }

    setFundingLinks(items);

    setLoading(false);
}

GraphQLQuery FundingLinksModel::query() const
{
    GraphQLQuery query;
    query.variables.insert(QueryVar::NODE_ID, identifier());

    query.query = SAILHUB_QUERY_GET_REPOSITORY_FUNDING_LINKS;

    return query;
}
