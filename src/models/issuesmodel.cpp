#include "issuesmodel.h"

IssuesModel::IssuesModel(QObject *parent) :
    PaginationModel(parent)
{

}

void IssuesModel::addIssue(const IssueListItem &issue)
{
    beginInsertRows(QModelIndex(), m_issues.count(),  m_issues.count());
    m_issues.append(issue);
    endInsertRows();
}

void IssuesModel::addIssues(const QList<IssueListItem> &issues)
{
    beginInsertRows(QModelIndex(), m_issues.count(),  m_issues.count() + issues.count() - 1);
    m_issues.append(issues);
    endInsertRows();
}

void IssuesModel::setIssues(const QList<IssueListItem> &issues)
{
    beginResetModel();
    m_issues.clear();
    m_issues = issues;
    endResetModel();
}

int IssuesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_issues.count();
}

QVariant IssuesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto issue = m_issues.at(index.row());

    switch (role) {
    case ClosedRole:
        return issue.closed;

    case CommentCountRole:
        return issue.commentCount;

    case CreatedAtRole:
        return issue.createdAt;

    case NodeIdRole:
        return issue.nodeId;

    case NumberRole:
        return issue.number;

    case RepositoryRole:
        return issue.repository;

    case TimeSpanRole:
        return issue.timeSpan;

    case TitleRole:
        return issue.title;

    case StateRole:
        return issue.state;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> IssuesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ClosedRole]           = "closed";
    roles[CommentCountRole]     = "commentCount";
    roles[CreatedAtRole]        = "createdAt";
    roles[NodeIdRole]           = "nodeId";
    roles[NumberRole]           = "number";
    roles[RepositoryRole]       = "repository";
    roles[TimeSpanRole]         = "timeSpan";
    roles[TitleRole]            = "title";
    roles[StateRole]            = "state";

    return roles;
}

void IssuesModel::clear()
{
    beginResetModel();
    m_issues.clear();
    endResetModel();
}
