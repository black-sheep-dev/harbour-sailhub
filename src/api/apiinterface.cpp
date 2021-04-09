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

void ApiInterface::addComment(const QString &body, CommentsModel *model)
{
    if (m_profile == nullptr || model == nullptr)
        return;

    GraphQLQuery query;
    query.query = SAILHUB_MUTATION_ADD_COMMENT;

    QJsonObject vars;
    vars.insert(ApiKey::CLIENT_MUTATION_ID, m_profile->nodeId());
    vars.insert(ApiKey::SUBJECT_ID, model->identifier());

    if (!body.isEmpty())
        vars.insert(ApiKey::BODY, body);

    query.variables.insert(SAILHUB_MUTATION_VAR_INPUT, vars);

    m_connector->sendQuery(query, RequestType::AddComment);
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

    m_connector->sendQuery(query, RequestType::CloseIssue);
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

    m_connector->sendQuery(query, RequestType::CreateIssue);
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

    m_connector->sendQuery(query, RequestType::DeleteComment);
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

    m_connector->sendQuery(query, RequestType::DeleteIssue);
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

void ApiInterface::getUserByLogin(const QString &login)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER_BY_LOGIN;
    query.variables.insert(QueryVar::USER_LOGIN, login);

    m_connector->sendQuery(query, RequestType::GetUserByLogin);
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

    m_connector->sendQuery(query, RequestType::UpdateComment);
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

    m_connector->sendQuery(query, RequestType::UpdateIssue);
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

    case RequestType::GetRepoTree:
        parseRepoTree(data, requestId);
        break;

    case RequestType::GetOrganization:
        emit organizationAvailable(DataUtils::organizationFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::GetPaginationModel:
        parsePaginationModel(data, requestId);
        break;

    case RequestType::GetIssue:
        emit issueAvailable(DataUtils::issueFromJson(data.value(ApiKey::NODE).toObject()));
        break;

    case RequestType::AddComment:
        emit commentAdded();
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

    case RequestType::CloseIssue:
        emit issueClosed();
        break;

    case RequestType::DeleteComment:
        emit commentDeleted();
        break;

    case RequestType::DeleteIssue:
        emit issueDeleted();
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
