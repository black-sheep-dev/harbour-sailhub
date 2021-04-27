#include "discussionsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET REPOSITORY ISSUES
static const QString SAILHUB_QUERY_GET_REPOSITORY_DISCUSSIONS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: DiscussionOrderField = UPDATED_AT, "
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
                       "            discussions("
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
                       "}").arg(SAILHUB_QUERY_ITEM_DISCUSSION_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

DiscussionsModel::DiscussionsModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(UpdatedAtRole);
    setSortOrder(Qt::DescendingOrder);
}

void DiscussionsModel::addDiscussion(const DiscussionListItem &discussion)
{
    beginInsertRows(QModelIndex(), m_discussions.count(),  m_discussions.count());
    m_discussions.append(discussion);
    endInsertRows();
}

void DiscussionsModel::addDiscussions(const QList<DiscussionListItem> &discussions)
{
    beginInsertRows(QModelIndex(), m_discussions.count(),  m_discussions.count() + discussions.count() - 1);
    m_discussions.append(discussions);
    endInsertRows();
}

void DiscussionsModel::setDiscussions(const QList<DiscussionListItem> &discussions)
{
    beginResetModel();
    m_discussions.clear();
    m_discussions = discussions;
    endResetModel();
}

int DiscussionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_discussions.count();
}

QVariant DiscussionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &discussion = m_discussions[index.row()];

    switch (role) {
    case AuthorAvatarRole:
        return discussion.authorAvatar;

    case AuthorLoginRole:
        return discussion.authorLogin;

    case CategoryRole:
        return discussion.category;

    case CommentCountRole:
        return discussion.commentCount;

    case CreatedAtRole:
        return discussion.createdAt;

    case CreatedAtTimeSpanRole:
        return discussion.createdAtTimeSpan;

    case EmojiRole:
        return discussion.emoji;

    case NodeIdRole:
        return discussion.nodeId;

    case TitleRole:
        return discussion.title;

    case UpdatedAtRole:
        return discussion.updatedAt;

    case UpdatedAtTimeSpanRole:
        return discussion.updatedAtTimeSpan;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DiscussionsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AuthorAvatarRole]         = "authorAvatar";
    roles[AuthorLoginRole]          = "authorLogin";
    roles[CategoryRole]             = "category";
    roles[CommentCountRole]         = "commentCount";
    roles[CreatedAtRole]            = "createdAt";
    roles[CreatedAtTimeSpanRole]    = "createdAtTimeSpan";
    roles[EmojiRole]                = "emoji";
    roles[NodeIdRole]               = "nodeId";
    roles[TitleRole]                = "title";
    roles[UpdatedAtRole]            = "updatedAt";
    roles[UpdatedAtTimeSpanRole]    = "updatedAtTimeSpan";

    return roles;
}

void DiscussionsModel::clear()
{
    beginResetModel();
    m_discussions.clear();
    endResetModel();
}

void DiscussionsModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject discussion = data.value(ApiKey::NODE).toObject()
                           .value(ApiKey::DISCUSSIONS).toObject();
    QJsonValue count = discussion.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(discussion, count));
    addDiscussions(DataUtils::discussionsFromJson(discussion));
    setLoading(false);
}

GraphQLQuery DiscussionsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();
    query.query = SAILHUB_QUERY_GET_REPOSITORY_DISCUSSIONS;

    return query;
}

QString DiscussionsModel::sortField() const
{
    switch (sortRole()) {
    case DiscussionsModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    case DiscussionsModel::UpdatedAtRole:
        return QStringLiteral("UPDATED_AT");

    default:
        return QString();
    }
}
