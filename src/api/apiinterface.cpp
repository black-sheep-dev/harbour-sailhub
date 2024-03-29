#include "apiinterface.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QHashIterator>
#include <QJsonArray>
#include <QJsonDocument>

#include "datautils.h"
#include "keys.h"
#include "mutations.h"
#include "queries.h"
#include "queryvars.h"

#include "src/enums/enums.h"
#include "src/entities/reaction.h"



ApiInterface::ApiInterface(QObject *parent) :
    QObject(parent)
{
    //m_downloader = new Downloader(m_manager, this);
    m_graphqlConnector = new GraphQLConnector(SAILHUB_API_GRAPHQL_URL, m_manager, this);
    m_restApiConnector = new RestApiConnector(m_manager, this);

    connect(m_graphqlConnector, &GraphQLConnector::requestFinished, this, &ApiInterface::parseData);
    connect(m_graphqlConnector, &GraphQLConnector::connectionError, this, &ApiInterface::onConnectionError);

    connect(m_restApiConnector, &RestApiConnector::connectionError, this, &ApiInterface::onConnectionError);
    connect(m_restApiConnector, &RestApiConnector::requestFinished, this, &ApiInterface::parseRestData);
}

//Downloader *ApiInterface::downloader()
//{
//    return m_downloader;
//}

void ApiInterface::setToken(const QString &token)
{
    m_graphqlConnector->setToken(token);
    m_restApiConnector->setToken(token);
    initialize();
}

QString ApiInterface::token() const
{
    return m_graphqlConnector->token();
}

void ApiInterface::addComment(const QString &body, const QString &subjectId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::ADD_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, subjectId);
    vars.insert(ApiKey::BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AddComment);
}

void ApiInterface::addDiscussionComment(const QString &body, const QString &discussionId, const QString &replyToId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::ADD_DISCUSSION_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::DISCUSSION_ID, discussionId);
    vars.insert(ApiKey::BODY, body);

    if (!replyToId.isEmpty())
        vars.insert(ApiKey::REPLY_TO_ID, replyToId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AddDiscussionComment);
}

void ApiInterface::addReaction(const QString &nodeId, quint8 reaction)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::ADD_REACTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, nodeId);
    vars.insert(ApiKey::CONTENT, Reaction::content(reaction));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AddReaction);
}

void ApiInterface::addStar(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::ADD_STAR;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::STARRABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AddStar, getNodeRequestId(nodeId));
}

void ApiInterface::assignUsers(const QString &nodeId, const QJsonArray &userIds)
{
    if (userIds.isEmpty())
        return;

    GraphQLQuery query;
    query.query = Mutation::ASSIGN_USERS_TO_ASSIGNABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ASSIGNABLE_ID, nodeId);
    vars.insert(ApiKey::ASSIGNEE_IDS, userIds);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AssignUsers);
}

void ApiInterface::clearProfileStatus()
{
    m_profileStatus->setExpiresAt(QDateTime(QDate(2000,1,1)));

    updateProfileStatus(m_profileStatus);
}

void ApiInterface::closeIssue(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::CLOSE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ISSUE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::CloseIssue, getNodeRequestId(nodeId));
}

void ApiInterface::closePullRequest(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::CLOSE_PULL_REQUEST;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::PULL_REQUEST_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::ClosePullRequest, getNodeRequestId(nodeId));
}

void ApiInterface::createDiscussion(const QString &title, const QString &body, const QString &categoryId, DiscussionsModel *model)
{
    if (m_profile == nullptr || model == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::CREATE_DISCUSSION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::REPOSITORY_ID, model->identifier());
    vars.insert(ApiKey::CATEGORY_ID, categoryId);
    vars.insert(ApiKey::TITLE, title);

    if (!body.isEmpty())
        vars.insert(ApiKey::BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::CreateDiscussion);
}

void ApiInterface::createIssue(const QString &title, const QString &body, IssuesModel *model)
{
    if (m_profile == nullptr || model == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::CREATE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::REPOSITORY_ID, model->identifier());
    vars.insert(ApiKey::TITLE, title);

    if (!body.isEmpty())
        vars.insert(ApiKey::BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::CreateIssue);
}

void ApiInterface::deleteComment(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::DELETE_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::DeleteComment);
}

void ApiInterface::deleteDiscussion(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::DELETE_DISCUSSION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::DeleteDiscussion);
}

void ApiInterface::deleteDiscussionComment(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::DELETE_DISCUSSION_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::DeleteDiscussionComment);
}

void ApiInterface::deleteIssue(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::DELETE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ISSUE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::DeleteIssue);
}

