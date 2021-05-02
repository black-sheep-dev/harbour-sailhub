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
    query.query = SAILHUB_MUTATION_ADD_COMMENT;

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
    query.query = SAILHUB_MUTATION_ADD_DISCUSSION_COMMENT;

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
    query.query = SAILHUB_MUTATION_ADD_REACTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, nodeId);
    vars.insert(ApiKey::CONTENT, Reaction::content(reaction));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AddReaction);
}

void ApiInterface::assignUsers(const QString &nodeId, const QJsonArray &userIds)
{
    if (userIds.isEmpty())
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_ASSIGN_USERS_TO_ASSIGNABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ASSIGNABLE_ID, nodeId);
    vars.insert(ApiKey::ASSIGNEE_IDS, userIds);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::AssignUsers);
}

void ApiInterface::closeIssue(const QString &nodeId)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_CLOSE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ISSUE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::CloseIssue);
}

void ApiInterface::createDiscussion(const QString &title, const QString &body, const QString &categoryId, DiscussionsModel *model)
{
    if (m_profile == nullptr || model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_CREATE_DISCUSSION;

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
    query.query = SAILHUB_MUTATION_CREATE_ISSUE;

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
    query.query = SAILHUB_MUTATION_DELETE_COMMENT;

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
    query.query = SAILHUB_MUTATION_DELETE_DISCUSSION;

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
    query.query = SAILHUB_MUTATION_DELETE_DISCUSSION_COMMENT;

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
    query.query = SAILHUB_MUTATION_DELETE_ISSUE;

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
    query.query = follow ? SAILHUB_MUTATION_FOLLOW_USER : SAILHUB_MUTATION_UNFOLLOW_USER;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::USER_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, follow ? RequestType::FollowUser : RequestType::UnfollowUser);
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
    query.query = SAILHUB_QUERY_GET_REPOSITORY;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetRepo);
}

void ApiInterface::getUser(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, RequestType::GetUser);
}

void ApiInterface::getUserByLogin(const QString &login)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER_BY_LOGIN;
    query.variables.insert(QueryVar::USER_LOGIN, login);

    m_graphqlConnector->sendQuery(query, RequestType::GetUserByLogin);
}

void ApiInterface::markDiscussionCommetAsAnswer(const QString &nodeId, bool answer)
{
    GraphQLQuery query;

    if (answer) {
        query.query = SAILHUB_MUTATION_MARK_DISCUSSION_COMMENT_AS_ANSWER;
    } else {
        query.query = SAILHUB_MUTATION_UNMARK_DISCUSSION_COMMENT_AS_ANSWER;
    }

    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_graphqlConnector->sendQuery(query, answer ? RequestType::MarkDiscussionCommentAsAnswer : RequestType::UnmarkDiscussionCommentAsAnswer);
}

void ApiInterface::starRepo(const QString &nodeId, bool star)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = star ? SAILHUB_MUTATION_REPO_ADD_STAR : SAILHUB_MUTATION_REPO_REMOVE_STAR;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::STARRABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, star ? RequestType::StarRepo : RequestType::UnstarRepo);
}

void ApiInterface::removeReaction(const QString &nodeId, quint8 reaction)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_REMOVE_REACTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, nodeId);
    vars.insert(ApiKey::CONTENT, Reaction::content(reaction));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::RemoveReaction);
}

void ApiInterface::subscribeToRepo(const QString &nodeId, quint8 state)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_REPO_UPATE_SUBSCRIPTION;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBSCRIBABLE_ID, nodeId);
    vars.insert(ApiKey::STATE, SubscriptionState::toString(state));

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateRepoSubscription);
}

void ApiInterface::unassignUser(const QString &nodeId, const QString &userId)
{
    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_UNASSIGN_USERS_FROM_ASSIGNABLE;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::ASSIGNABLE_ID, nodeId);
    vars.insert(ApiKey::ASSIGNEE_IDS, QJsonArray() << userId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UnassignUser);
}

void ApiInterface::updateComment(Comment *comment)
{
    if (comment == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_UPDATE_COMMENT;

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
    query.query = SAILHUB_MUTATION_UPDATE_DISCUSSION;

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
    query.query = SAILHUB_MUTATION_UPDATE_DISCUSSION_COMMENT;

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
    query.query = SAILHUB_MUTATION_UPDATE_ISSUE;

    QJsonObject vars;
    vars.insert(ApiKey::ID, issue->nodeId());
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::TITLE, issue->title());
    vars.insert(ApiKey::BODY, issue->body());

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_graphqlConnector->sendQuery(query, RequestType::UpdateIssue);
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

QDateTime ApiInterface::rateLimitResetAt() const
{
    return m_rateLimitResetAt;
}

bool ApiInterface::ready() const
{
    return m_ready;
}

User *ApiInterface::profile() const
{
    return m_profile;
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

void ApiInterface::onConnectionError(quint16 error, const QString &msg)
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
        emit userAvailable(DataUtils::userFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetUserByLogin:
        emit userAvailable(DataUtils::userFromJson(data.value(ApiKey::USER).toObject()));
        break;

    case RequestType::GetRepo:
        emit repoAvailable(DataUtils::repoFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetRelease:
        emit releaseAvailable(DataUtils::releaseFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetModel:
        parseModel(data, requestId);
        break;

    case RequestType::GetOrganization:
        emit organizationAvailable(DataUtils::organizationFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetIssue:
        emit issueAvailable(DataUtils::issueFromJson(data.value(ApiKey::NODE).toObject()));
        break;     

    case RequestType::GetPullRequest:
        emit pullRequestAvailable(DataUtils::pullRequestFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetDiscussion:
        emit discussionAvailable(DataUtils::discussionFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetGist:
        emit gistAvailable(DataUtils::gistFromJson(data.value(ApiKey::NODE).toObject()));
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

    case RequestType::StarRepo:
        emit repoStarred(data.value(ApiKey::ADD_STAR).toObject()
                             .value(ApiKey::STARRABLE).toObject()
                             .value(ApiKey::ID).toString(), true);
        break;

    case RequestType::UnstarRepo:
        emit repoStarred(data.value(ApiKey::REMOVE_STAR).toObject()
                             .value(ApiKey::STARRABLE).toObject()
                             .value(ApiKey::ID).toString(), false);
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

    case RequestType::UpdateRepoSubscription:
        parseRepoSubscription(data);
        break;

    case RequestType::GetFileContent:
        parseFileContent(data);
        break;

    case RequestType::GetProfile:
        emit profileChanged(DataUtils::userFromJson(data.value(ApiKey::VIEWER).toObject(), m_profile));
        setReady(true);
        break;

    case RequestType::AssignUsers:
        emit usersAssigned();
        break;

    case RequestType::UnassignUser:
        emit userUnassigned();
        break;

    case RequestType::CloseIssue:
        emit issueClosed();
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

void ApiInterface::initialize()
{
    getProfile();
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

    QList<NotificationListItem> unreaded;
    for (const auto &item : items) {
        if (!item.unread)
            continue;

        unreaded.append(item);
    }

    if (!unreaded.isEmpty())
        emit notificationsAvailable(unreaded);


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

void ApiInterface::parseRepoSubscription(const QJsonObject &obj)
{
    const QJsonObject subscription = obj.value(ApiKey::UPDATE_SUBSCRIPTION).toObject()
                                        .value(ApiKey::SUBSCRIBABLE).toObject();

    const QString state = subscription.value(ApiKey::VIEWER_SUBSCRIPTION).toString();

    quint8 value = SubscriptionState::fromString(state);

    emit subscribedToRepo(subscription.value(ApiKey::ID).toString(), value);
}
