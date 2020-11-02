#include "sailhub.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QSettings>

SailHub::SailHub(QObject *parent) :
    QObject(parent),
    m_api(new ApiInterface(this)),
    m_reposModel(new ReposModel(this)),
    m_reposSearchModel(new ReposModel(this)),
    m_usersModel(new UsersModel(this)),
    m_usersSearchModel(new UsersModel(this))
{
    connect(m_api, &ApiInterface::repoAvailable, this, &SailHub::onRepoAvailable);
    connect(m_api, &ApiInterface::reposAvailable, this, &SailHub::onReposAvailable);
    connect(m_api, &ApiInterface::reposFound, m_reposSearchModel, &UsersModel::setNodes);
    connect(m_api, &ApiInterface::usersFound, m_usersSearchModel, &UsersModel::setNodes);
    connect(m_api, &ApiInterface::userAvailable, this, &SailHub::onUserAvailable);
    connect(m_api, &ApiInterface::usersAvailable, this, &SailHub::onUsersAvailable);

    readSettings();
}

SailHub::~SailHub()
{
    writeSettings();
}

void SailHub::followRepo(const QString &reponame)
{
    m_api->getRepo(reponame, SailHub::OperationFollow);
}

void SailHub::followUser(const QString &username)
{
    m_api->getUser(username, SailHub::OperationFollow);
}

void SailHub::getFollowers(const QString &username)
{
    m_api->getFollowers(username, SailHub::OperationGetFollowers);
}

void SailHub::getFollowing(const QString &username)
{
    m_api->getFollowers(username, SailHub::OperationGetFollowing);
}

void SailHub::getRepo(const QString &reponame)
{
    m_api->getRepo(reponame, SailHub::OperationGet);
}

void SailHub::getUser(const QString &username)
{
    m_api->getUser(username, SailHub::OperationGet);
}

void SailHub::initialize()
{

}

ReposModel *SailHub::reposModel()
{
    return m_reposModel;
}

ReposModel *SailHub::reposSearchModel()
{
    return m_reposSearchModel;
}

void SailHub::saveSettings()
{
    writeSettings();
}

void SailHub::searchRepos(const QString &pattern)
{
    m_reposSearchModel->reset();
    m_reposSearchModel->setLoading(true);
    m_api->searchRepos(pattern);
}

void SailHub::searchUsers(const QString &pattern)
{
    m_usersSearchModel->reset();
    m_usersSearchModel->setLoading(true);
    m_api->searchUsers(pattern);
}

UsersModel *SailHub::usersSearchModel()
{
    return m_usersSearchModel;
}

UsersModel *SailHub::usersModel()
{
    return m_usersModel;
}

void SailHub::onRepoAvailable(Repo *repo, quint8 operation)
{
    switch (operation) {
    case OperationGet:
        emit repoAvailable(repo);
        break;

    case OperationFollow:
        m_reposModel->addNode(repo);
        writeSettings();
        break;

    default:
#ifdef QT_DEBUG
        qDebug() << QStringLiteral("Operation unknown: ") << operation;
#endif
        break;
    }
}

void SailHub::onReposAvailable(const QList<Node *> &repos, quint8 operation)
{
    Q_UNUSED(operation)

    auto *model = new ReposModel;
    model->setNodes(repos);

    emit reposAvailable(model);
}

void SailHub::onUserAvailable(User *user, quint8 operation)
{
    switch (operation) {
    case OperationGet:
        emit userAvailable(user);
        break;

    case OperationFollow:
        m_usersModel->addNode(user);
        writeSettings();
        break;

    default:
#ifdef QT_DEBUG
        qDebug() << QStringLiteral("Operation unknown: ") << operation;
#endif
        break;
    }
}

void SailHub::onUsersAvailable(const QList<Node *> &users, quint8 operation)
{
    auto *model = new UsersModel;
    model->setNodes(users);

    switch (operation) {
    case OperationGetFollowers:
        emit followersAvailable(model);
        break;

    case OperationGetFollowing:
        emit followingAvailable(model);
        break;

    default:
#ifdef QT_DEBUG
        qDebug() << QStringLiteral("Operation unknown: ") << operation;
#endif
        model->deleteLater();
        break;
    }
}

void SailHub::readSettings()
{
    QSettings settings;
    settings.beginGroup(QStringLiteral("DATA"));

    // repos
    const QStringList reponames = settings.value(QStringLiteral("followed_repos")).toStringList();
    for (const QString &reponame : reponames) {
        followRepo(reponame);
    }

    // users
    const QStringList usernames = settings.value(QStringLiteral("followed_users")).toStringList();
    for (const QString &username : usernames) {
        followUser(username);
    }


    settings.endGroup();
}

void SailHub::writeSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("DATA"));

    // repos
    QStringList reponames;
    for (auto *node : m_reposModel->nodes()) {
        auto *repo = qobject_cast<Repo *>(node);

        reponames.append(repo->fullName());
    }
    settings.setValue(QStringLiteral("followed_repos"), reponames);

    // users
    QStringList usernames;
    for (auto *node : m_usersModel->nodes()) {
        auto *user = qobject_cast<User *>(node);

        usernames.append(user->login());
    }
    settings.setValue(QStringLiteral("followed_users"), usernames);

    settings.endGroup();
}
