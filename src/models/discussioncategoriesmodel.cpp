#include "discussioncategoriesmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET REPOSITORY DISCUSSION CATEGORIES
static const QString SAILHUB_QUERY_GET_REPOSITORY_DISCUSSION_CATEGORIES =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            discussionCategories("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor "
                       "                    ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_DISCUSSION_CATEGORY_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

DiscussionCategoriesModel::DiscussionCategoriesModel(QObject *parent) :
    PaginationModel(parent)
{

}

void DiscussionCategoriesModel::addCategory(const DiscussionCategoryListItem &category)
{
    beginInsertRows(QModelIndex(), m_categories.count(),  m_categories.count());
    m_categories.append(category);
    endInsertRows();
}

void DiscussionCategoriesModel::addCategories(const QList<DiscussionCategoryListItem> &categories)
{
    beginInsertRows(QModelIndex(), m_categories.count(),  m_categories.count() + categories.count() - 1);
    m_categories.append(categories);
    endInsertRows();
}

void DiscussionCategoriesModel::setCategories(const QList<DiscussionCategoryListItem> &categories)
{
    beginResetModel();
    m_categories.clear();
    m_categories = categories;
    endResetModel();
}

int DiscussionCategoriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_categories.count();
}

QVariant DiscussionCategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &category = m_categories[index.row()];

    switch (role) {
    case DescriptionRole:
        return category.description;

    case EmojiRole:
        return category.emoji;

    case NameRole:
        return category.name;

    case NodeIdRole:
        return category.nodeId;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DiscussionCategoriesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DescriptionRole]      = "description";
    roles[EmojiRole]            = "emoji";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";

    return roles;
}

void DiscussionCategoriesModel::clear()
{
    beginResetModel();
    m_categories.clear();
    endResetModel();
}

void DiscussionCategoriesModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject categories = data.value(ApiKey::NODE).toObject()
                           .value(ApiKey::DISCUSSION_CATEGORIES).toObject();
    QJsonValue count = categories.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(categories, count));
    addCategories(DataUtils::discussionCategoriesFromJson(categories));
    setLoading(false);
}

GraphQLQuery DiscussionCategoriesModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();
    query.query = SAILHUB_QUERY_GET_REPOSITORY_DISCUSSION_CATEGORIES;

    return query;
}
