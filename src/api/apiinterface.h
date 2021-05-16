#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QObject>

#include <QDateTime>
#include <QHash>
#include <QNetworkAccessManager>

#include "downloader.h"
#include "graphqlconnector.h"
#include "restapiconnector.h"

#include "src/entities/user.h"
#include "src/entities/profilestatus.h"
#include "src/models/commentsmodel.h"
#include "src/models/discussionsmodel.h"
#include "src/models/discussioncategoriesmodel.h"
#include "src/models/discussioncommentsmodel.h"
#include "src/models/fundinglinksmodel.h"
#include "src/models/gistsmodel.h"
#include "src/models/issuesmodel.h"
#include "src/models/labelsmodel.h"
#include "src/models/notificationsmodel.h"
#include "src/models/organizationsmodel.h"
#include "src/models/pullrequestsmodel.h"
#include "src/models/releasesmodel.h"
#include "src/models/releaseassetsmodel.h"
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
    Q_PROPERTY(ProfileStatus* profileStatus READ profileStatus NOTIFY profileStatusChanged)

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
        AddDiscussionComment,
        AddReaction,
        AddStar,
        AssignUsers,
        CloseIssue,
        CreateDiscussion,
        CreateIssue,
        DeleteComment,
        DeleteDiscussionComment,
        DeleteDiscussion,
        DeleteIssue,
        FollowUser,
        GetDiscussion,
        GetFileContent,
        GetGist,
        GetIssue,
        GetLogin,
        GetModel,
        GetNotifications,
        GetOrganization,
        GetProfile,
        GetProfileStatus,
        GetPullRequest,
        GetUser,
        GetUserByLogin,
        GetRelease,
        GetReleases,
        GetReleaseAssets,
        GetRepo,
        MarkDiscussionCommentAsAnswer,
        RemoveReaction,
        RemoveStar,
        ReopenIssue,
        UnassignUser,
        UnfollowUser,
        UnmarkDiscussionCommentAsAnswer,
        UpdateComment,
        UpdateDiscussionComment,
        UpdateDiscussion,
        UpdateIssue,
        UpdateProfileStatus,
        UpdateSubscription
    };
    Q_ENUM(RequestType)

    explicit ApiInterface(QObject *parent = nullptr);

    //Q_INVOKABLE Downloader *downloader();
    void setToken(const QString &token);
    Q_INVOKABLE QString token() const;

    // api calls
    void getLogin();
    Q_INVOKABLE void addComment(const QString &body, const QString &subjectId);
    Q_INVOKABLE void addDiscussionComment(const QString &body, const QString &discussionId, const QString &replyToId = QString());
    Q_INVOKABLE void addReaction(const QString &nodeId, quint8 reaction);
    Q_INVOKABLE void addStar(const QString &nodeId);
    Q_INVOKABLE void assignUsers(const QString &nodeId, const QJsonArray &userIds);
    Q_INVOKABLE void clearProfileStatus();
    Q_INVOKABLE void closeIssue(const QString &nodeId);
    Q_INVOKABLE void createDiscussion(const QString &title, const QString &body, const QString &categoryId, DiscussionsModel *model);
    Q_INVOKABLE void createIssue(const QString &title, const QString &body, IssuesModel *model);
    Q_INVOKABLE void deleteComment(const QString &nodeId);
    Q_INVOKABLE void deleteDiscussion(const QString &nodeId);
    Q_INVOKABLE void deleteDiscussionComment(const QString &nodeId);
    Q_INVOKABLE void deleteIssue(const QString &nodeId);
    Q_INVOKABLE void followUser(const QString &nodeId, bool follow = true);
    Q_INVOKABLE void getDiscussion(const QString &nodeId);
    Q_INVOKABLE void getFileContent(const QString &nodeId, const QString &branch);
    Q_INVOKABLE void getGist(const QString &nodeId);
    Q_INVOKABLE void getIssue(const QString &nodeId);
    Q_INVOKABLE void getModel(BaseModel *model);
    Q_INVOKABLE void getNotifications(NotificationsModel *model = nullptr);
    Q_INVOKABLE void getOrganization(const QString &nodeId);
    Q_INVOKABLE void getPaginationModel(PaginationModel *model);
    Q_INVOKABLE void getProfile();
    Q_INVOKABLE void getProfileStatus();
    Q_INVOKABLE void getPullRequest(const QString &nodeId);
    Q_INVOKABLE void getRelease(const QString &nodeId);
    Q_INVOKABLE void getRepo(const QString &nodeId);
    Q_INVOKABLE void getUser(const QString &nodeId);
    Q_INVOKABLE void getUserByLogin(const QString &login);
    Q_INVOKABLE void markDiscussionCommetAsAnswer(const QString &nodeId, bool answer = true);
    Q_INVOKABLE void removeReaction(const QString &nodeId, quint8 reaction);
    Q_INVOKABLE void removeStar(const QString &nodeId);
    Q_INVOKABLE void reopenIssue(const QString &nodeId);
    Q_INVOKABLE void subscribeTo(const QString &nodeId, quint8 state);
    Q_INVOKABLE void unassignUser(const QString &nodeId, const QString &userId);
    Q_INVOKABLE void updateComment(Comment *comment);
    Q_INVOKABLE void updateDiscussion(Discussion *discussion);
    Q_INVOKABLE void updateDiscussionComment(DiscussionComment *comment);
    Q_INVOKABLE void updateIssue(Issue *issue);
    Q_INVOKABLE void updateProfileStatus(ProfileStatus *status = nullptr);
    Q_INVOKABLE void updateReactions(const QString &nodeId, quint8 before, quint8 after);

    // properties
    quint8 paginationCount() const;
    quint16 rateLimitRemaining() const;
    QDateTime rateLimitResetAt() const;
    bool ready() const;
    User *profile();
    ProfileStatus *profileStatus();

