#include "reposmodel.h"

ReposModel::ReposModel(QObject *parent) :
    NodesModel(parent)
{

}

Repo *ReposModel::repoAt(int index)
{
    return qobject_cast<Repo *>(nodeAt(index));
}

Repo *ReposModel::repoById(quint32 id)
{
    return qobject_cast<Repo *>(nodeById(id));
}

Repo *ReposModel::repoById(const QString &id)
{
    return qobject_cast<Repo *>(nodeById(id));
}

QVariant ReposModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto *repo = qobject_cast<Repo *>(m_nodes.at(index.row()));

    QVariant variant;

    switch (role) {
    case ArchivedRole:
        return repo->archived();

    case DefaultBranchRole:
        return repo->defaultBranch();

    case DescriptionRole:
        return repo->description();

    case DisabledRole:
        return repo->disabled();

    case ForkRole:
        return repo->fork();

    case ForksRole:
        return repo->forks();

    case FullNameRole:
        return repo->fullName();

    case HasDownloadsRole:
        return repo->hasDownloads();

    case HasIssuesRole:
        return repo->hasIssues();

    case HasPagesRole:
        return repo->hasPages();

    case HasProjectsRole:
        return repo->hasProjects();

    case HomepageRole:
        return repo->homepage();

    case LanguageRole:
        return repo->language();

    case LicenseKeyRole:
        return repo->licenseKey();

    case LicenseNameRole:
        return repo->licenseName();

    case LicenseUrlRole:
        return repo->licenseUrl();

    case MirrorUrlRole:
        return repo->mirrorUrl();

    case OpenIssuesRole:
        return repo->openIssues();

    case OwnerRole:
        variant.setValue(repo->owner());
        return variant;

    case PrivateRepoRole:
        return repo->privateRepo();

    case PushedAtRole:
        return repo->pushedAt();

    case ScoreRole:
        return repo->score();

    case SizeRole:
        return repo->size();

    case StargazersRole:
        return repo->stargazers();

    case SubscribersRole:
        return repo->subscribers();

    case WatchersRole:
        return repo->watchers();

    default:
        return NodesModel::data(index, role);
    }
}

QHash<int, QByteArray> ReposModel::roleNames() const
{
    QHash<int, QByteArray> roles = NodesModel::roleNames();

    roles[ArchivedRole]         = "archived";
    roles[DefaultBranchRole]    = "defaultBranch";
    roles[DescriptionRole]      = "description";
    roles[DisabledRole]         = "disabled";
    roles[ForkRole]             = "fork";
    roles[ForksRole]            = "forks";
    roles[FullNameRole]         = "fullName";
    roles[HasDownloadsRole]     = "hasDownloads";
    roles[HasIssuesRole]        = "hasIssues";
    roles[HasPagesRole]         = "hasPages";
    roles[HasProjectsRole]      = "hasProjects";
    roles[HasWikiRole]          = "hasWiki";
    roles[HomepageRole]         = "homepage";
    roles[LanguageRole]         = "language";
    roles[LicenseKeyRole]       = "licenseKey";
    roles[LicenseNameRole]      = "licenseName";
    roles[LicenseUrlRole]       = "licenseUrl";
    roles[MirrorUrlRole]        = "mirrorUrl";
    roles[OpenIssuesRole]       = "openIssues";
    roles[OwnerRole]            = "owner";
    roles[PrivateRepoRole]      = "privateRepo";
    roles[PushedAtRole]         = "pushedAt";
    roles[ScoreRole]            = "score";
    roles[SizeRole]             = "size";
    roles[StargazersRole]       = "stargazers";
    roles[SubscribersRole]      = "subscribers";
    roles[WatchersRole]         = "watchers";

    return roles;
}