void ApiInterface::followUser(const QString &nodeId, bool follow)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = follow ? Mutation::FOLLOW_USER : Mutation::UNFOLLOW_USER;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::USER_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, follow ? RequestType::FollowUser : RequestType::UnfollowUser);
}

void ApiInterface::getCommit(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_COMMIT;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetCommit);
}

void ApiInterface::getDiscussion(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_DISCUSSION;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetDiscussion);
}

void ApiInterface::getFileContent(const QString &nodeId, const QString &branch)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_FILE_CONTENT;
    query.variables.insert(QueryVar::NODE_ID, nodeId);
    query.variables.insert(QueryVar::BRANCH, branch);

    m_graphqlConnector->sendQuery(query, RequestType::GetFileContent);
}

void ApiInterface::getGist(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_GIST;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetGist);
}

void ApiInterface::getIssue(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ISSUE;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetIssue);
}

void ApiInterface::getModel(BaseModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query = model->query();
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    model->setLoading(true);

    // save and send
    const QByteArray uuid = model->uuid();
    m_modelRequests.insert(uuid, model);
    m_graphqlConnector->sendQuery(query, RequestType::GetModel, uuid);
}

void ApiInterface::getNotifications(NotificationsModel *model)
{
    if (model != nullptr) {
        model->setLoading(true);

        // save and send
        m_notificationsModelRequests.insert(model->uuid(), model);
        m_restApiConnector->get(QStringLiteral("/notifications?all=false"),
                                RequestType::GetNotifications,
                                model->uuid());
    } else {
        // only unreaded notifications
        m_restApiConnector->get(QStringLiteral("/notifications"),
                                RequestType::GetNotifications);
    }
}

void ApiInterface::getOrganization(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ORGANIZATION;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetOrganization);
}

void ApiInterface::getPaginationModel(PaginationModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query = model->query();
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    model->setLoading(true);

    // save and send
    const QByteArray uuid = model->uuid();
    m_modelRequests.insert(uuid, model);
    m_graphqlConnector->sendQuery(query, RequestType::GetModel, uuid);
}

void ApiInterface::getProfile()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_VIEWER_PROFILE;

    m_graphqlConnector->sendQuery(query, RequestType::GetProfile);
}

void ApiInterface::getProfileStatus()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_PROFILE_STATUS;

    m_graphqlConnector->sendQuery(query, RequestType::GetProfileStatus);
}

void ApiInterface::getPullRequest(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_PULL_REQUEST;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetPullRequest);
}

void ApiInterface::getRelease(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_RELEASE;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetRelease);
}

void ApiInterface::getRepo(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY.arg(SAILHUB_QUERY_ITEM_REPO);
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetRepo);
}

void ApiInterface::getRepo(const QString &username, const QString &reponame)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_BY_NAME.arg(SAILHUB_QUERY_ITEM_REPO);
    query.variables.insert(QueryVar::OWNER, username);
    query.variables.insert(QueryVar::NAME, reponame);

    m_graphqlConnector->sendQuery(query, RequestType::GetRepoByName);
}

void ApiInterface::getRepoId(const QString &username, const QString &reponame)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_BY_NAME.arg(SAILHUB_QUERY_ITEM_REPO);
    query.variables.insert(QueryVar::OWNER, username);
    query.variables.insert(QueryVar::NAME, reponame);

    m_graphqlConnector->sendQuery(query, RequestType::GetRepoId);
}

void ApiInterface::getUser(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER.arg(SAILHUB_QUERY_ITEM_USER);
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetUser);
}

void ApiInterface::getUserByLogin(const QString &login)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER_BY_LOGIN.arg(SAILHUB_QUERY_ITEM_USER);
    query.variables.insert(QueryVar::USER_LOGIN, login);

    m_graphqlConnector->sendQuery(query, RequestType::GetUserByLogin);
}

void ApiInterface::lock(const QString &nodeId, quint8 reason)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::LOCK_LOCKABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    if (reason != LockReason::Unknown)
        vars.insert(ApiKey::LOCK_REASON, LockReason::toString(reason));
    vars.insert(ApiKey::LOCKABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::Lock, getNodeRequestId(nodeId));
}

void ApiInterface::markDiscussionCommetAsAnswer(const QString &nodeId, bool answer)
{
    GraphQLQuery query;

    if (answer) {
        query.query = Mutation::MARK_DISCUSSION_COMMENT_AS_ANSWER;
    } else {
        query.query = Mutation::UNMARK_DISCUSSION_COMMENT_AS_ANSWER;
    }

    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, answer ? RequestType::MarkDiscussionCommentAsAnswer : RequestType::UnmarkDiscussionCommentAsAnswer);
}