public slots:
    void setPaginationCount(quint8 paginationCount);  
    void setReady(bool ready);

signals:
    void apiError(quint8 error, const QString &msg = QString());
    void commentAdded(bool added = true);
    void commentDeleted(bool deleted = true);
    void discussionAvailable(Discussion *discussion);
    void discussionCreated(bool created = true);
    void discussionDeleted(bool deleted = true);
    void discussionCommentAdded(bool added = true);
    void discussionCommentDeleted(bool added = true);
    void discussionCommentMarkedAsAnswer(bool marked = true);
    void discussionCommentUnmarkedAsAnswer(bool unmarked = true);
    void fileContentAvailable(const QString &content);
    void gistAvailable(Gist *gist);
    void issueAvailable(Issue *issue);
    void issueClosed(bool closed = true);
    void issueCreated(bool created = true);
    void issueDeleted(bool deleted = true);
    void issueReopened(bool reopend =  true);
    void notificationsAvailable(const QList<NotificationListItem> &notifications);
    void organizationAvailable(Organization *organization);
    void profileStatusAvailable(ProfileStatus *status);
    void pullRequestAvailable(PullRequest *request);
    void releaseAvailable(Release *release);
    void repoAvailable(Repo *repo);
    void starred(const QString &nodeId, bool starred);
    void subscribedTo(const QString &nodeId, quint8 state);
    void userAvailable(User *user);
    void userFollowed(const QString &nodeId, bool following);
    void userUnassigned(bool unassigned = true);
    void usersAssigned(bool assigned = true);

    // properties
    void paginationCountChanged(quint8 count);
    void rateLimitRemainingChanged(quint16 count);
    void rateLimitResetAtChanged(const QDateTime &timestamp);
    void readyChanged(bool ready);
    void profileChanged(User *profile);
    void profileStatusChanged(ProfileStatus *status);


private slots:
    void onConnectionError(quint16 error, const QString &msg);
    void parseData(const QJsonObject &obj, quint8 requestType, const QByteArray &requestId);
    void parseRestData(const QJsonDocument &doc, quint8 requestType, const QByteArray &requestId);

private:
    void initialize();
    void parseFileContent(const QJsonObject &obj);
    void parseNotificationsModel(const QJsonArray &array, const QByteArray &requestId);
    void parseModel(const QJsonObject &obj, const QByteArray &requestId);
    void parseSubscription(const QJsonObject &obj);

    //Downloader *m_downloader{nullptr};
    GraphQLConnector *m_graphqlConnector{nullptr};
    RestApiConnector *m_restApiConnector{nullptr};

    QNetworkAccessManager *m_manager{new QNetworkAccessManager(this)};
    QHash<QByteArray, BaseModel *> m_modelRequests;
    QHash<QByteArray, NotificationsModel *> m_notificationsModelRequests;


    // properties
    quint8 m_paginationCount{20};
    quint16 m_rateLimitRemaining{0};
    QDateTime m_rateLimitResetAt;
    bool m_ready{false};
    User *m_profile{new User(this)};
    ProfileStatus *m_profileStatus{new ProfileStatus(this)};

};

#endif // APIINTERFACE_H
