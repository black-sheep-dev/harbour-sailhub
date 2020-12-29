#include "apiinterface.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QHashIterator>

#include "datautils.h"
#include "keys.h"
#include "queries.h"

ApiInterface::ApiInterface(QObject *parent) :
    QObject(parent)
{
    connect(m_connector, &GraphQLConnector::requestFinished, this, &ApiInterface::parseData);
}

QString ApiInterface::login() const
{
    return m_login;
}

void ApiInterface::setToken(const QString &token)
{
    m_connector->setToken(token);
    initialize();
}

void ApiInterface::getLogin()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_LOGIN;

    m_connector->sendQuery(query, RequestType::GetLogin);
}

void ApiInterface::getProfile()
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER;
    query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, m_login);

    m_connector->sendQuery(query, RequestType::GetProfile);
}

void ApiInterface::getRepo(const QString &login, const QString &repoName)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_REPOSITORY;
    query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, login);
    query.variables.insert(SAILHUB_QUERY_VAR_REPO_NAME, repoName);

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

    default:
        break;
    }

    if ( repoType == Repo::Fork ) {
        const QStringList parts = model->identifier().split("/");

        if (parts.count() < 2)
            return;

        query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, parts.first());
        query.variables.insert(SAILHUB_QUERY_VAR_REPO_NAME, parts.last());

    } else {
        query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, model->identifier());
    }

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

void ApiInterface::getUser(const QString &login)
{
    GraphQLQuery query;
    query.query = SAILHUB_QUERY_GET_USER;
    query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, login);

    m_connector->sendQuery(query, RequestType::GetUser);
}

void ApiInterface::getUsers(UsersModel *model)
{
    GraphQLQuery query;
    query.variables.insert(SAILHUB_QUERY_VAR_ITEM_COUNT, m_paginationCount);

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

    if ( model->modelType() == User::Contributor
         || model->modelType() == User::Stargazer
         || model->modelType() == User::Watcher ) {

        const QStringList parts = model->identifier().split("/");

        if (parts.count() < 2)
            return;

        query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, parts.first());
        query.variables.insert(SAILHUB_QUERY_VAR_REPO_NAME, parts.last());

    } else {
        query.variables.insert(SAILHUB_QUERY_VAR_USER_LOGIN, model->identifier());
    }

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

quint8 ApiInterface::paginationCount() const
{
    return m_paginationCount;
}

void ApiInterface::setPaginationCount(quint8 paginationCount)
{
    if (m_paginationCount == paginationCount)
        return;

    m_paginationCount = paginationCount;
    emit paginationCountChanged(m_paginationCount);
}

void ApiInterface::parseData(const QJsonObject &obj, quint8 requestType, const QByteArray &requestId)
{
#ifdef QT_DEBUG
    qDebug() << requestType;
    qDebug() << obj;
#endif

    const QJsonObject data = obj.value(SAILHUB_API_KEY_DATA).toObject();

    switch (requestType) {
    case RequestType::GetProfile:
    case RequestType::GetUser:
        emit userAvailable(DataUtils::userFromJson(data.value(SAILHUB_API_KEY_USER).toObject()));
        break;

    case RequestType::GetUsers:
        parseUsers(data, requestId);
        break;

    case RequestType::GetRepo:
        emit repoAvailable(DataUtils::repoFromJson(data.value(SAILHUB_API_KEY_REPOSITORY).toObject()));
        break;

    case RequestType::GetRepos:
        parseRepos(data, requestId);
        break;

    case RequestType::GetLogin:
        m_login = data.value(SAILHUB_API_KEY_VIEWER).toObject()
                    .value(SAILHUB_API_KEY_LOGIN).toString();
        break;

    default:
        break;
    }
}

void ApiInterface::initialize()
{
    getLogin();
}

void ApiInterface::parseRepos(const QJsonObject &obj, const QByteArray &requestId)
{
    ReposModel *model = m_reposModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;



    // get identifier and repos
    QJsonObject repos;

    switch (model->modelType()) {
    case Repo::User:
        repos = obj.value(SAILHUB_API_KEY_USER).toObject()
                .value(SAILHUB_API_KEY_REPOSITORIES).toObject();
        break;

    case Repo::Fork:
        repos = obj.value(SAILHUB_API_KEY_REPOSITORY).toObject()
                .value(SAILHUB_API_KEY_FORKS).toObject();
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(repos));
    model->addRepos(DataUtils::reposFromJson(repos));
    model->setLoading(false);

    // cleanup
    m_usersModelRequests.remove(requestId);
}

void ApiInterface::parseUsers(const QJsonObject &obj, const QByteArray &requestId)
{
    UsersModel *model = m_usersModelRequests.value(requestId, nullptr);

    if (model == nullptr)
        return;

    // get identifier and users
    QJsonObject users;

    switch (model->modelType()) {
    case User::Contributor:
        users = obj.value(SAILHUB_API_KEY_REPOSITORY).toObject()
                .value(SAILHUB_API_KEY_MENTIONABLE_USERS).toObject();
        break;

    case User::Stargazer:
        users = obj.value(SAILHUB_API_KEY_REPOSITORY).toObject()
                .value(SAILHUB_API_KEY_STARGAZERS).toObject();
        break;

    case User::Watcher:
        users = obj.value(SAILHUB_API_KEY_REPOSITORY).toObject()
                .value(SAILHUB_API_KEY_WATCHERS).toObject();
        break;

    case User::Follower:
        users = obj.value(SAILHUB_API_KEY_USER).toObject()
                .value(SAILHUB_API_KEY_FOLLOWERS).toObject();
        break;

    case User::Following:
        users = obj.value(SAILHUB_API_KEY_USER).toObject()
                .value(SAILHUB_API_KEY_FOLLOWING).toObject();
        break;

    default:
        return;
    }

    model->setPageInfo(DataUtils::pageInfoFromJson(users));
    model->addUsers(DataUtils::usersFromJson(users));
    model->setLoading(false);

    // cleanup
    m_usersModelRequests.remove(requestId);
}
