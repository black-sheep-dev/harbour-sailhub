#include "user.h"

User::User(QObject *parent) :
    QObject(parent)
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

QString User::company() const
{
    return m_company;
}

quint32 User::followers() const
{
    return m_followers;
}

quint32 User::following() const
{
    return m_following;
}

QString User::location() const
{
    return m_location;
}

QString User::login() const
{
    return m_login;
}

QString User::name() const
{
    return m_name;
}

quint32 User::organizations() const
{
    return m_organizations;
}

quint32 User::repositories() const
{
    return m_repositories;
}

quint32 User::starredRepositories() const
{
    return m_starredRepositories;
}

UserStatus User::status() const
{
    return m_status;
}

QString User::twitterUsername() const
{
    return m_twitterUsername;
}

QString User::websiteUrl() const
{
    return m_websiteUrl;
}

void User::setAvatarUrl(const QString &avatarUrl)
{
    if (m_avatarUrl == avatarUrl)
        return;

    m_avatarUrl = avatarUrl;
    emit avatarUrlChanged(m_avatarUrl);
}

void User::setBio(const QString &bio)
{
    if (m_bio == bio)
        return;

    m_bio = bio;
    emit bioChanged(m_bio);
}

void User::setCompany(const QString &company)
{
    if (m_company == company)
        return;

    m_company = company;
    emit companyChanged(m_company);
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

void User::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void User::setOrganizations(quint32 organizations)
{
    if (m_organizations == organizations)
        return;

    m_organizations = organizations;
    emit organizationsChanged(m_organizations);
}

void User::setRepositories(quint32 repositories)
{
    if (m_repositories == repositories)
        return;

    m_repositories = repositories;
    emit repositoriesChanged(m_repositories);
}

void User::setStarredRepositories(quint32 starredRepositories)
{
    if (m_starredRepositories == starredRepositories)
        return;

    m_starredRepositories = starredRepositories;
    emit starredRepositoriesChanged(m_starredRepositories);
}

void User::setStatus(UserStatus status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

void User::setTwitterUsername(const QString &twitterUsername)
{
    if (m_twitterUsername == twitterUsername)
        return;

    m_twitterUsername = twitterUsername;
    emit twitterUsernameChanged(m_twitterUsername);
}

void User::setWebsiteUrl(const QString &websiteUrl)
{
    if (m_websiteUrl == websiteUrl)
        return;

    m_websiteUrl = websiteUrl;
    emit websiteUrlChanged(m_websiteUrl);
}
