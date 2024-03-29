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
        CreatedAtTimeSpanRole,
        NodeIdRole,
        NumberRole,
        RepositoryRole,
        SortRole,
        StateRole,
        TitleRole,
        UpdatedAtRole,
        UpdatedAtTimeSpanRole
    };
    Q_ENUM(PullRequestRoles)

    explicit PullRequestsModel(QObject *parent = nullptr);
    ~PullRequestsModel() override;

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
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
    QString sortField() const override;
};

#endif // PULLREQUESTSMODEL_H
