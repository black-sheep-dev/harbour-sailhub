#include "usersmodel.h"

UsersModel::UsersModel(QObject *parent) :
    NodesModel(parent)
{

}

User *UsersModel::userAt(int index)
{
    return qobject_cast<User *>(nodeAt(index));
}

User *UsersModel::userById(quint32 id)
{
    return qobject_cast<User *>(nodeById(id));
}

User *UsersModel::userById(const QString &id)
{
    return qobject_cast<User *>(nodeById(id));
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto *user = qobject_cast<User *>(m_nodes.at(index.row()));

    switch (role) {
    case NameRole:
        if (user->name().isEmpty())
            return user->login();

        return user->name();

    case AvatarUrlRole:
        return user->avatarUrl();

    case BioRole:
        return user->bio();

    case BlogRole:
        return user->blog();

    case CompanyRole:
        return user->company();

    case EmailRole:
        return user->email();

    case FollowersRole:
        return user->followers();

    case FollowingRole:
        return user->following();

    case GravatarIdRole:
        return user->gravatarId();

    case HireableRole:
        return user->hireable();

    case LocationRole:
        return user->location();

    case LoginRole:
        return user->login();

    case PublicReposRole:
        return user->publicRepos();

    case PublicGistsRole:
        return user->publicGists();

    case ScoreRole:
        return user->score();

    case TwitterUsernameRole:
        return user->twitterUsername();

    case UserTypeRole:
        return user->userType();

    default:
        return NodesModel::data(index, role);
    }
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles = NodesModel::roleNames();

    roles[AvatarUrlRole]        = "avatarUrl";
    roles[BioRole]              = "bio";
    roles[BlogRole]             = "blog";
    roles[CompanyRole]          = "company";
    roles[EmailRole]            = "email";
    roles[FollowersRole]        = "followers";
    roles[FollowingRole]        = "following";
    roles[GravatarIdRole]       = "gravatar_id";
    roles[HireableRole]         = "hireable";
    roles[LocationRole]         = "location";
    roles[LoginRole]            = "login";
    roles[PublicReposRole]      = "publicRepos";
    roles[PublicGistsRole]      = "publicGists";
    roles[ScoreRole]            = "score";
    roles[TwitterUsernameRole]  = "twitterUsername";
    roles[UserTypeRole]         = "userType";

    return roles;
}
