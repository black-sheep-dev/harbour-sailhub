#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>

#include "src/entities/repo.h"
#include "src/entities/user.h"

static const QString SAILHUB_API_URL                                = QStringLiteral("https://api.github.com");

static const QString SAILHUB_API_ENDPOINT_FOLLOWERS                 = QStringLiteral("/followers");
static const QString SAILHUB_API_ENDPOINT_FOLLOWING                 = QStringLiteral("/following");
static const QString SAILHUB_API_ENDPOINT_REPOS                     = QStringLiteral("/repos");
static const QString SAILHUB_API_ENDPOINT_REPOS_SINGLE              = QStringLiteral("/repos/");
static const QString SAILHUB_API_ENDPOINT_REPOS_SEARCH              = QStringLiteral("/search/repositories");
static const QString SAILHUB_API_ENDPOINT_USERS                     = QStringLiteral("/users/");
static const QString SAILHUB_API_ENDPOINT_USERS_SEARCH              = QStringLiteral("/search/users");

class ApiInterface : public QObject
{
    Q_OBJECT

public:
    explicit ApiInterface(QObject *parent = nullptr);

    void getFollowers(const QString &username, quint8 operation = 0);
    void getFollowing(const QString &username, quint8 operation = 0);
    void getRepo(const QString &reponame, quint8 operation = 0);
    void getRepos(const QString &username, quint8 operation = 0);
    void getUser(const QString &username, quint8 operation = 0);
    void searchRepos(const QString &pattern);
    void searchUsers(const QString &pattern);

signals:
    void repoAvailable(Repo *repo, quint8 operation);
    void reposAvailable(const QList<Node *> &users, quint8 operation);
    void reposFound(const QList<Node *> &repos);
    void userAvailable(User *user, quint8 operation);
    void usersAvailable(const QList<Node *> &users, quint8 operation);
    void usersFound(const QList<Node *> &users);

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    Repo *parseRepo(const QJsonObject &obj);
    QList<Node *> parseRepos(const QJsonArray &array);
    User *parseUser(const QJsonObject &obj, bool minimal = false);
    QList<Node *> parseUsers(const QJsonArray &array, bool minimal = false);
    QNetworkRequest getRequest(const QString &endpoint, const QUrlQuery &params = QUrlQuery());
    QByteArray gunzip(const QByteArray &data);

    QNetworkAccessManager *m_manager{nullptr};

};

#endif // APIINTERFACE_H
