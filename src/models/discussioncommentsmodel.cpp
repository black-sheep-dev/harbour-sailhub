#include "discussioncommentsmodel.h"


#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

static const QString SAILHUB_QUERY_GET_DISCUSSION_COMMENTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Discussion {"
                       "            id"
                       "            comments("
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
                       "    "
                       "}").arg(SAILHUB_QUERY_ITEM_DISCUSSION_COMMENT, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

static const QString SAILHUB_QUERY_GET_DISCUSSION_COMMENT_REPLIES =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on DiscussionComment {"
                       "            id"
                       "            replies("
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
                       "    "
                       "}").arg(SAILHUB_QUERY_ITEM_DISCUSSION_COMMENT, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

DiscussionCommentsModel::DiscussionCommentsModel(QObject *parent) :
    PaginationModel(parent)
{

}

DiscussionComment *DiscussionCommentsModel::commentAt(const int index)
{
    if (index < 0 || index > (m_comments.count() - 1))
        return nullptr;

    return m_comments.at(index);
}

int DiscussionCommentsModel::count()
{
    return m_comments.count();
}

void DiscussionCommentsModel::addComment(DiscussionComment *comment)
{
    if (comment == nullptr)
        return;

    const int index = m_comments.count() - 1;

    comment->setParent(this);
    beginInsertRows(QModelIndex(), m_comments.count(), m_comments.count());
    m_comments.append(comment);
    endInsertRows();

    if (index < 0)
        return;

    emit commentsAdded(index, 1);
}

void DiscussionCommentsModel::addComments(const QList<DiscussionComment *> &comments)
{
    QList<DiscussionComment *> items;
    for (auto comment : comments) {
        if (comment == nullptr)
            continue;

        comment->setParent(this);
        items.append(comment);
    }

    int index = m_comments.count() - 1;

    beginInsertRows(QModelIndex(), m_comments.count(), m_comments.count() + items.count() - 1);
    m_comments.append(items);
    endInsertRows();

    if (index < 0)
        index = 0;

    emit commentsAdded(index, items.count());
}

void DiscussionCommentsModel::setComments(const QList<DiscussionComment *> &comments)
{
    beginResetModel();
    if (!m_comments.isEmpty()) {
        qDeleteAll(m_comments.begin(), m_comments.end());
        m_comments.clear();
    }

    for (auto comment : comments) {
        if (comment == nullptr)
            continue;

        comment->setParent(this);
        m_comments.append(comment);
    }
    endResetModel();
}

int DiscussionCommentsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_comments.count();
}

QVariant DiscussionCommentsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto comment = m_comments.at(index.row());

    switch (role) {
    case AuthorAvatarRole:
        return comment->author()->avatarUrl();

    case AuthorLoginRole:
        return comment->author()->login();

    case BodyRole:
        return comment->body();

    case CreatedAtTimeSpanRole:
        return comment->createdAtTimeSpan();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DiscussionCommentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AuthorAvatarRole]         = "authorAvatar";
    roles[AuthorLoginRole]          = "authorLogin";
    roles[BodyRole]                 = "body";
    roles[CreatedAtTimeSpanRole]    = "createdAtTimeSpan";

    return roles;
}

void DiscussionCommentsModel::clear()
{
    beginResetModel();
    if (!m_comments.isEmpty())
        qDeleteAll(m_comments.begin(), m_comments.end());

    m_comments.clear();
    endResetModel();
}

void DiscussionCommentsModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject comments;

    switch (modelType()) {
    case DiscussionComment::Comment:
        comments = data.value(ApiKey::NODE).toObject().value(ApiKey::COMMENTS).toObject();
        break;

    case DiscussionComment::Reply:
        comments = data.value(ApiKey::NODE).toObject().value(ApiKey::REPLIES).toObject();
        break;

    default:
        break;
    }

    const QJsonValue count = comments.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(comments, count));
    addComments(DataUtils::discussionCommentsFromJson(comments));
    setLoading(false);
}

GraphQLQuery DiscussionCommentsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case DiscussionComment::Comment:
        query.query = SAILHUB_QUERY_GET_DISCUSSION_COMMENTS;
        break;

    case DiscussionComment::Reply:
        query.query = SAILHUB_QUERY_GET_DISCUSSION_COMMENT_REPLIES;
        break;

    default:
        break;
    }

    return query;
}
