#ifndef SAILHUB_H
#define SAILHUB_H

#include <QObject>

#include "api/apiinterface.h"
#include "entities/user.h"
#include "models/reposmodel.h"
#include "models/usersmodel.h"

class SailHub : public QObject
{
    Q_OBJECT

public:
    enum Operation {
        OperationNone,
        OperationFollow,
        OperationGetFollowers,
        OperationGetFollowing,
        OperationGet
    };
    Q_ENUM(Operation)

    explicit SailHub(QObject *parent = nullptr);
    ~SailHub() override;

    Q_INVOKABLE void followRepo(const QString &reponame);
    Q_INVOKABLE void followUser(const QString &username);
    Q_INVOKABLE void getFollowers(const QString &username);
    Q_INVOKABLE void getFollowing(const QString &username);
    Q_INVOKABLE void getRepo(const QString &reponame);
    Q_INVOKABLE void getUser(const QString &username);
    Q_INVOKABLE void initialize();
    Q_INVOKABLE ReposModel *reposModel();
    Q_INVOKABLE ReposModel *reposSearchModel();
    Q_INVOKABLE void saveSettings();
    Q_INVOKABLE void searchRepos(const QString &pattern);
    Q_INVOKABLE void searchUsers(const QString &pattern);
    Q_INVOKABLE UsersModel *usersSearchModel();
    Q_INVOKABLE UsersModel *usersModel();

signals:
    void followersAvailable(UsersModel *model);
    void followingAvailable(UsersModel *model);
    void repoAvailable(Repo *repo);
    void reposAvailable(ReposModel *model);
    void userAvailable(User *user);
    void usersAvailable(UsersModel *model);

private slots:
    void onRepoAvailable(Repo *repo, quint8 operation);
    void onReposAvailable(const QList<Node *> &repos, quint8 operation);
    void onUserAvailable(User *user, quint8 operation);
    void onUsersAvailable(const QList<Node *> &users, quint8 operation);

private:
    void readSettings();
    void writeSettings();

    ApiInterface *m_api{nullptr};
    ReposModel *m_reposModel{nullptr};
    ReposModel *m_reposSearchModel{nullptr};
    UsersModel *m_usersModel{nullptr};
    UsersModel *m_usersSearchModel{nullptr};
};

#endif // SAILHUB_H
