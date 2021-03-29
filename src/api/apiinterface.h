#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QObject>

#include <QDateTime>
#include <QHash>

#include "graphqlconnector.h"
#include "src/entities/user.h"
#include "src/models/issuesmodel.h"
#include "src/models/organizationsmodel.h"
#include "src/models/reposmodel.h"
#include "src/models/usersmodel.h"

static const QString SAILHUB_API_GRAPHQL_URL            = QStringLiteral("https://api.github.com/graphql");

class ApiInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 paginationCount READ paginationCount WRITE setPaginationCount NOTIFY paginationCountChanged)
    Q_PROPERTY(quint16 rateLimitRemaining READ rateLimitRemaining NOTIFY rateLimitRemainingChanged)
    Q_PROPERTY(QDateTime rateLimitResetAt READ rateLimitResetAt NOTIFY rateLimitResetAtChanged)
    Q_PROPERTY(bool ready READ ready WRITE setReady NOTIFY readyChanged)
    Q_PROPERTY(User* profile READ profile NOTIFY profileChanged)

public:
    enum ApiError {
        ErrorUndefined,
        ErrorTimeout,
        ErrorUnauthorized,
        ErrorServerUnavailable
    };
    Q_ENUM(ApiError)

    enum RequestType {
        Undefined,
        CreateIssue,
        FollowUser,
        GetComments,
        GetIssue,
        GetIssues,
        GetLogin,
        GetOrganization,
        GetOrganizations,
        GetProfile,
        GetUser,
        GetUsers,
        GetRepo,
        GetRepos,
        SearchOrganization,
        SearchRepo,
        SearchUser,
        StarRepo,
        UnfollowUser,
        UnstarRepo,
        UpdateRepoSubscription
    };
    Q_ENUM(RequestType)

    explicit ApiInterface(QObject *parent = nullptr);

    void setToken(const QString &token);
    Q_INVOKABLE QString token() const;

    // api calls
    void getLogin();
    Q_INVOKABLE void createIssue(const QString &title, const QString &body, IssuesModel *model);
    Q_INVOKABLE void followUser(const QString &nodeId, bool follow = true);
    Q_INVOKABLE void getComments(CommentsModel *model);
    Q_INVOKABLE void getIssue(const QString &nodeId);
    Q_INVOKABLE void getIssues(IssuesModel *model);
    Q_INVOKABLE void getOrganization(const QString &nodeId);
    Q_INVOKABLE void getOrganizations(OrganizationsModel *model);
    Q_INVOKABLE void getProfile();
    Q_INVOKABLE void getRepo(const QString &nodeId);
    Q_INVOKABLE void getRepos(ReposModel *model);
    Q_INVOKABLE void getUser(const QString &nodeId);
    Q_INVOKABLE void getUsers(UsersModel *model);
    Q_INVOKABLE void searchOrganization(const QString &pattern, OrganizationsModel *model);
    Q_INVOKABLE void searchRepo(const QString &pattern, ReposModel *model);
    Q_INVOKABLE void searchUser(const QString &pattern, UsersModel *model);
    Q_INVOKABLE void starRepo(const QString &nodeId, bool star = true);
    Q_INVOKABLE void subscribeToRepo(const QString &nodeId, quint8 state);

    // properties
    quint8 paginationCount() const;
    quint16 rateLimitRemaining() const;
    QDateTime rateLimitResetAt() const;
    bool ready() const;
    User *profile() const;

public slots:
    void setPaginationCount(quint8 paginationCount);  
    void setReady(bool ready);

signals:
    void apiError(quint8 error, const QString &msg = QString());
    void issueCreated(Issue *issue);
    void issueAvailable(Issue *issue);
    void organizationAvailable(Organization *organization);
    void repoAvailable(Repo *repo);
    void repoStarred(const QString &nodeId, bool starred);
    void subscribedToRepo(const QString &nodeId, quint8 state);
    void userAvailable(User *user);
    void userFollowed(const QString &nodeId, bool following);

    // properties
    void paginationCountChanged(quint8 count);
    void rateLimitRemainingChanged(quint16 count);
    void rateLimitResetAtChanged(const QDateTime &timestamp);
    void readyChanged(bool ready);
    void profileChanged(User *profile);

private slots:
    void onConnectionError(quint16 error, const QString &msg);
    void parseData(const QJsonObject &obj, quint8 requestType, const QByteArray &requestId);

private:
    void initialize();
    void parseComments(const QJsonObject &obj, const QByteArray &requestId);
    void parseIssues(const QJsonObject &obj, const QByteArray &requestId);
    void parseOrganizations(const QJsonObject &obj, const QByteArray &requestId);
    void parseRepos(const QJsonObject &obj, const QByteArray &requestId);
    void parseRepoSubscription(const QJsonObject &obj);
    void parseUsers(const QJsonObject &obj, const QByteArray &requestId);

    GraphQLConnector *m_connector{new GraphQLConnector(SAILHUB_API_GRAPHQL_URL, this)};
    QHash<QByteArray, CommentsModel *> m_commentsModelRequests;
    QHash<QByteArray, IssuesModel *> m_issuesModelRequests;
    QHash<QByteArray, OrganizationsModel *> m_organizationsModelRequests;
    QHash<QByteArray, ReposModel *> m_reposModelRequests;
    QHash<QByteArray, UsersModel *> m_usersModelRequests;

    // properties
    quint8 m_paginationCount{20};
    quint16 m_rateLimitRemaining;
    QDateTime m_rateLimitResetAt;
    bool m_ready{false};
    User *m_profile{new User(this)};

};

#endif // APIINTERFACE_H
