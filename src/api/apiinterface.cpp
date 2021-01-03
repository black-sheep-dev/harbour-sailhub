#include "apiinterface.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QHashIterator>
#include <QJsonArray>

#include "datautils.h"
#include "keys.h"
#include "mutations.h"
#include "queries.h"

ApiInterface::ApiInterface(QObject *parent) :
    QObject(parent)
{
    connect(m_connector, &GraphQLConnector::requestFinished, this, &ApiInterface::parseData);
    connect(m_connector, &GraphQLConnector::connectionError, this, &ApiInterface::onConnectionError);
}

void ApiInterface::setToken(const QString &token)
{
    m_connector->setToken(token);
    initialize();
}

QString ApiInterface::token() const
{
    return m_connector->token();
}

void ApiInterface::createIssue(const QString &title, const QString &body, IssuesModel *model)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_ADD_ISSUE;

    QJsonObject vars;
    vars.insert(SAILHUB_API_KEY_CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(SAILHUB_API_KEY_REPOSITORY_ID, model->identifier());
    vars.insert(SAILHUB_API_KEY_TITLE, title);

    if (!body.isEmpty())
        vars.insert(SAILHUB_API_KEY_BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    const QByteArray uuid = model->uuid();
    m_issuesModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::CreateIssue, uuid);
}

void ApiInterface::followUser(const QString &nodeId, bool follow)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = follow ? SAILHUB_MUTATION_FOLLOW_USER : SAILHUB_MUTATION_UNFOLLOW_USER;

    QJsonObject vars;
    vars.insert(SAILHUB_API_KEY_CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(SAILHUB_API_KEY_USER_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_connector->sendQuery(query, follow ? RequestType::FollowUser : RequestType::UnfollowUser);
}

void ApiInterface::getComments(CommentsModel *model)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ISSUE_COMMENTS;

    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, model->identifier());
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send

    const QByteArray uuid = model->uuid();
    m_commentsModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetIssues, uuid);
}

void ApiInterface::getIssue(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ISSUE;
    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetIssue);
}

void ApiInterface::getIssues(IssuesModel *model)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_ISSUES;

    const quint8 state = model->modelType();

    if (state == 0)
        return;

    QJsonArray states;
    if (state & Issue::StateOpen)
        states.append(QStringLiteral("OPEN"));
    if (state & Issue::StateClosed)
        states.append(QStringLiteral("CLOSED"));
    query.variables.insert(SAILHUB_QUERY_VAR_STATES, states);

    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, model->identifier());
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send

    const QByteArray uuid = model->uuid();
    m_issuesModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetIssues, uuid);
}

void ApiInterface::getProfile()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_VIEWER_PROFILE;

    m_connector->sendQuery(query, RequestType::GetProfile);
}

void ApiInterface::getRepo(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY;
    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetRepo);
}

void ApiInterface::getRepos(ReposModel *model)
{
    GraphQLQuery query;
    const quint8 repoType = model->modelType();

    switch (repoType) {
    case Repo::User:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES;
        break;

    case Repo::Fork:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_FORKS;
        break;

    case Repo::Starred:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES_STARRED;
        break;

    default:
        break;
    }

    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, model->identifier());
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send

    const QByteArray uuid = model->uuid();
    m_reposModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetRepos, uuid);
}

void ApiInterface::getUser(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER;
    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetUser);
}

void ApiInterface::getUsers(UsersModel *model)
{
    GraphQLQuery query;

    switch (model->modelType()) {
    case User::Follower:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWERS;
        break;

    case User::Following:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWING;
        break;

    case User::Contributor:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS;
        break;

    case User::Stargazer:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS;
        break;

    case User::Watcher:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_WATCHERS;
        break;

    default:
        break;
    }

    query.variables.insert(SAILHUB_QUERY_VAR_NODE_ID, model->identifier());
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if cursor available insert it
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send
    const QByteArray uuid = model->uuid();
    m_usersModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetUsers, uuid);
}

void ApiInterface::searchRepo(const QString &pattern, ReposModel *model)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_SEARCH_REPOSITORY;
    query.variables.insert(SAILHUB_QUERY_VAR_QUERY_STRING, pattern);
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    const QByteArray uuid = model->uuid();
    m_reposModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::SearchRepo, uuid);
}

void ApiInterface::searchUser(const QString &pattern, UsersModel *model)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_SEARCH_USER;
    query.variables.insert(SAILHUB_QUERY_VAR_QUERY_STRING, pattern);
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(SAILHUB_QUERY_VAR_ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    const QByteArray uuid = model->uuid();
    m_usersModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::SearchUser, uuid);
}

