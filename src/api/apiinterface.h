#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QObject>

#include <QHash>

#include "graphqlconnector.h"
#include "src/entities/user.h"
#include "src/models/reposmodel.h"
#include "src/models/usersmodel.h"

static const QString SAILHUB_API_GRAPHQL_URL            = QStringLiteral("https://api.github.com/graphql");

class ApiInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint8 paginationCount READ paginationCount WRITE setPaginationCount NOTIFY paginationCountChanged)

public:  
    enum RequestType {
        GetUndefined,
        GetLogin,
        GetProfile,
        GetUser,
        GetUsers,
        GetRepo,
        GetRepos
    };
    Q_ENUM(RequestType)

    explicit ApiInterface(QObject *parent = nullptr);

    Q_INVOKABLE QString login() const;
    void setToken(const QString &token);

    // api calls
    void getLogin();
    Q_INVOKABLE void getProfile();
    Q_INVOKABLE void getRepo(const QString &login, const QString &repoName);
    Q_INVOKABLE void getRepos(ReposModel *model);
    Q_INVOKABLE void getUser(const QString &login);
    Q_INVOKABLE void getUsers(UsersModel *model);

    // properties
    quint8 paginationCount() const;

public slots:
    void setPaginationCount(quint8 paginationCount);

signals:
    Q_INVOKABLE void repoAvailable(Repo *repo);
    Q_INVOKABLE void userAvailable(User *user);

    // properties
    void paginationCountChanged(quint8 count);

private slots:
    void parseData(const QJsonObject &obj, quint8 requestType, const QByteArray &requestId);

private:
    void initialize();
    void parseRepos(const QJsonObject &obj, const QByteArray &requestId);
    void parseUsers(const QJsonObject &obj, const QByteArray &requestId);

    GraphQLConnector *m_connector{new GraphQLConnector(SAILHUB_API_GRAPHQL_URL, this)};
    QHash<QByteArray, ReposModel *> m_reposModelRequests;
    QHash<QByteArray, UsersModel *> m_usersModelRequests;

    QString m_login;

    // properties
    quint8 m_paginationCount{20};
};

#endif // APIINTERFACE_H
