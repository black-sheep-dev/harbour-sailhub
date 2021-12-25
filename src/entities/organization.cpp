#include "organization.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
OrganizationListItem::OrganizationListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    avatarUrl = data.value(ApiKey::AVATAR_URL).toString();
    description = data.value(ApiKey::DESCRIPTION).toString();
    login = data.value(ApiKey::LOGIN).toString();
}

// Object
Organization::Organization(QObject *parent) :
    Node(parent)
{

}

Organization::Organization(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Organization::setData(const QJsonObject &data)
{
    Node::setData(data);

    setAvatarUrl(data.value(ApiKey::AVATAR_URL).toString());
    setDescription(data.value(ApiKey::DESCRIPTION).toString());
    setEmail(data.value(ApiKey::EMAIL).toString());
    setLocation(data.value(ApiKey::LOCATION).toString());
    setLogin(data.value(ApiKey::LOGIN).toString());
    setMembers(DataUtils::DataUtils::getTotalCount(data.value(ApiKey::MEMBERS_WITH_ROLE).toObject()));
    setProjects(DataUtils::getTotalCount(data.value(ApiKey::PROJECTS).toObject()));
    setRepositories(DataUtils::getTotalCount(data.value(ApiKey::REPOSITORIES).toObject()));
    setTeams(DataUtils::getTotalCount(data.value(ApiKey::TEAMS).toObject()));
    setTwitterUsername(data.value(ApiKey::TWITTER_USERNAME).toString());
    setViewerIsMember(data.value(ApiKey::VIEWER_IS_MEMBER).toBool());
    setViewerIsSponsoring(data.value(ApiKey::VIEWER_IS_SPONSORING).toBool());
    setWebsiteUrl(data.value(ApiKey::WEBSITE_URL).toString());
}

const QString &Organization::avatarUrl() const
{
    return m_avatarUrl;
}

const QString &Organization::description() const
{
    return m_description;
}

const QString &Organization::email() const
{
    return m_email;
}

const QString &Organization::location() const
{
    return m_location;
}

const QString &Organization::login() const
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

const QString &Organization::twitterUsername() const
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

const QString &Organization::websiteUrl() const
{
    return m_websiteUrl;
}

void Organization::setAvatarUrl(const QString &avatarUrl)
{
    if (m_avatarUrl == avatarUrl)
        return;

    m_avatarUrl = avatarUrl;
    emit avatarUrlChanged();
}

void Organization::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged();
}

void Organization::setEmail(const QString &email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged();
}

void Organization::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged();
}

void Organization::setLogin(const QString &login)
{
    if (m_login == login)
        return;

    m_login = login;
    emit loginChanged();
}

void Organization::setMembers(quint32 members)
{
    if (m_members == members)
        return;

    m_members = members;
    emit membersChanged();
}

void Organization::setProjects(quint32 projects)
{
    if (m_projects == projects)
        return;

    m_projects = projects;
    emit projectsChanged();
}

void Organization::setRepositories(quint32 repositories)
{
    if (m_repositories == repositories)
        return;

    m_repositories = repositories;
    emit repositoriesChanged();
}

void Organization::setTeams(quint32 teams)
{
    if (m_teams == teams)
        return;

    m_teams = teams;
    emit teamsChanged();
}

void Organization::setTwitterUsername(const QString &twitterUsername)
{
    if (m_twitterUsername == twitterUsername)
        return;

    m_twitterUsername = twitterUsername;
    emit twitterUsernameChanged();
}

void Organization::setViewerIsMember(bool viewerIsMember)
{
    if (m_viewerIsMember == viewerIsMember)
        return;

    m_viewerIsMember = viewerIsMember;
    emit viewerIsMemberChanged();
}

void Organization::setViewerIsSponsoring(bool viewerIsSponsoring)
{
    if (m_viewerIsSponsoring == viewerIsSponsoring)
        return;

    m_viewerIsSponsoring = viewerIsSponsoring;
    emit viewerIsSponsoringChanged();
}

void Organization::setWebsiteUrl(const QString &websiteUrl)
{
    if (m_websiteUrl == websiteUrl)
        return;

    m_websiteUrl = websiteUrl;
    emit websiteUrlChanged();
}
