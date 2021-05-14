#ifndef USER_H
#define USER_H

#include "node.h"

struct UserListItem {
    QString avatarUrl;
    QString login;
    QString name;
    QString nodeId;
};

class User : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
    Q_PROPERTY(QString bio READ bio WRITE setBio NOTIFY bioChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(quint32 followers READ followers WRITE setFollowers NOTIFY followersChanged)
    Q_PROPERTY(quint32 following READ following WRITE setFollowing NOTIFY followingChanged)
    Q_PROPERTY(quint32 gistCount READ gistCount WRITE setGistCount NOTIFY gistCountChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(bool isViewer READ isViewer WRITE setIsViewer NOTIFY isViewerChanged)
    Q_PROPERTY(quint32 organizations READ organizations WRITE setOrganizations NOTIFY organizationsChanged)
    Q_PROPERTY(quint32 repositories READ repositories WRITE setRepositories NOTIFY repositoriesChanged)
    Q_PROPERTY(quint32 starredRepositories READ starredRepositories WRITE setStarredRepositories NOTIFY starredRepositoriesChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString twitterUsername READ twitterUsername WRITE setTwitterUsername NOTIFY twitterUsernameChanged)
    Q_PROPERTY(bool viewerIsFollowing READ viewerIsFollowing WRITE setViewerIsFollowing NOTIFY viewerIsFollowingChanged)
    Q_PROPERTY(QString websiteUrl READ websiteUrl WRITE setWebsiteUrl NOTIFY websiteUrlChanged)

public:    
    enum UserType {
        Undefined,
        Assignable,
        Contributor,
        Follower,
        Following,
        IssueAssignee,
        IssueParticipant,
        OrganizationMember,
        PullRequestAssignee,
        PullRequestParticipant,
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
    QString email() const;
    quint32 followers() const;
    quint32 following() const;
    quint32 gistCount() const;
    QString location() const;
    QString login() const;
    bool isViewer() const;
    quint32 organizations() const;
    quint32 repositories() const;
    quint32 starredRepositories() const;
    QString status() const;
    QString twitterUsername() const;
    bool viewerIsFollowing() const;
    QString websiteUrl() const;

signals:
    // properties
    void avatarUrlChanged(const QString &avatarUrl);
    void bioChanged(const QString &bio);
    void companyChanged(const QString &company);
    void emailChanged(const QString &email);
    void followersChanged(quint32 followers);
    void followingChanged(quint32 following);
    void gistCountChanged(quint32 count);
    void locationChanged(const QString &location);
    void loginChanged(const QString &login);
    void isViewerChanged(bool isViewer);
    void organizationsChanged(quint32 organizations);
    void repositoriesChanged(quint32 repositories);
    void starredRepositoriesChanged(quint32 starredRepositories);
    void statusChanged(const QString &status);
    void twitterUsernameChanged(const QString &twitterUsername);
    void viewerIsFollowingChanged(bool following);
    void websiteUrlChanged(const QString &websiteUrl);

public slots:
    // properties
    void setAvatarUrl(const QString &avatarUrl);
    void setBio(const QString &bio);
    void setCompany(const QString &company);
    void setEmail(const QString &email);
    void setFollowers(quint32 followers);
    void setFollowing(quint32 following);
    void setGistCount(quint32 count);
    void setLocation(const QString &location);
    void setLogin(const QString &login);
    void setIsViewer(bool isViewer);
    void setOrganizations(quint32 organizations);
    void setRepositories(quint32 repositories);
    void setStarredRepositories(quint32 starredRepositories);
    void setStatus(const QString &status);
    void setTwitterUsername(const QString &twitterUsername);
    void setViewerIsFollowing(bool following);
    void setWebsiteUrl(const QString &websiteUrl);

private:
    // properties
    QString m_avatarUrl;
    QString m_bio;
    QString m_company;
    QString m_email;
    quint32 m_followers{0};
    quint32 m_following{0};
    quint32 m_gistCount{0};
    QString m_location;
    QString m_login;
    bool m_isViewer{false};
    quint32 m_organizations{0};
    quint32 m_repositories{0};
    quint32 m_starredRepositories{0};
    QString m_status;
    QString m_twitterUsername;
    bool m_viewerIsFollowing{false};
    QString m_websiteUrl;
};

#endif // USER_H
