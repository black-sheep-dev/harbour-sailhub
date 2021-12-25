#include "user.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
UserListItem::UserListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    avatarUrl = data.value(ApiKey::AVATAR_URL).toString();
    login = data.value(ApiKey::LOGIN).toString();
}

// Object
User::User(QObject *parent) :
    Node(parent)
{

}

User::User(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void User::setData(const QJsonObject &data)
{
    Node::setData(data);

    setAvatarUrl(data.value(ApiKey::AVATAR_URL).toString());
    setBio(data.value(ApiKey::BIO).toString());
    setCompany(data.value(ApiKey::COMPANY).toString());
    setEmail(data.value(ApiKey::EMAIL).toString());
    setFollowers(DataUtils::getTotalCount(data.value(ApiKey::FOLLOWERS).toObject()));
    setFollowing(DataUtils::getTotalCount(data.value(ApiKey::FOLLOWING).toObject()));
    setGistCount(DataUtils::getTotalCount(data.value(ApiKey::GISTS).toObject()));
    setLocation(data.value(ApiKey::LOCATION).toString());
    setLogin(data.value(ApiKey::LOGIN).toString());
    setIsViewer(data.value(ApiKey::IS_VIEWER).toBool());
    setOrganizations(DataUtils::getTotalCount(data.value(ApiKey::ORGANIZATIONS).toObject()));
    setRepositories(DataUtils::getTotalCount(data.value(ApiKey::REPOSITORIES).toObject()));
    setStarredRepositories(DataUtils::getTotalCount(data.value(ApiKey::STARRED_REPOSITORIES).toObject()));
    setTwitterUsername(data.value(ApiKey::TWITTER_USERNAME).toString());
    setViewerIsFollowing(data.value(ApiKey::VIEWER_IS_FOLLOWING).toBool());
    setWebsiteUrl(data.value(ApiKey::WEBSITE_URL).toString());

    // user status
    const QJsonObject status = data.value(ApiKey::STATUS).toObject();
    setStatusEmoji(DataUtils::getEmojiLinkFromString(status.value(ApiKey::EMOJI_HTML).toString()));
    setStatusMessage(status.value(ApiKey::MESSAGE).toString());
}

const QString &User::avatarUrl() const
{
    return m_avatarUrl;
}

const QString &User::bio() const
{
    return m_bio;
}

const QString &User::company() const
{
    return m_company;
}

const QString &User::email() const
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

quint32 User::gistCount() const
{
    return m_gistCount;
}

const QString &User::location() const
{
    return m_location;
}

const QString &User::login() const
{
    return m_login;
}

bool User::isViewer() const
{
    return m_isViewer;
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

const QString &User::statusEmoji() const
{
    return m_statusEmoji;
}

const QString &User::statusMessage() const
{
    return m_statusMessage;
}

const QString &User::twitterUsername() const
{
    return m_twitterUsername;
}

bool User::viewerIsFollowing() const
{
    return m_viewerIsFollowing;
}

const QString &User::websiteUrl() const
{
    return m_websiteUrl;
}

void User::setAvatarUrl(const QString &avatarUrl)
{
    if (m_avatarUrl == avatarUrl)
        return;

    m_avatarUrl = avatarUrl;
    emit avatarUrlChanged();
}

void User::setBio(const QString &bio)
{
    if (m_bio == bio)
        return;

    m_bio = bio;
    emit bioChanged();
}

void User::setCompany(const QString &company)
{
    if (m_company == company)
        return;

    m_company = company;
    emit companyChanged();
}

void User::setEmail(const QString &email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged();
}

void User::setFollowers(quint32 followers)
{
    if (m_followers == followers)
        return;

    m_followers = followers;
    emit followersChanged();
}

void User::setFollowing(quint32 following)
{
    if (m_following == following)
        return;

    m_following = following;
    emit followingChanged();
}

void User::setGistCount(quint32 count)
{
    if (m_gistCount == count)
        return;

    m_gistCount = count;
    emit gistCountChanged();
}

void User::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged();
}

void User::setLogin(const QString &login)
{
    if (m_login == login)
        return;

    m_login = login;
    emit loginChanged();
}

void User::setIsViewer(bool isViewer)
{
    if (m_isViewer == isViewer)
        return;

    m_isViewer = isViewer;
    emit isViewerChanged();
}

void User::setOrganizations(quint32 organizations)
{
    if (m_organizations == organizations)
        return;

    m_organizations = organizations;
    emit organizationsChanged();
}

void User::setRepositories(quint32 repositories)
{
    if (m_repositories == repositories)
        return;

    m_repositories = repositories;
    emit repositoriesChanged();
}

void User::setStarredRepositories(quint32 starredRepositories)
{
    if (m_starredRepositories == starredRepositories)
        return;

    m_starredRepositories = starredRepositories;
    emit starredRepositoriesChanged();
}

void User::setStatusEmoji(const QString &emoji)
{
    if (m_statusEmoji == emoji)
        return;

    m_statusEmoji = emoji;
    emit statusEmojiChanged();
}

void User::setStatusMessage(const QString &message)
{
    if (m_statusMessage == message)
        return;

    m_statusMessage = message;
    emit statusMessageChanged();
}

void User::setTwitterUsername(const QString &twitterUsername)
{
    if (m_twitterUsername == twitterUsername)
        return;

    m_twitterUsername = twitterUsername;
    emit twitterUsernameChanged();
}

void User::setViewerIsFollowing(bool following)
{
    if (m_viewerIsFollowing == following)
        return;

    m_viewerIsFollowing = following;
    emit viewerIsFollowingChanged();
}

void User::setWebsiteUrl(const QString &websiteUrl)
{
    if (m_websiteUrl == websiteUrl)
        return;

    m_websiteUrl = websiteUrl;
    emit websiteUrlChanged();
}
