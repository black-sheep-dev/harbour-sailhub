#ifndef COMMITSMODEL_H
#define COMMITSMODEL_H

#include "paginationmodel.h"

#include "src/entities/commit.h"

class CommitsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum CommitRoles {
        AuthorAvatarRole    = Qt::UserRole + 1,
        AuthorLoginRole,
        MessageHeadlineRole,
        NodeIdRole,
        PushedAtTimeSpanRole
    };
    Q_ENUM(CommitRoles)

    explicit CommitsModel(QObject *parent = nullptr);

    void addCommit(const CommitListItem &commit);
    void addCommits(const QList<CommitListItem> &commits);
    void setCommits(const QList<CommitListItem> &commits);

private:
    QList<CommitListItem> m_commits;


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // BaseModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
};

#endif // COMMITSMODEL_H
