#ifndef USER_H
#define USER_H

#include "node.h"

#include <QDateTime>

class User : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
    Q_PROPERTY(QString bio READ bio WRITE setBio NOTIFY bioChanged)
    Q_PROPERTY(QString blog READ blog WRITE setBlog NOTIFY blogChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(quint32 followers READ followers WRITE setFollowers NOTIFY followersChanged)
    Q_PROPERTY(quint32 following READ following WRITE setFollowing NOTIFY followingChanged)
    Q_PROPERTY(QString gravatarId READ gravatarId WRITE setGravatarId NOTIFY gravatarIdChanged)
    Q_PROPERTY(bool hireable READ hireable WRITE setHireable NOTIFY hireableChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(quint32 publicRepos READ publicRepos WRITE setPublicRepos NOTIFY publicReposChanged)
    Q_PROPERTY(quint32 publicGists READ publicGists WRITE setPublicGists NOTIFY publicGistsChanged)
    Q_PROPERTY(qreal score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(QString twitterUsername READ twitterUsername WRITE setTwitterUsername NOTIFY twitterUsernameChanged)
    Q_PROPERTY(quint8 userType READ userType WRITE setUserType NOTIFY userTypeChanged)

public:   
    enum UserType {
        TypeUndefined,
        TypeOrganization,
        TypeUser
    };
    Q_ENUM(UserType)

    explicit User(QObject *parent = nullptr);

    QString avatarUrl() const;
    QString bio() const;
    QString blog() const;
    QString company() const;
    QString email() const;
    quint32 followers() const;
    quint32 following() const;
    QString gravatarId() const;
    bool hireable() const;
    QString location() const;
    QString login() const;
    quint32 publicRepos() const;
    quint32 publicGists() const;
    qreal score() const;
    QString twitterUsername() const;
    quint8 userType() const;

signals:
    void avatarUrlChanged(const QString &url);
    void bioChanged(const QString &bio);
    void blogChanged(const QString &blog);
    void companyChanged(const QString &company);
    void emailChanged(const QString &email);
    void followersChanged(quint32 followers);
    void followingChanged(quint32 following);
    void gravatarIdChanged(const QString &id);
    void hireableChanged(bool hireable);
    void locationChanged(const QString &location);
    void loginChanged(const QString &login);
    void publicReposChanged(quint32 repos);
    void publicGistsChanged(quint32 gists);
    void scoreChanged(qreal score);
    void twitterUsernameChanged(const QString &username);
    void userTypeChanged(quint8 type);

public slots:
    void setAvatarUrl(const QString &url);
    void setBio(const QString &bio);
    void setBlog(const QString &blog);
    void setCompany(const QString &company);
    void setEmail(const QString &email);
    void setFollowers(quint32 followers);
    void setFollowing(quint32 following);
    void setGravatarId(const QString &id);
    void setHireable(bool hireable);
    void setLocation(const QString &location);
    void setLogin(const QString &login);
    void setPublicRepos(quint32 repos);
    void setPublicGists(quint32 gists);
    void setScore(qreal score);
    void setTwitterUsername(const QString &username);
    void setUserType(quint8 type);

private:
    QString m_avatarUrl;
    QString m_bio;
    QString m_blog;
    QString m_company;
    QString m_email;
    quint32 m_followers{0};
    quint32 m_following{0};
    QString m_gravatarId;
    bool m_hireable{false};
    QString m_location;
    QString m_login;
    quint32 m_publicRepos{0};
    quint32 m_publicGists{0};
    qreal m_score{0.0};
    QString m_twitterUsername;
    quint8 m_userType{UserType::TypeUndefined};
};
Q_DECLARE_METATYPE(User*)

#endif // USER_H
