#include "organization.h"

Organization::Organization(QObject *parent) :
    Node(parent)
{

}

QString Organization::avatarUrl() const
{
    return m_avatarUrl;
}

QString Organization::description() const
{
    return m_description;
}

QString Organization::email() const
{
    return m_email;
}

QString Organization::location() const
{
    return m_location;
}

QString Organization::login() const
{
    return m_login;
}

quint32 Organization::members() const
{
    return m_members;
}

quint32 Organization::projects() const
{
    return m_projects;
}

quint32 Organization::repositories() const
{
    return m_repositories;
}

quint32 Organization::teams() const
{
    return m_teams;
}

QString Organization::twitterUsername() const
{
    return m_twitterUsername;
}

bool Organization::viewerIsMember() const
{
    return m_viewerIsMember;
}

bool Organization::viewerIsSponsoring() const
{
    return m_viewerIsSponsoring;
}

QString Organization::websiteUrl() const
{
    return m_websiteUrl;
}

void Organization::setAvatarUrl(const QString &avatarUrl)
{
    if (m_avatarUrl == avatarUrl)
        return;

    m_avatarUrl = avatarUrl;
    emit avatarUrlChanged(m_avatarUrl);
}

void Organization::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
}

void Organization::setEmail(const QString &email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged(m_email);
}

void Organization::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged(m_location);
}

void Organization::setLogin(const QString &login)
{
    if (m_login == login)
        return;

    m_login = login;
    emit loginChanged(m_login);
}

void Organization::setMembers(quint32 members)
{
    if (m_members == members)
        return;

    m_members = members;
    emit membersChanged(m_members);
}

void Organization::setProjects(quint32 projects)
{
    if (m_projects == projects)
        return;

    m_projects = projects;
    emit projectsChanged(m_projects);
}

void Organization::setRepositories(quint32 repositories)
{
    if (m_repositories == repositories)
        return;

    m_repositories = repositories;
    emit repositoriesChanged(m_repositories);
}

void Organization::setTeams(quint32 teams)
{
    if (m_teams == teams)
        return;

    m_teams = teams;
    emit teamsChanged(m_teams);
}

void Organization::setTwitterUsername(const QString &twitterUsername)
{
    if (m_twitterUsername == twitterUsername)
        return;

    m_twitterUsername = twitterUsername;
    emit twitterUsernameChanged(m_twitterUsername);
}

void Organization::setViewerIsMember(bool viewerIsMember)
{
    if (m_viewerIsMember == viewerIsMember)
        return;

    m_viewerIsMember = viewerIsMember;
    emit viewerIsMemberChanged(m_viewerIsMember);
}

void Organization::setViewerIsSponsoring(bool viewerIsSponsoring)
{
    if (m_viewerIsSponsoring == viewerIsSponsoring)
        return;

    m_viewerIsSponsoring = viewerIsSponsoring;
    emit viewerIsSponsoringChanged(m_viewerIsSponsoring);
}

void Organization::setWebsiteUrl(const QString &websiteUrl)
{
    if (m_websiteUrl == websiteUrl)
        return;

    m_websiteUrl = websiteUrl;
    emit websiteUrlChanged(m_websiteUrl);
}
