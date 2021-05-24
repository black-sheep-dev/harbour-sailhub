#include "commitsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET PULL REQEUEST COMMITS
static const QString SAILHUB_QUERY_GET_PULL_REQUEST_COMMITS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on PullRequest {"
                       "            id"
                       "            commits("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor "
                       "                    ) {"
                       "                nodes {"
                       "                    commit {"
                       "                        %1"
                       "                    }"
                       "                }"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_COMMIT_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

CommitsModel::CommitsModel(QObject *parent) :
    PaginationModel(parent)
{

}

void CommitsModel::addCommit(const CommitListItem &commit)
{
    beginInsertRows(QModelIndex(), m_commits.count(),  m_commits.count());
    m_commits.append(commit);
    endInsertRows();
}

void CommitsModel::addCommits(const QList<CommitListItem> &commits)
{
    beginInsertRows(QModelIndex(), m_commits.count(),  m_commits.count() + commits.count() - 1);
    m_commits.append(commits);
    endInsertRows();
}

void CommitsModel::setCommits(const QList<CommitListItem> &commits)
{
    beginResetModel();
    m_commits.clear();
    m_commits = commits;
    endResetModel();
}

int CommitsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_commits.count();
}

QVariant CommitsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &commit = m_commits[index.row()];

    switch (role) {
    case AuthorAvatarRole:
        return commit.authorAvatar;

    case AuthorLoginRole:
        return commit.authorLogin;

    case MessageHeadlineRole:
        return commit.messageHeadline;

    case NodeIdRole:
        return commit.nodeId;

    case PushedAtTimeSpanRole:
        return commit.pushedAtTimeSpan;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CommitsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AuthorAvatarRole]             = "authorAvatar";
    roles[AuthorLoginRole]               = "authorName";
    roles[MessageHeadlineRole]          = "messageHeadline";
    roles[NodeIdRole]                   = "nodeId";
    roles[PushedAtTimeSpanRole]         = "pushedAtTimeSpan";

    return roles;
}

void CommitsModel::clear()
{
    beginResetModel();
    m_commits.clear();
    endResetModel();
}

void CommitsModel::parseQueryResult(const QJsonObject &data)
{
    QJsonObject commits;

    switch (modelType()) {
    case Commit::PullRequest:
        commits = data.value(ApiKey::NODE).toObject()
                      .value(ApiKey::COMMITS).toObject();
        break;

    default:
        break;
    }

    const QJsonValue count = commits.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(commits, count));

    // read commit items
    QList<CommitListItem> items;

    const QJsonArray nodes = commits.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject commit = node.toObject();
        if (commit.isEmpty())
            continue;

        items.append(CommitListItem(commit));
    }

    addCommits(items);

    setLoading(false);
}

GraphQLQuery CommitsModel::query() const
{
    GraphQLQuery query;
    query.variables = defaultQueryVariables();

    // query
    switch (modelType()) {
    case Commit::PullRequest:
        query.query = SAILHUB_QUERY_GET_PULL_REQUEST_COMMITS;
        query.variables.insert(QueryVar::NODE_ID, identifier());
        break;

    default:
        break;
    }

    return query;
}