void ApiInterface::starRepo(const QString &nodeId, bool star)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = star ? SAILHUB_MUTATION_REPO_ADD_STAR : SAILHUB_MUTATION_REPO_REMOVE_STAR;

    QJsonObject vars;
    vars.insert(SAILHUB_API_KEY_CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(SAILHUB_API_KEY_STARRABLE_ID, nodeId);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_connector->sendQuery(query, star ? RequestType::StarRepo : RequestType::UnstarRepo);
}

void ApiInterface::subscribeToRepo(const QString &nodeId, quint8 state)
{
    if (m_profile == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_REPO_UPATE_SUBSCRIPTION;

    QJsonObject vars;
    vars.insert(SAILHUB_API_KEY_CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(SAILHUB_API_KEY_SUBSCRIBABLE_ID, nodeId);

    switch (state) {
    case Repo::SubscriptionIgnored:
        vars.insert(SAILHUB_API_KEY_STATE, QStringLiteral("IGNORED"));
        break;

    case Repo::Subscribed:
        vars.insert(SAILHUB_API_KEY_STATE, QStringLiteral("SUBSCRIBED"));
        break;

    case Repo::Unsubscribed:
        vars.insert(SAILHUB_API_KEY_STATE, QStringLiteral("UNSUBSCRIBED"));
        break;

    default:
        break;
    }

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_connector->sendQuery(query, RequestType::UpdateRepoSubscription);
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

    const QJsonObject data = obj.value(SAILHUB_API_KEY_DATA).toObject();

    // get rateLimit
    const QJsonObject rateLimit = obj.value(SAILHUB_API_KEY_RATE_LIMIT).toObject();
    if (!rateLimit.isEmpty()) {
        m_rateLimitRemaining = rateLimit.value(SAILHUB_API_KEY_REMAINING).toInt();
        emit rateLimitRemainingChanged(m_rateLimitRemaining);
        m_rateLimitResetAt = QDateTime::fromString(rateLimit.value(SAILHUB_API_KEY_RESET_AT).toString());
        emit rateLimitResetAtChanged(m_rateLimitResetAt);
    }

    switch (requestType) {
    case RequestType::GetUser:
        emit userAvailable(DataUtils::userFromJson(data.value(SAILHUB_API_KEY_NODE).toObject()));
        break;

    case RequestType::GetUsers:
    case RequestType::SearchUser:
        parseUsers(data, requestId);
        break;

    case RequestType::GetRepo:
        emit repoAvailable(DataUtils::repoFromJson(data.value(SAILHUB_API_KEY_NODE).toObject()));
        break;

    case RequestType::GetRepos:
    case RequestType::SearchRepo:
        parseRepos(data, requestId);
        break;

    case RequestType::GetIssue:
        emit issueAvailable(DataUtils::issueFromJson(data.value(SAILHUB_API_KEY_NODE).toObject()));
        break;

    case RequestType::GetIssues:
        parseIssues(data, requestId);
        break;

    case RequestType::CreateIssue:
        emit issueCreated(DataUtils::issueFromJson(data.value(SAILHUB_API_KEY_NODE).toObject()));
        break;

    case RequestType::GetComments:
        parseComments(data, requestId);
        break;

    case StarRepo:
        emit repoStarred(data.value(SAILHUB_API_KEY_ADD_STAR).toObject()
                             .value(SAILHUB_API_KEY_STARRABLE).toObject()
                             .value(SAILHUB_API_KEY_ID).toString(), true);
        break;

    case UnstarRepo:
        emit repoStarred(data.value(SAILHUB_API_KEY_REMOVE_STAR).toObject()
                             .value(SAILHUB_API_KEY_STARRABLE).toObject()
                             .value(SAILHUB_API_KEY_ID).toString(), false);
        break;

    case FollowUser:
        emit userFollowed(data.value(SAILHUB_API_KEY_FOLLOWER_USER).toObject()
                              .value(SAILHUB_API_KEY_USER).toObject()
                              .value(SAILHUB_API_KEY_ID).toString(), true);
        break;

    case UnfollowUser:
        emit userFollowed(data.value(SAILHUB_API_KEY_UNFOLLOW_USER).toObject()
                              .value(SAILHUB_API_KEY_USER).toObject()
                              .value(SAILHUB_API_KEY_ID).toString(), false);
        break;

    case UpdateRepoSubscription:
        parseRepoSubscription(data);
        break;

    case GetProfile:
        emit profileChanged(DataUtils::userFromJson(data.value(SAILHUB_API_KEY_VIEWER).toObject(), m_profile));
        setReady(true);
        break;

    default:
        break;
    }
}

void ApiInterface::initialize()
{
    getProfile();
}

void ApiInterface::parseComments(const QJsonObject &obj, const QByteArray &requestId)
{
    CommentsModel *model = m_commentsModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // get identifier and comments
    const QJsonObject comments = obj.value(SAILHUB_API_KEY_NODE).toObject()
                                  .value(SAILHUB_API_KEY_COMMENTS).toObject();
    const QJsonValue count = comments.value(SAILHUB_API_KEY_TOTAL_COUNT);

    model->setPageInfo(DataUtils::pageInfoFromJson(comments, count));
    model->addComments(DataUtils::commentsFromJson(comments));
    model->setLoading(false);

    // cleanup
    m_commentsModelRequests.remove(requestId);
}

void ApiInterface::parseIssues(const QJsonObject &obj, const QByteArray &requestId)
{
    IssuesModel *model = m_issuesModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // get identifier and repos

    const QJsonObject issues = obj.value(SAILHUB_API_KEY_NODE).toObject()
                                  .value(SAILHUB_API_KEY_ISSUES).toObject();
    const QJsonValue count = issues.value(SAILHUB_API_KEY_TOTAL_COUNT);

    model->setPageInfo(DataUtils::pageInfoFromJson(issues, count));
    model->addIssues(DataUtils::issuesFromJson(issues));
    model->setLoading(false);

    // cleanup
    m_issuesModelRequests.remove(requestId);
}

void ApiInterface::parseRepos(const QJsonObject &obj, const QByteArray &requestId)
{
    ReposModel *model = m_reposModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // get identifier and repos
    QJsonValue count;
    QJsonObject repos;

    switch (model->modelType()) {
    case Repo::User:
        repos = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_REPOSITORIES).toObject();
        count = repos.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case Repo::Fork:
        repos = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_FORKS).toObject();
        count = repos.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case Repo::Search:
        repos = obj.value(SAILHUB_API_KEY_SEARCH).toObject();
        count = repos.value(SAILHUB_API_KEY_REPOSITORY_COUNT);
        break;

    case Repo::Starred:
        repos = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_STARRED_REPOSITORIES).toObject();
        count = repos.value(SAILHUB_API_KEY_REPOSITORY_COUNT);
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(repos, count));
    model->addRepos(DataUtils::reposFromJson(repos));
    model->setLoading(false);

    // cleanup
    m_reposModelRequests.remove(requestId);
}

