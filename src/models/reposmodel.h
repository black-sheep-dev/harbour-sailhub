#ifndef REPOSMODEL_H
#define REPOSMODEL_H

#include "paginationmodel.h"

#include "src/entities/repo.h"

class ReposModel : public PaginationModel
{
    Q_OBJECT

public:
    enum RepoRoles {
        CreatedAtRole           = Qt::UserRole + 1,
        DescriptionRole,
        FlagsRole,
        LanguageColorRole,
        LanguageNameRole,
        LockReasonRole,
        NameRole,
        NodeIdRole,
        OwnerAvatarRole,
        OwnerLoginRole,
        PushedAtRole,
        SortRole,
        StargazerCountRole,
        UpdatedAtRole
    };
    Q_ENUM(RepoRoles)

    explicit ReposModel(QObject *parent = nullptr);
    ~ReposModel() override;

    void addRepo(const RepoListItem &repo);
    void addRepos(const QList<RepoListItem> &repos);
    void setRepos(const QList<RepoListItem> &repos);

private:
    QList<RepoListItem> m_repos;

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;

    // PaginationModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
    QString sortField() const override;
};

#endif // REPOSMODEL_H