void ApiInterface::removeReaction(const QString &nodeId, quint8 reaction)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::REMOVE_REACTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, nodeId);
    vars.insert(ApiKey::CONTENT, Reaction::content(reaction));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::RemoveReaction);
}

void ApiInterface::removeStar(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::REMOVE_STAR;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::STARRABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::RemoveStar, getNodeRequestId(nodeId));
}

void ApiInterface::reopenIssue(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::REOPEN_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ISSUE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::ReopenIssue, getNodeRequestId(nodeId));
}

void ApiInterface::reopenPullRequest(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::REOPEN_PULL_REQUEST;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::PULL_REQUEST_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::ReopenPullRequest, getNodeRequestId(nodeId));
}

void ApiInterface::subscribeTo(const QString &nodeId, quint8 state)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPATE_SUBSCRIPTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBSCRIBABLE_ID, nodeId);
    vars.insert(ApiKey::STATE, SubscriptionState::toString(state));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateSubscription);
}

void ApiInterface::unassignUser(const QString &nodeId, const QString &userId)
{
    GraphQLQuery query;
    query.query = Mutation::UNASSIGN_USERS_FROM_ASSIGNABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ASSIGNABLE_ID, nodeId);
    vars.insert(ApiKey::ASSIGNEE_IDS, QJsonArray() << userId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UnassignUser);
}

void ApiInterface::unlock(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UNLOCK_LOCKABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::LOCKABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::Unlock, getNodeRequestId(nodeId));
}

void ApiInterface::updateComment(Comment *comment)
{
    if (comment == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPDATE_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::ID, comment->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::BODY, comment->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateComment);
}

void ApiInterface::updateDiscussion(Discussion *discussion)
{
    if (discussion == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPDATE_DISCUSSION;

    QJsonObject vars;
    vars.insert(ApiKey::DISCUSSION_ID, discussion->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::TITLE, discussion->title());
    vars.insert(ApiKey::BODY, discussion->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateDiscussion);
}

void ApiInterface::updateDiscussionComment(DiscussionComment *comment)
{
    if (comment == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPDATE_DISCUSSION_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::COMMENT_ID, comment->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::BODY, comment->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateDiscussionComment);
}

void ApiInterface::updateIssue(Issue *issue)
{
    if (issue == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPDATE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::ID, issue->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::TITLE, issue->title());
    vars.insert(ApiKey::BODY, issue->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateIssue);
}

void ApiInterface::updatePullRequest(PullRequest *request)
{
    if (request == nullptr)
        return;

    GraphQLQuery query;
    query.query = Mutation::UPDATE_PULL_REQUEST;

    QJsonObject vars;
    vars.insert(ApiKey::PULL_REQUEST_ID, request->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::TITLE, request->title());
    vars.insert(ApiKey::BODY, request->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdatePullRequest);
}

void ApiInterface::updateProfileStatus(ProfileStatus *status)
{
    if (status == nullptr)
        status = m_profileStatus;

    GraphQLQuery query;
    query.query = Mutation::CHANGE_PROFILE_STATUS;

    QJsonObject vars;

    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());

    if (!status->emoji().isEmpty())
        vars.insert(ApiKey::EMOJI, status->emoji());

    if (status->expiresAt().isValid())
        vars.insert(ApiKey::EXPIRES_AT, status->expiresAt().toString(Qt::ISODate));

    vars.insert(ApiKey::LIMITED_AVAILABILITY, status->indicatesLimitedAvailability());

    if (!status->message().isEmpty())
        vars.insert(ApiKey::MESSAGE, status->message());

    if (!status->organizationId().isEmpty())
        vars.insert(ApiKey::ORGANIZATION_ID, status->organizationId());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateProfileStatus);
}

void ApiInterface::updateReactions(const QString &nodeId, quint8 before, quint8 after)
{
    quint8 flag{1};

    for (int i = 0; i < 8; ++i) {

        if ( (before & flag) == (after & flag)) {
            flag *= 2;
            continue;
        }

        if (after & flag)
            addReaction(nodeId, flag);
        else
            removeReaction(nodeId, flag);

        flag *= 2;
    }
}

quint8 ApiInterface::paginationCount() const
{
    return m_paginationCount;
}

quint16 ApiInterface::rateLimitRemaining() const
{
    return m_rateLimitRemaining;
}

const QDateTime &ApiInterface::rateLimitResetAt() const
{
    return m_rateLimitResetAt;
}

bool ApiInterface::ready() const
{
    return m_ready;
}

