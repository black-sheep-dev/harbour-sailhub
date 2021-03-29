#ifndef USER_H
#define USER_H

#include "node.h"

struct UserListItem {
    QString avatarUrl;
    QString login;
    QString name;
    QString nodeId;
};

struct UserStatus {
    QString emoji;
    QString message;

    UserStatus() {};
    UserStatus(const UserStatus &other) {
        emoji = other.emoji;
        message = other.message;
    }

    bool operator==(const UserStatus &other) const {
        return emoji == other.emoji && message == other.message;
    }

    bool operator!=(const UserStatus &other) const {
        return !(emoji == other.emoji && message == other.message);
    }
};

class User : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
    Q_PROPERTY(QString bio READ bio WRITE setBio NOTIFY bioChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(quint32 followers READ followers WRITE setFollowers NOTIFY followersChanged)
    Q_PROPERTY(quint32 following READ following WRITE setFollowing NOTIFY followingChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(bool isViewer READ isViewer WRITE setIsViewer NOTIFY isViewerChanged)
    Q_PROPERTY(quint32 organizations READ organizations WRITE setOrganizations NOTIFY organizationsChanged)
    Q_PROPERTY(quint32 repositories READ repositories WRITE setRepositories NOTIFY repositoriesChanged)
    Q_PROPERTY(quint32 starredRepositories READ starredRepositories WRITE setStarredRepositories NOTIFY starredRepositoriesChanged)
    Q_PROPERTY(UserStatus status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString twitterUsername READ twitterUsername WRITE setTwitterUsername NOTIFY twitterUsernameChanged)
    Q_PROPERTY(bool viewerIsFollowing READ viewerIsFollowing WRITE setViewerIsFollowing NOTIFY viewerIsFollowingChanged)
    Q_PROPERTY(QString websiteUrl READ websiteUrl WRITE setWebsiteUrl NOTIFY websiteUrlChanged)

public:    
    enum UserType {
        Undefined,
        Contributor,
        Follower,
        Following,
        OrganizationMember,
        Search,
        Stargazer,
        Watcher
    };
    Q_ENUM(UserType)

    explicit User(QObject *parent = nullptr);

    // properties
    QString avatarUrl() const;
    QString bio() const;
    QString company() const;
    quint32 followers() const;
    quint32 following() const;
    QString location() const;
    QString login() const;
    bool isViewer() const;
    quint32 organizations() const;
    quint32 repositories() const;
    quint32 starredRepositories() const;
    UserStatus status() const;
    QString twitterUsername() const;
    bool viewerIsFollowing() const;
    QString websiteUrl() const;

signals:
    // properties
    void avatarUrlChanged(const QString &avatarUrl);
    void bioChanged(const QString &bio);
    void companyChanged(const QString &company);
    void followersChanged(quint32 followers);
    void followingChanged(quint32 following);
    void locationChanged(const QString &location);
    void loginChanged(const QString &login);
    void isViewerChanged(bool isViewer);
    void organizationsChanged(quint32 organizations);
    void repositoriesChanged(quint32 repositories);
    void starredRepositoriesChanged(quint32 starredRepositories);
    void statusChanged(const UserStatus &status);
    void twitterUsernameChanged(const QString &twitterUsername);
    void viewerIsFollowingChanged(bool following);
    void websiteUrlChanged(const QString &websiteUrl);

public slots:
    // properties
    void setAvatarUrl(const QString &avatarUrl);
    void setBio(const QString &bio);
    void setCompany(const QString &company);
    void setFollowers(quint32 followers);
    void setFollowing(quint32 following);
    void setLocation(const QString &location);
    void setLogin(const QString &login);
    void setIsViewer(bool isViewer);
    void setOrganizations(quint32 organizations);
    void setRepositories(quint32 repositories);
    void setStarredRepositories(quint32 starredRepositories);
    void setStatus(UserStatus status);
    void setTwitterUsername(const QString &twitterUsername);
    void setViewerIsFollowing(bool following);
    void setWebsiteUrl(const QString &websiteUrl);

private:
    // properties
    QString m_avatarUrl;
    QString m_bio;
    QString m_company;
    quint32 m_followers{0};
    quint32 m_following{0};
    QString m_location;
    QString m_login;
    bool m_isViewer{false};
    quint32 m_organizations{0};
    quint32 m_repositories{0};
    quint32 m_starredRepositories{0};
    UserStatus m_status{UserStatus()};
    QString m_twitterUsername;
    bool m_viewerIsFollowing{false};
    QString m_websiteUrl;

};

#endif // USER_H
