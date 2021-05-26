#include "commentsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

static const QString SAILHUB_QUERY_GET_COMMENTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on %3 {"
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

int CommentsModel::count()
{
    return m_comments.count();
}

void CommentsModel::addComment(Comment *comment)
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

void CommentsModel::addComments(const QList<Comment *> &comments)
{
    QList<Comment *> items;
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

void CommentsModel::setComments(const QList<Comment *> &comments)
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
        return comment->lastEditedAt();

    case NodeIdRole:
        return comment->nodeId();

    case ReactionConfusedCountRole:
        return comment->reactionConfusedCount();

    case ReactionEyesCountRole:
        return comment->reactionEyesCount();

    case ReactionHeartCountRole:
        return comment->reactionHeartCount();

    case ReactionHoorayCountRole:
        return comment->reactionHoorayCount();

    case ReactionLaughCountRole:
        return comment->reactionLaughCount();

    case ReactionRocketCountRole:
        return comment->reactionRocketCount();

    case ReactionThumbsDownCountRole:
        return comment->reactionThumbsDownCount();

    case ReactionThumbsUpCountRole:
        return comment->reactionThumbsUpCount();

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

    roles[AuthorIdRole]                 = "authorId";
    roles[AuthorAvatarUrlRole]          = "authorAvatarUrl";
    roles[AuthorLoginRole]              = "authorLogin";
    roles[BodyRole]                     = "body";
    roles[BodyExcerptRole]              = "bodyExcerpt";
    roles[CreatedAtRole]                = "createdAt";
    roles[CreatedAtTimeSpanRole]        = "createdAtTimeSpan";
    roles[EditedRole]                   = "edited";
    roles[LastEditAtRole]               = "lastEditAt";
    roles[NodeIdRole]                   = "nodeId";
    roles[ReactionConfusedCountRole]    = "reactionConfusedCount";
    roles[ReactionEyesCountRole]        = "reactionEyesCount";
    roles[ReactionHeartCountRole]       = "reactionHeartCount";
    roles[ReactionHoorayCountRole]      = "reactionHoorayCount";
    roles[ReactionLaughCountRole]       = "reactionLaughCount";
    roles[ReactionRocketCountRole]      = "reactionRocketCount";
    roles[ReactionThumbsDownCountRole]  = "reactionThumbsDownCount";
    roles[ReactionThumbsUpCountRole]    = "reactionThumbsUpCount";
    roles[ViewerAbilitiesRole]          = "viewerAbilities";
    roles[ViewerDidAuthorRole]          = "viewerDidAuthor";

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

    // read comment items
    QList<Comment *> items;

    const QJsonArray nodes = comments.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject item = node.toObject();
        if (item.isEmpty())
            continue;

        items.append(new Comment(item));
    }

    addComments(items);
    setLoading(false);
}

GraphQLQuery CommentsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    switch (modelType()) {
    case Comment::Issue:
        query.query = SAILHUB_QUERY_GET_COMMENTS.arg(QStringLiteral("Issue"));
        break;

    case Comment::PullRequest:
        query.query = SAILHUB_QUERY_GET_COMMENTS.arg(QStringLiteral("PullRequest"));
        break;

    default:
        break;
    }

    return query;
}
