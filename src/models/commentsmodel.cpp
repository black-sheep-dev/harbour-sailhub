#include "commentsmodel.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

static const QString SAILHUB_QUERY_GET_ISSUE_COMMENTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Issue {"
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
                       "}").arg(SAILHUB_QUERY_ITEM_COMMENT, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

static const QString SAILHUB_QUERY_GET_PULL_REQUEST_COMMENTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on PullRequest {"
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
                       "}").arg(SAILHUB_QUERY_ITEM_COMMENT, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

CommentsModel::CommentsModel(QObject *parent) :
    PaginationModel(parent)
{

}

Comment *CommentsModel::commentAt(const int index)
{
    if (index < 0 || index > (m_comments.count() - 1))
        return nullptr;

    return m_comments.at(index);
}

void CommentsModel::deleteComment(const int index)
{
    if (index < 0 || index > (m_comments.count() - 1))
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_comments.takeAt(index)->deleteLater();
    endRemoveRows();
}

void CommentsModel::addComment(Comment *comment)
{
    if (comment == nullptr)
        return;

    comment->setParent(this);
    beginInsertRows(QModelIndex(), m_comments.count(), m_comments.count());
    m_comments.append(comment);
    endInsertRows();
}

void CommentsModel::addComments(const QList<Comment *> &comments)
{
    QList<Comment *> items;
    for (auto comment : comments) {
        if (comment == nullptr)
            continue;

        comment->setParent(this);
        items.append(comment);
    }

    beginInsertRows(QModelIndex(), m_comments.count(), m_comments.count() + items.count() - 1);
    m_comments.append(items);
    endInsertRows();
}

void CommentsModel::setComments(const QList<Comment *> &comments)
{
    beginResetModel();
    if (!m_comments.isEmpty()) {
        qDeleteAll(m_comments.begin(), m_comments.end());
        m_comments.clear();
    }

    for (auto *comment : comments) {
        if (comment == nullptr)
            continue;

        comment->setParent(this);
        m_comments.append(comment);
    }
    endResetModel();
}

int CommentsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_comments.count();
}

QVariant CommentsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto comment = m_comments.at(index.row());

    switch (role) {
    case AuthorIdRole:
        return comment->author()->nodeId();

    case AuthorLoginRole:
        return comment->author()->login();

    case AuthorAvatarUrlRole:
        return comment->author()->avatarUrl();

    case BodyRole:
        return comment->body();

    case BodyExcerptRole:
        return comment->bodyExcerpt();

    case CreatedAtRole:
        return comment->createdAt();

    case CreatedAtTimeSpanRole:
        return comment->createdAtTimeSpan();

    case EditedRole:
        return comment->edited();

    case LastEditAtRole:
        return comment->lastEditAt();

    case NodeIdRole:
        return comment->nodeId();

    case ViewerAbilitiesRole:
        return comment->viewerAbilities();

    case ViewerDidAuthorRole:
        return comment->viewerDidAuthor();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CommentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AuthorIdRole]             = "authorId";
    roles[AuthorAvatarUrlRole]      = "authorAvatarUrl";
    roles[AuthorLoginRole]          = "authorLogin";
    roles[BodyRole]                 = "body";
    roles[BodyExcerptRole]          = "bodyExcerpt";
    roles[CreatedAtRole]            = "createdAt";
    roles[CreatedAtTimeSpanRole]    = "createdAtTimeSpan";
    roles[EditedRole]               = "edited";
    roles[LastEditAtRole]           = "lastEditAt";
    roles[NodeIdRole]               = "nodeId";
    roles[ViewerAbilitiesRole]      = "viewerAbilities";
    roles[ViewerDidAuthorRole]      = "viewerDidAuthor";

    return roles;
}

void CommentsModel::clear()
{
    beginResetModel();
    qDeleteAll(m_comments.begin(), m_comments.end());
    m_comments.clear();
    endResetModel();
}

void CommentsModel::parseQueryResult(const QJsonObject &data)
{
    const QJsonObject comments = data.value(ApiKey::NODE).toObject()
                                     .value(ApiKey::COMMENTS).toObject();
    const QJsonValue count = comments.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(comments, count));
    addComments(DataUtils::commentsFromJson(comments));
    setLoading(false);
}

GraphQLQuery CommentsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case Comment::Issue:
        query.query = SAILHUB_QUERY_GET_ISSUE_COMMENTS;
        break;

    case Comment::PullRequest:
        query.query = SAILHUB_QUERY_GET_PULL_REQUEST_COMMENTS;
        break;

    default:
        break;
    }

    return query;
}