User *ApiInterface::profile()
{
    return m_profile;
}

ProfileStatus *ApiInterface::profileStatus()
{
    return m_profileStatus;
}

void ApiInterface::setPaginationCount(quint8 paginationCount)
{
    if (m_paginationCount == paginationCount)
        return;

    m_paginationCount = paginationCount;
    emit paginationCountChanged(m_paginationCount);
}

void ApiInterface::setReady(bool ready)
{
    if (m_ready == ready)
        return;

    m_ready = ready;
    emit readyChanged(m_ready);
}

void ApiInterface::onConnectionError(quint16 error, const QString &msg, const QByteArray &requestId)
{
#ifdef QT_DEBUG
    qDebug() << error;
    qDebug() << msg;
#endif

    switch (error) {
    case QNetworkReply::TimeoutError:
        emit apiError(ErrorTimeout, msg);
        break;

    case QNetworkReply::AuthenticationRequiredError:
        emit apiError(ErrorUnauthorized, msg);
        break;

    case QNetworkReply::ServiceUnavailableError:
        emit apiError(ErrorServerUnavailable, msg);
        break;

    default:
        break;
    }

    // cleanup
    m_nodeRequests.take(requestId);
    m_modelRequests.take(requestId);
}

void ApiInterface::parseData(const QJsonObject &obj, quint8 requestType, const QByteArray &requestId)
{
#ifdef QT_DEBUG
    qDebug() << requestType;
    qDebug() << obj;
#endif

    const QJsonObject data = obj.value(ApiKey::DATA).toObject();

    // get rateLimit
    const QJsonObject rateLimit = obj.value(ApiKey::RATE_LIMIT).toObject();
    if (!rateLimit.isEmpty()) {
        m_rateLimitRemaining = rateLimit.value(ApiKey::REMAINING).toInt();
        emit rateLimitRemainingChanged(m_rateLimitRemaining);
        m_rateLimitResetAt = QDateTime::fromString(rateLimit.value(ApiKey::RESET_AT).toString());
        emit rateLimitResetAtChanged(m_rateLimitResetAt);
    }

    switch (requestType) {
    case RequestType::GetUser:
        emit userAvailable(new User(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetUserByLogin:
        emit userAvailable(new User(data.value(ApiKey::USER).toObject()));
        break;

    case RequestType::GetRepo:
        emit repoAvailable(new Repo(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetRepoId:
        emit repoIdAvailable(new Repo(data.value(ApiKey::REPOSITORY).toObject()));
        break;

    case RequestType::GetRepoByName:
        emit repoAvailable(new Repo(data.value(ApiKey::REPOSITORY).toObject()));
        emit repoByNameAvailable(new Repo(data.value(ApiKey::REPOSITORY).toObject()));
        break;

    case RequestType::GetRelease:
        emit releaseAvailable(new Release(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetModel:
        parseModel(data, requestId);
        break;

    case RequestType::GetOrganization:
        emit organizationAvailable(new Organization(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetIssue:
        emit issueAvailable(new Issue(data.value(ApiKey::NODE).toObject()));
        break;     

    case RequestType::GetPullRequest:
        emit pullRequestAvailable(new PullRequest(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetDiscussion:
        emit discussionAvailable(new Discussion(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetCommit:
        emit commitAvailable(new Commit(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetGist:
        emit gistAvailable(new Gist(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::AddComment:
        emit commentAdded();
        break;

    case RequestType::AddDiscussionComment:
        emit discussionCommentAdded();
        break;

    case RequestType::CreateDiscussion:
        emit discussionCreated();
        break;

    case RequestType::CreateIssue:
        emit issueCreated();
        break; 

    case RequestType::AddStar:
        emit starred(m_nodeRequests.take(requestId), true);
        break;

    case RequestType::RemoveStar:
        emit starred(m_nodeRequests.take(requestId), false);
        break;

    case RequestType::FollowUser:
        emit userFollowed(data.value(ApiKey::FOLLOWER_USER).toObject()
                              .value(ApiKey::USER).toObject()
                              .value(ApiKey::ID).toString(), true);
        break;

    case RequestType::UnfollowUser:
        emit userFollowed(data.value(ApiKey::UNFOLLOW_USER).toObject()
                              .value(ApiKey::USER).toObject()
                              .value(ApiKey::ID).toString(), false);
        break;

    case RequestType::UpdateSubscription:
        parseSubscription(data);
        break;

    case RequestType::GetFileContent:
        parseFileContent(data);
        break;

    case RequestType::GetProfile:
        m_profile->setData(data.value(ApiKey::VIEWER).toObject());
        emit profileChanged(m_profile);
        setReady(true);
        break;

    case RequestType::GetProfileStatus:
        m_profileStatus->setData(data.value(ApiKey::VIEWER).toObject()
                                 .value(ApiKey::STATUS).toObject());
        emit profileStatusChanged(m_profileStatus);
        break;

    case RequestType::UpdateProfileStatus:
        m_profileStatus->setData(data.value(ApiKey::CHANGE_USER_STATUS).toObject()
                                 .value(ApiKey::STATUS).toObject());
        emit profileStatusChanged(m_profileStatus);
        break;

    case RequestType::AssignUsers:
        emit usersAssigned();
        break;

    case RequestType::UnassignUser:
        emit userUnassigned();
        break;

    case RequestType::CloseIssue:
        emit issueClosed(m_nodeRequests.take(requestId));
        break;

    case RequestType::ClosePullRequest:
        emit pullRequestClosed(m_nodeRequests.take(requestId));
        break;

    case RequestType::ReopenIssue:
        emit issueReopened(m_nodeRequests.take(requestId));
        break;

    case RequestType::ReopenPullRequest:
        emit pullRequestReopened(m_nodeRequests.take(requestId));
        break;

    case RequestType::DeleteComment:
        emit commentDeleted();
        break;

    case RequestType::DeleteDiscussionComment:
        emit discussionCommentDeleted();
        break;

    case RequestType::MarkDiscussionCommentAsAnswer:
        emit discussionCommentMarkedAsAnswer();
        break;

    case RequestType::UnmarkDiscussionCommentAsAnswer:
        emit discussionCommentUnmarkedAsAnswer();
        break;

    case RequestType::DeleteDiscussion:
        emit discussionDeleted();
        break;

    case RequestType::DeleteIssue:
        emit issueDeleted();
        break;

    case RequestType::Lock:
        emit locked(m_nodeRequests.take(requestId),
                    data.value(ApiKey::LOCK_LOCKABLE).toObject()
                    .value(ApiKey::LOCKED_RECORD).toObject()
                    .value(ApiKey::LOCKED).toBool());
        break;

    case RequestType::Unlock:
        emit locked(m_nodeRequests.take(requestId),
                    data.value(ApiKey::UNLOCK_LOCKABLE).toObject()
                    .value(ApiKey::LOCKED_RECORD).toObject()
                    .value(ApiKey::LOCKED).toBool());
        break;

    default:
        break;
    }
}

void ApiInterface::parseRestData(const QJsonDocument &doc, quint8 requestType, const QByteArray &requestId)
{
#ifdef QT_DEBUG
    qDebug() << requestType;
    qDebug() << doc;
#endif

    switch (requestType) {
    case GetNotifications:
        parseNotificationsModel(doc.array(), requestId);
        break;

    default:
        break;
    }
}

QByteArray ApiInterface::getNodeRequestId(const QString &nodeId)
{
    const QByteArray uuid = QUuid::createUuid().toByteArray();
    m_nodeRequests.insert(uuid, nodeId);

    return uuid;
}

void ApiInterface::initialize()
{
    getProfile();
    getProfileStatus();
}

void ApiInterface::parseFileContent(const QJsonObject &obj)
{
    const QJsonObject data = obj.value(ApiKey::NODE).toObject()
            .value(ApiKey::OBJECT).toObject();

    if (data.value(ApiKey::IS_BINARY).toBool())
        return;

    emit fileContentAvailable(data.value(ApiKey::TEXT).toString());
}

void ApiInterface::parseNotificationsModel(const QJsonArray &array, const QByteArray &requestId)
{
    // check notifications for unread ones
    const QList<NotificationListItem> items = DataUtils::notificationsFromJson(array);
    emit notificationsAvailable(items);

    // update model
    auto model = m_notificationsModelRequests.value(requestId, nullptr);

    if (model == nullptr) {
        return;
    }

    // parse data
    model->setNotifications(items);

    // cleanup
    m_notificationsModelRequests.remove(requestId);
}

void ApiInterface::parseModel(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = m_modelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // parse data
    model->parseQueryResult(obj);

    // cleanup
    m_modelRequests.remove(requestId);
}

void ApiInterface::parseSubscription(const QJsonObject &obj)
{
    const QJsonObject subscription = obj.value(ApiKey::UPDATE_SUBSCRIPTION).toObject()
                                        .value(ApiKey::SUBSCRIBABLE).toObject();

    const QString state = subscription.value(ApiKey::VIEWER_SUBSCRIPTION).toString();

    emit subscribedTo(subscription.value(ApiKey::ID).toString(), SubscriptionState::fromString(state));
}
