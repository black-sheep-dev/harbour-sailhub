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
#include "queryvars.h"

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
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::REPOSITORY_ID, model->identifier());
    vars.insert(ApiKey::TITLE, title);

    if (!body.isEmpty())
        vars.insert(ApiKey::BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::CreateIssue, uuid);
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

    m_connector->sendQuery(query, follow ? RequestType::FollowUser : RequestType::UnfollowUser);
}

void ApiInterface::getComments(CommentsModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ISSUE_COMMENTS;

    query.variables.insert(QueryVar::NODE_ID, model->identifier());
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetComments, uuid);
}

void ApiInterface::getFileContent(const QString &nodeId, const QString &branch)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_FILE_CONTENT;
    query.variables.insert(QueryVar::NODE_ID, nodeId);
    query.variables.insert(QueryVar::BRANCH, branch);

    m_connector->sendQuery(query, RequestType::GetFileContent);
}

void ApiInterface::getIssue(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ISSUE;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetIssue);
}

void ApiInterface::getOrganization(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_ORGANIZATION;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetOrganization);
}

void ApiInterface::getOrganizations(OrganizationsModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;

    switch (model->modelType()) {
    case Organization::IsMember:
        query.query = SAILHUB_QUERY_GET_USER_ORGANIZATIONS;
        break;

    default:
        break;
    }

    query.variables.insert(QueryVar::NODE_ID, model->identifier());
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if cursor available insert it
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send
    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetOrganizations, uuid);
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
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetPaginationModel, uuid);
}

void ApiInterface::getProfile()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_VIEWER_PROFILE;

    m_connector->sendQuery(query, RequestType::GetProfile);
}

void ApiInterface::getPullRequest(const QString &nodeId)
{

}

void ApiInterface::getRepo(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetRepo);
}

void ApiInterface::getRepos(ReposModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;
    const quint8 repoType = model->modelType();

    switch (repoType) {
    case Repo::User:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES;
        break;

    case Repo::Organization:
        query.query = SAILHUB_QUERY_GET_ORGANIZATION_REPOSITORIES;
        break;

    case Repo::Fork:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_FORKS;
        break;

    case Repo::Starred:
        query.query = SAILHUB_QUERY_GET_USER_REPOSITORIES_STARRED;
        break;

    default:
        return;
    }

    query.variables.insert(QueryVar::NODE_ID, model->identifier());
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetRepos, uuid);
}

void ApiInterface::getRepoTree(const QString &nodeId, const QString &branch, const QString &path, TreeModel *model)
{
    if (model == nullptr)
        return;

#ifdef QT_DEBUG
    qDebug() << "NodeID: " << nodeId;
    qDebug() << "branch: " << branch;
    qDebug() << "path: " << path;
#endif

    model->setLoading(true);

    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY_FILES;

    query.variables.insert(QueryVar::NODE_ID, nodeId);
    query.variables.insert(QueryVar::BRANCH, branch);
    query.variables.insert(QueryVar::PATH, path);

    const QByteArray uuid = QUuid::createUuid().toByteArray();
    m_treeModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetRepoTree, uuid);
}

void ApiInterface::getUser(const QString &nodeId)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER;
    query.variables.insert(QueryVar::NODE_ID, nodeId);

    m_connector->sendQuery(query, RequestType::GetUser);
}

void ApiInterface::getUsers(UsersModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;

    switch (model->modelType()) {
    case User::Follower:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWERS;
        break;

    case User::Following:
        query.query = SAILHUB_QUERY_GET_USER_FOLLOWING;
        break;

    case User::OrganizationMember:
        query.query = SAILHUB_QUERY_GET_ORGANIZATION_MEMBERS;
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
        return;
    }

    query.variables.insert(QueryVar::NODE_ID, model->identifier());
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if cursor available insert it
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    // save and send
    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::GetUsers, uuid);
}

