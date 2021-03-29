#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include "node.h"

struct OrganizationListItem {
    QString avatarUrl;
    QString description;
    QString login;
    QString name;
    QString nodeId;
};

class Organization : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(quint32 members READ members WRITE setMembers NOTIFY membersChanged)
    Q_PROPERTY(quint32 projects READ projects WRITE setProjects NOTIFY projectsChanged)
    Q_PROPERTY(quint32 repositories READ repositories WRITE setRepositories NOTIFY repositoriesChanged)
    Q_PROPERTY(quint32 teams READ teams WRITE setTeams NOTIFY teamsChanged)
    Q_PROPERTY(QString twitterUsername READ twitterUsername WRITE setTwitterUsername NOTIFY twitterUsernameChanged)
    Q_PROPERTY(bool viewerIsMember READ viewerIsMember WRITE setViewerIsMember NOTIFY viewerIsMemberChanged)
    Q_PROPERTY(bool viewerIsSponsoring READ viewerIsSponsoring WRITE setViewerIsSponsoring NOTIFY viewerIsSponsoringChanged)
    Q_PROPERTY(QString websiteUrl READ websiteUrl WRITE setWebsiteUrl NOTIFY websiteUrlChanged)

public:
    enum OrganizationType {
        Undefined,
        Search,
        IsMember
    };
    Q_ENUM(OrganizationType)

    explicit Organization(QObject *parent = nullptr);

    QString avatarUrl() const;
    QString description() const;
    QString email() const;
    QString location() const;
    QString login() const;
    quint32 members() const;
    quint32 projects() const;
    quint32 repositories() const;
    quint32 teams() const;
    QString twitterUsername() const;
    bool viewerIsMember() const;
    bool viewerIsSponsoring() const;
    QString websiteUrl() const;

signals:
    void avatarUrlChanged(const QString &avatarUrl);
    void descriptionChanged(const QString &description);
    void emailChanged(const QString &email);
    void locationChanged(const QString &location);
    void loginChanged(const QString &login);
    void membersChanged(quint32 members);
    void projectsChanged(quint32 projects);
    void repositoriesChanged(quint32 repositories);
    void teamsChanged(quint32 teams);
    void twitterUsernameChanged(const QString &twitterUsername);
    void viewerIsMemberChanged(bool viewerIsMember);
    void viewerIsSponsoringChanged(bool viewerIsSponsoring);
    void websiteUrlChanged(const QString &websiteUrl);

public slots:
    void setAvatarUrl(const QString &avatarUrl);
    void setDescription(const QString &description);
    void setEmail(const QString &email);
    void setLocation(const QString &location);
    void setLogin(const QString &login);
    void setMembers(quint32 members);
    void setProjects(quint32 projects);
    void setRepositories(quint32 repositories);
    void setTeams(quint32 teams);
    void setTwitterUsername(const QString &twitterUsername);
    void setViewerIsMember(bool viewerIsMember);
    void setViewerIsSponsoring(bool viewerIsSponsoring);
    void setWebsiteUrl(const QString &websiteUrl);

private:
    QString m_avatarUrl;
    QString m_description;
    QString m_email;
    QString m_location;
    QString m_login;
    quint32 m_members{0};
    quint32 m_projects{0};
    quint32 m_repositories{0};
    quint32 m_teams{0};
    QString m_twitterUsername;
    bool m_viewerIsMember{false};
    bool m_viewerIsSponsoring{false};
    QString m_websiteUrl;
};

#endif // ORGANIZATION_H
