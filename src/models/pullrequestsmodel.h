#ifndef PULLREQUESTSMODEL_H
#define PULLREQUESTSMODEL_H

#include "paginationmodel.h"

#include "src/entities/pullrequest.h"

class PullRequestsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum PullRequestRoles {
        CommentCountRole        = Qt::UserRole + 1,
        CreatedAtRole,
        NodeIdRole,
        NumberRole,
        RepositoryRole,
        StateRole,
        TimeSpanRole,
        TitleRole
    };
    Q_ENUM(PullRequestRoles)

    explicit PullRequestsModel(QObject *parent = nullptr);

    void addPullRequest(const PullRequestListItem &repo);
    void addPullRequests(const QList<PullRequestListItem> &repos);
    void setPullRequests(const QList<PullRequestListItem> &repos);

private:
    QList<PullRequestListItem> m_pullRequests;


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // PaginationModel interface
public:
    void clear() override;
};

#endif // PULLREQUESTSMODEL_H