void ApiInterface::searchOrganization(const QString &pattern, OrganizationsModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_QUERY_SEARCH_ORGANIZATION;
    query.variables.insert(QueryVar::QUERY_STRING, pattern);
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::SearchOrganization, uuid);
}

void ApiInterface::searchRepo(const QString &pattern, ReposModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_QUERY_SEARCH_REPOSITORY;
    query.variables.insert(QueryVar::QUERY_STRING, pattern);
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::SearchRepo, uuid);
}

void ApiInterface::searchUser(const QString &pattern, UsersModel *model)
{
    if (model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_QUERY_SEARCH_USER;
    query.variables.insert(QueryVar::QUERY_STRING, pattern);
    query.variables.insert(QueryVar::ITEM_COUNT, m_paginationCount);

    // if next insert item cursor
    if (!model->lastItemCursor().isEmpty()) {
        query.variables.insert(QueryVar::ITEM_CURSOR, model->lastItemCursor());
    }

    model->setLoading(true);

    const QByteArray uuid = model->uuid();
    m_paginationModelRequests.insert(uuid, model);
    m_connector->sendQuery(query, RequestType::SearchUser, uuid);
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

    m_connector->sendQuery(query, star ? RequestType::StarRepo : RequestType::UnstarRepo);
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

    switch (state) {
    case Repo::SubscriptionIgnored:
        vars.insert(ApiKey::STATE, QStringLiteral("IGNORED"));
        break;

    case Repo::Subscribed:
        vars.insert(ApiKey::STATE, QStringLiteral("SUBSCRIBED"));
        break;

    case Repo::Unsubscribed:
        vars.insert(ApiKey::STATE, QStringLiteral("UNSUBSCRIBED"));
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

    case RequestType::GetUsers:
    case RequestType::SearchUser:
        parseUsers(data, requestId);
        break;

    case RequestType::GetRepo:
        emit repoAvailable(DataUtils::repoFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetRepos:
    case RequestType::SearchRepo:
        parseRepos(data, requestId);
        break;

    case RequestType::GetRepoTree:
        parseRepoTree(data, requestId);
        break;

    case RequestType::GetOrganization:
        emit organizationAvailable(DataUtils::organizationFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetOrganizations:
    case RequestType::SearchOrganization:
        parseOrganizations(data, requestId);
        break;

    case RequestType::GetPaginationModel:
        parsePaginationModel(data, requestId);
        break;

    case RequestType::GetIssue:
        emit issueAvailable(DataUtils::issueFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::CreateIssue:
        emit issueCreated(DataUtils::issueFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetComments:
        parseComments(data, requestId);
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
    auto model = qobject_cast<CommentsModel *>(m_paginationModelRequests.value(requestId, nullptr));

    if (model == nullptr)
        return;

    // get identifier and comments
    const QJsonObject comments = obj.value(ApiKey::NODE).toObject()
                                  .value(ApiKey::COMMENTS).toObject();
    const QJsonValue count = comments.value(ApiKey::TOTAL_COUNT);

    model->setPageInfo(DataUtils::pageInfoFromJson(comments, count));
    model->addComments(DataUtils::commentsFromJson(comments));
    model->setLoading(false);

    // cleanup
    m_paginationModelRequests.remove(requestId);
}

void ApiInterface::parseFileContent(const QJsonObject &obj)
{
    const QJsonObject data = obj.value(ApiKey::NODE).toObject()
            .value(ApiKey::OBJECT).toObject();

    if (data.value(ApiKey::IS_BINARY).toBool())
        return;

    emit fileContentAvailable(data.value(ApiKey::TEXT).toString());
}

void ApiInterface::parseOrganizations(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = qobject_cast<OrganizationsModel *>(m_paginationModelRequests.value(requestId, nullptr));

    if (model == nullptr)
        return;

    // get identifier and users
    QJsonValue count;
    QJsonObject organizations;

    switch (model->modelType()) {
    case Organization::IsMember:
        organizations = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::ORGANIZATIONS).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case Organization::Search:
        organizations = obj.value(ApiKey::SEARCH).toObject();
        count = organizations.value(ApiKey::USER_COUNT);
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(organizations, count));
    model->addOrganizations(DataUtils::organizationsFromJson(organizations));
    model->setLoading(false);

    // cleanup
    m_paginationModelRequests.remove(requestId);
}

void ApiInterface::parsePaginationModel(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = m_paginationModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // parse data
    model->parseQueryResult(obj);

    // cleanup
    m_paginationModelRequests.remove(requestId);
}

void ApiInterface::parseRepos(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = qobject_cast<ReposModel *>(m_paginationModelRequests.value(requestId, nullptr));

    if (model == nullptr)
        return;

    // get identifier and repos
    QJsonValue count;
    QJsonObject repos;

    switch (model->modelType()) {
    case Repo::User:
    case Repo::Organization:
        repos = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::REPOSITORIES).toObject();
        count = repos.value(ApiKey::TOTAL_COUNT);
        break;

    case Repo::Fork:
        repos = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::FORKS).toObject();
        count = repos.value(ApiKey::TOTAL_COUNT);
        break;

    case Repo::Search:
        repos = obj.value(ApiKey::SEARCH).toObject();
        count = repos.value(ApiKey::REPOSITORY_COUNT);
        break;

    case Repo::Starred:
        repos = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::STARRED_REPOSITORIES).toObject();
        count = repos.value(ApiKey::REPOSITORY_COUNT);
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(repos, count));
    model->addRepos(DataUtils::reposFromJson(repos));
    model->setLoading(false);

    // cleanup
    m_paginationModelRequests.remove(requestId);
}

void ApiInterface::parseRepoSubscription(const QJsonObject &obj)
{
    const QJsonObject subscription = obj.value(ApiKey::UPDATE_SUBSCRIPTION).toObject()
                                        .value(ApiKey::SUBSCRIBABLE).toObject();

    const QString state = subscription.value(ApiKey::VIEWER_SUBSCRIPTION).toString();

    quint8 value{0};

    if (state == QLatin1String("IGNORED")) {
        value = Repo::SubscriptionIgnored;
    } else if (state == QLatin1String("UNSUBSCRIBED")) {
        value = Repo::Unsubscribed;
    } else if (state == QLatin1String("SUBSCRIBED")) {
        value = Repo::Subscribed;
    }

    emit subscribedToRepo(subscription.value(ApiKey::ID).toString(), value);
}

void ApiInterface::parseRepoTree(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = m_treeModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    model->setItems(DataUtils::treeListItemsFromJson(obj));

    m_treeModelRequests.remove(requestId);
}

void ApiInterface::parseUsers(const QJsonObject &obj, const QByteArray &requestId)
{
    auto model = qobject_cast<UsersModel *>(m_paginationModelRequests.value(requestId, nullptr));

    if (model == nullptr)
        return;

    // get identifier and users
    QJsonValue count;
    QJsonObject users;

    switch (model->modelType()) {
    case User::Contributor:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::MENTIONABLE_USERS).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Stargazer:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::STARGAZERS).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Watcher:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::WATCHERS).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Follower:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::FOLLOWERS).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Following:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::FOLLOWING).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::OrganizationMember:
        users = obj.value(ApiKey::NODE).toObject()
                   .value(ApiKey::MEMBERS_WITH_ROLE).toObject();
        count = obj.value(ApiKey::TOTAL_COUNT);
        break;

    case User::Search:
        users = obj.value(ApiKey::SEARCH).toObject();
        count = users.value(ApiKey::USER_COUNT);
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(users, count));
    model->addUsers(DataUtils::usersFromJson(users));
    model->setLoading(false);

    // cleanup
    m_paginationModelRequests.remove(requestId);
}
