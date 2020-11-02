#include "user.h"

User::User(QObject *parent) :
    Node(parent)
{

}

QString User::avatarUrl() const
{
    return m_avatarUrl;
}

QString User::bio() const
{
    return m_bio;
}

QString User::blog() const
{
    return m_blog;
}

QString User::company() const
{
    return m_company;
}

QString User::email() const
{
    return m_email;
}

quint32 User::followers() const
{
    return m_followers;
}

quint32 User::following() const
{
    return m_following;
}

QString User::gravatarId() const
{
    return m_gravatarId;
}

bool User::hireable() const
{
    return m_hireable;
}

QString User::location() const
{
    return m_location;
}

QString User::login() const
{
    return m_login;
}

quint32 User::publicRepos() const
{
    return m_publicRepos;
}

quint32 User::publicGists() const
{
    return m_publicGists;
}

qreal User::score() const
{
    return m_score;
}

QString User::twitterUsername() const
{
    return m_twitterUsername;
}

quint8 User::userType() const
{
    return m_userType;
}

void User::setAvatarUrl(const QString &url)
{
    if (m_avatarUrl == url)
        return;

    m_avatarUrl = url;
    emit avatarUrlChanged(m_avatarUrl);
}

void User::setBio(const QString &bio)
{
    if (m_bio == bio)
        return;

    m_bio = bio;
    emit bioChanged(m_bio);
}

void User::setBlog(const QString &blog)
{
    if (m_blog == blog)
        return;

    m_blog = blog;
    emit blogChanged(m_blog);
}

void User::setCompany(const QString &company)
{
    if (m_company == company)
        return;

    m_company = company;
    emit companyChanged(m_company);
}

void User::setEmail(const QString &email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged(m_email);
}

void User::setFollowers(quint32 followers)
{
    if (m_followers == followers)
        return;

    m_followers = followers;
    emit followersChanged(m_followers);
}

void User::setFollowing(quint32 following)
{
    if (m_following == following)
        return;

    m_following = following;
    emit followingChanged(m_following);
}

void User::setGravatarId(const QString &id)
{
    if (m_gravatarId == id)
        return;

    m_gravatarId = id;
    emit gravatarIdChanged(m_gravatarId);
}

void User::setHireable(bool hireable)
{
    if (m_hireable == hireable)
        return;

    m_hireable = hireable;
    emit hireableChanged(m_hireable);
}

void User::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged(m_location);
}

void User::setLogin(const QString &login)
{
    if (m_login == login)
        return;

    m_login = login;
    emit loginChanged(m_login);
}

void User::setPublicRepos(quint32 repos)
{
    if (m_publicRepos == repos)
        return;

    m_publicRepos = repos;
    emit publicReposChanged(m_publicRepos);
}

void User::setPublicGists(quint32 gists)
{
    if (m_publicGists == gists)
        return;

    m_publicGists = gists;
    emit publicGistsChanged(m_publicGists);
}

void User::setScore(qreal score)
{
    if (qFuzzyCompare(m_score, score))
        return;

    m_score = score;
    emit scoreChanged(m_score);
}

void User::setTwitterUsername(const QString &username)
{
    if (m_twitterUsername == username)
        return;

    m_twitterUsername = username;
    emit twitterUsernameChanged(m_twitterUsername);
}

void User::setUserType(quint8 type)
{
    if (m_userType == type)
        return;

    m_userType = type;
    emit userTypeChanged(m_userType);
}
