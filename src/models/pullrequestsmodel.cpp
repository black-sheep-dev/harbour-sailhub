#include "pullrequestsmodel.h"

#include "src/api/datautils.h"

PullRequestsModel::PullRequestsModel(QObject *parent) :
    PaginationModel(parent)
{

}

void PullRequestsModel::addPullRequest(const PullRequestListItem &repo)
{
    beginInsertRows(QModelIndex(), m_pullRequests.count(), m_pullRequests.count());
    m_pullRequests.append(repo);
    endInsertRows();
}

void PullRequestsModel::addPullRequests(const QList<PullRequestListItem> &repos)
{
    beginInsertRows(QModelIndex(), m_pullRequests.count(), m_pullRequests.count() + repos.count() - 1);
    m_pullRequests.append(repos);
    endInsertRows();
}

void PullRequestsModel::setPullRequests(const QList<PullRequestListItem> &repos)
{
    beginResetModel();
    m_pullRequests.clear();
    m_pullRequests = repos;
    endResetModel();
}

int PullRequestsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_pullRequests.count();
}

QVariant PullRequestsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto pr = m_pullRequests.at(index.row());

    switch (role) {
    case CommentCountRole:
        return pr.commentCount;

    case CreatedAtRole:
        return pr.createdAt;

    case NodeIdRole:
        return pr.nodeId;

    case NumberRole:
        return pr.number;

    case RepositoryRole:
        return pr.repository;

    case StateRole:
        return pr.state;

    case TimeSpanRole:
        return pr.timeSpan;

    case TitleRole:
        return pr.title;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PullRequestsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CommentCountRole]     = "commentCount";
    roles[CreatedAtRole]        = "createdAt";
    roles[NodeIdRole]           = "nodeId";
    roles[NumberRole]           = "number";
    roles[RepositoryRole]       = "repository";
    roles[StateRole]            = "state";
    roles[TimeSpanRole]         = "timeSpan";
    roles[TitleRole]            = "title";

    return roles;
}

void PullRequestsModel::clear()
{
    beginResetModel();
    m_pullRequests.clear();
    endResetModel();
}
