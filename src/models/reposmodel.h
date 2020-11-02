#ifndef REPOSMODEL_H
#define REPOSMODEL_H

#include "nodesmodel.h"

#include "src/entities/repo.h"

class ReposModel : public NodesModel
{
    Q_OBJECT

public:
    enum RepoRoles {
        ArchivedRole            = NodesModel::CustomRole + 1,
        DefaultBranchRole,
        DescriptionRole,
        DisabledRole,
        ForkRole,
        ForksRole,
        FullNameRole,
        HasDownloadsRole,
        HasIssuesRole,
        HasPagesRole,
        HasProjectsRole,
        HasWikiRole,
        HomepageRole,
        LanguageRole,
        LicenseKeyRole,
        LicenseNameRole,
        LicenseUrlRole,
        MirrorUrlRole,
        OpenIssuesRole,
        OwnerRole,
        PrivateRepoRole,
        PushedAtRole,
        ScoreRole,
        SizeRole,
        StargazersRole,
        SubscribersRole,
        WatchersRole
    };
    Q_ENUM(RepoRoles)

    explicit ReposModel(QObject *parent = nullptr);

    Q_INVOKABLE Repo *repoAt(int index);
    Q_INVOKABLE Repo *repoById(quint32 id);
    Q_INVOKABLE Repo *repoById(const QString &id);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

};

#endif // REPOSMODEL_H
