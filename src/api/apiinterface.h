#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QObject>

#include <QDateTime>
#include <QHash>
#include <QNetworkAccessManager>

#include "graphqlconnector.h"
#include "restapiconnector.h"
#include "src/entities/user.h"
#include "src/models/commentsmodel.h"
#include "src/models/issuesmodel.h"
#include "src/models/labelsmodel.h"
#include "src/models/organizationsmodel.h"
#include "src/models/pullrequestsmodel.h"
#include "src/models/reposmodel.h"
#include "src/models/treemodel.h"
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
        AddComment,
        AddReaction,
        CloseIssue,
        CreateIssue,
        DeleteComment,
        DeleteIssue,
        FollowUser,
        GetFileContent,
        GetIssue,
        GetLogin,
        GetNotifications,
        GetOrganization,
        GetPaginationModel,
        GetProfile,
        GetPullRequest,
        GetUser,
        GetUserByLogin,
        GetRepo,
        GetRepoTree,
        RemoveReaction,
        StarRepo,
        UnfollowUser,
        UnstarRepo,
        UpdateComment,
        UpdateIssue,
        UpdateRepoSubscription
    };
    Q_ENUM(RequestType)

    explicit ApiInterface(QObject *parent = nullptr);

    void setToken(const QString &token);
    Q_INVOKABLE QString token() const;

    // api calls
    void getLogin();
    Q_INVOKABLE void addComment(const QString &body, const QString &subjectId);
    Q_INVOKABLE void addReaction(const QString &nodeId, quint8 reaction);
    Q_INVOKABLE void closeIssue(const QString &nodeId);
    Q_INVOKABLE void createIssue(const QString &title, const QString &body, IssuesModel *model);
    Q_INVOKABLE void deleteComment(const QString &nodeId);
    Q_INVOKABLE void deleteIssue(const QString &nodeId);
    Q_INVOKABLE void followUser(const QString &nodeId, bool follow = true);
    Q_INVOKABLE void getFileContent(const QString &nodeId, const QString &branch);
    Q_INVOKABLE void getIssue(const QString &nodeId);
    Q_INVOKABLE void getNotifications();
    Q_INVOKABLE void getOrganization(const QString &nodeId);
    Q_INVOKABLE void getPaginationModel(PaginationModel *model);
    Q_INVOKABLE void getProfile();
    Q_INVOKABLE void getPullRequest(const QString &nodeId);
    Q_INVOKABLE void getRepo(const QString &nodeId);
    Q_INVOKABLE void getRepoTree(const QString &nodeId,const QString &branch, const QString &path,  TreeModel *model);
    Q_INVOKABLE void getUser(const QString &nodeId);
    Q_INVOKABLE void getUserByLogin(const QString &login);
    Q_INVOKABLE void starRepo(const QString &nodeId, bool star = true);
    Q_INVOKABLE void removeReaction(const QString &nodeId, quint8 reaction);
    Q_INVOKABLE void subscribeToRepo(const QString &nodeId, quint8 state);
    Q_INVOKABLE void updateComment(Comment *comment);
    Q_INVOKABLE void updateIssue(Issue *issue);
    Q_INVOKABLE void updateReactions(const QString &nodeId, quint8 before, quint8 after);

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
    void commentAdded(bool added = true);
    void commentDeleted(bool deleted = true);
    void fileContentAvailable(const QString &content);
    void issueClosed(bool closed = true);
    void issueCreated(bool created = true);
    void issueDeleted(bool deleted = true);
    void issueAvailable(Issue *issue);
    void organizationAvailable(Organization *organization);
    void pullRequestAvailable(PullRequest *request);
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
    void parseRestData(const QJsonDocument &doc, quint8 requestType, const QByteArray &requestId);

private:
    void initialize();
    void parseComments(const QJsonObject &obj, const QByteArray &requestId);
    void parseFileContent(const QJsonObject &obj);
    void parsePaginationModel(const QJsonObject &obj, const QByteArray &requestId);
    void parseRepoSubscription(const QJsonObject &obj);
    void parseRepoTree(const QJsonObject &obj, const QByteArray &requestId);

    GraphQLConnector *m_graphqlConnector{nullptr};
    RestApiConnector *m_restApiConnector{nullptr};

    QNetworkAccessManager *m_manager{new QNetworkAccessManager(this)};
    QHash<QByteArray, PaginationModel *> m_paginationModelRequests;
    QHash<QByteArray, TreeModel *> m_treeModelRequests;

    // properties
    quint8 m_paginationCount{20};
    quint16 m_rateLimitRemaining;
    QDateTime m_rateLimitResetAt;
    bool m_ready{false};
    User *m_profile{new User(this)};

};

#endif // APIINTERFACE_H