void ApiInterface::parseRepoSubscription(const QJsonObject &obj)
{
    const QJsonObject subscription = obj.value(SAILHUB_API_KEY_UPDATE_SUBSCRIPTION).toObject()
                                        .value(SAILHUB_API_KEY_SUBSCRIBABLE).toObject();

    const QString state = subscription.value(SAILHUB_API_KEY_VIEWER_SUBSCRIPTION).toString();

    quint8 value{0};

    if (state == QLatin1String("IGNORED")) {
        value = Repo::SubscriptionIgnored;
    } else if (state == QLatin1String("UNSUBSCRIBED")) {
        value = Repo::Unsubscribed;
    } else if (state == QLatin1String("SUBSCRIBED")) {
        value = Repo::Subscribed;
    }

    emit subscribedToRepo(subscription.value(SAILHUB_API_KEY_ID).toString(), value);
}

void ApiInterface::parseUsers(const QJsonObject &obj, const QByteArray &requestId)
{
    UsersModel *model = m_usersModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // get identifier and users
    QJsonValue count;
    QJsonObject users;

    switch (model->modelType()) {
    case User::Contributor:
        users = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_MENTIONABLE_USERS).toObject();
        count = obj.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case User::Stargazer:
        users = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_STARGAZERS).toObject();
        count = obj.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case User::Watcher:
        users = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_WATCHERS).toObject();
        count = obj.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case User::Follower:
        users = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_FOLLOWERS).toObject();
        count = obj.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case User::Following:
        users = obj.value(SAILHUB_API_KEY_NODE).toObject()
                   .value(SAILHUB_API_KEY_FOLLOWING).toObject();
        count = obj.value(SAILHUB_API_KEY_TOTAL_COUNT);
        break;

    case User::Search:
        users = obj.value(SAILHUB_API_KEY_SEARCH).toObject();
        count = users.value(SAILHUB_API_KEY_USER_COUNT);
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(users, count));
    model->addUsers(DataUtils::usersFromJson(users));
    model->setLoading(false);

    // cleanup
    m_usersModelRequests.remove(requestId);
}
