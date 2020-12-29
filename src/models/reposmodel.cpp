#include "reposmodel.h"

ReposModel::ReposModel(QObject *parent) :
    PaginationModel(parent)
{

}

void ReposModel::addRepo(const RepoListItem &repo)
{
    beginInsertRows(QModelIndex(), m_repos.count(), m_repos.count());
    m_repos.append(repo);
    endInsertRows();
}

void ReposModel::addRepos(const QList<RepoListItem> &repos)
{
    beginInsertRows(QModelIndex(), m_repos.count(), m_repos.count() + repos.count() - 1);
    m_repos.append(repos);
    endInsertRows();
}

void ReposModel::setRepos(const QList<RepoListItem> &repos)
{
    beginResetModel();
    m_repos.clear();
    m_repos = repos;
    endResetModel();
}

QVariant ReposModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto repo = m_repos.at(index.row());

    switch (role) {
    case DescriptionRole:
        return repo.description;

    case LanguageColorRole:
        return repo.language.color;

    case LanguageNameRole:
        return repo.language.name;

    case NameRole:
        return repo.name;

    case NodeIdRole:
        return repo.nodeId;

    case OwnerRole:
        return repo.owner;

    case StargazerCountRole:
        return repo.stargazerCount;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReposModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DescriptionRole]      = "description";
    //roles[LanguageRole]         = "language";
    roles[LanguageColorRole]    = "languageColor";
    roles[LanguageNameRole]     = "languageName";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";
    roles[OwnerRole]            = "owner";
    roles[StargazerCountRole]   = "stargazerCount";

    return roles;
}

int ReposModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_repos.count();
}
