#ifndef REPOSMODEL_H
#define REPOSMODEL_H

#include "paginationmodel.h"

#include "src/entities/repo.h"

class ReposModel : public PaginationModel
{
    Q_OBJECT

public:
    enum RepoRoles {
        DescriptionRole            = Qt::UserRole + 1,
        //LanguageRole,
        LanguageColorRole,
        LanguageNameRole,
        NameRole,
        NodeIdRole,
        OwnerRole,
        StargazerCountRole
    };
    Q_ENUM(RepoRoles)

    explicit ReposModel(QObject *parent = nullptr);

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
};

#endif // REPOSMODEL_H
