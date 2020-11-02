#include "apiinterface.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

#include <zlib.h>

ApiInterface::ApiInterface(QObject *parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, &QNetworkAccessManager::finished, this, &ApiInterface::onRequestFinished);
}

void ApiInterface::getFollowers(const QString &username, quint8 operation)
{
    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_USERS + username + SAILHUB_API_ENDPOINT_FOLLOWERS));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_FOLLOWERS);
    reply->setProperty("operation", operation);
}

void ApiInterface::getFollowing(const QString &username, quint8 operation)
{
    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_USERS + username + SAILHUB_API_ENDPOINT_FOLLOWING));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_FOLLOWING);
    reply->setProperty("operation", operation);
}

void ApiInterface::getRepo(const QString &reponame, quint8 operation)
{
    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_REPOS_SINGLE + reponame));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_REPOS_SINGLE);
    reply->setProperty("operation", operation);
}

void ApiInterface::getRepos(const QString &username, quint8 operation)
{
    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_USERS + username + SAILHUB_API_ENDPOINT_REPOS));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_REPOS);
    reply->setProperty("operation", operation);
}

void ApiInterface::getUser(const QString &username, quint8 operation)
{
    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_USERS + username));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_USERS);
    reply->setProperty("operation", operation);
}

void ApiInterface::searchRepos(const QString &pattern)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("q"), pattern);

    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_REPOS_SEARCH, query));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_REPOS_SEARCH);
}

void ApiInterface::searchUsers(const QString &pattern)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("q"), pattern);

    QNetworkReply *reply = m_manager->get(getRequest(SAILHUB_API_ENDPOINT_USERS_SEARCH, query));
    reply->setProperty("endpoint", SAILHUB_API_ENDPOINT_USERS_SEARCH);
}

void ApiInterface::onRequestFinished(QNetworkReply *reply)
{
#ifdef QT_DEBUG
    qDebug() << "API REPLY";
#endif

    // read data
    const QString endpoint = reply->property("endpoint").toString();
    quint8 operation = quint8(reply->property("operation").toUInt());
    const QByteArray raw = reply->readAll();
    QByteArray data = gunzip(raw);

    if (data.isEmpty())
        data = raw;

    const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

#ifdef QT_DEBUG
    qDebug() << endpoint;
    //qDebug() << data;
    qDebug() << data.size();
    qDebug() << status;
#endif

    // handel errors
    if (reply->error()) {
#ifdef QT_DEBUG
        qDebug() << reply->errorString();
#endif

        reply->deleteLater();
        return;
    }

    // delete reply
    reply->deleteLater();

    // parse json response
    QJsonParseError error{};

    const QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error) {
#ifdef QT_DEBUG
        qDebug() << "JSON PARSE ERROR";
        qDebug() << error.errorString();
#endif
        return;
    }

    // handle endpoints
    if (endpoint == SAILHUB_API_ENDPOINT_USERS_SEARCH) {
        emit usersFound(parseUsers(doc.object().value(QStringLiteral("items")).toArray(), true));
    } else if (endpoint == SAILHUB_API_ENDPOINT_REPOS_SEARCH) {
        emit reposFound(parseRepos(doc.object().value(QStringLiteral("items")).toArray()));
    } else if (endpoint == SAILHUB_API_ENDPOINT_USERS) {
        const QJsonObject user = doc.object();
        emit userAvailable(parseUser(user), operation);
    } else if ( endpoint == SAILHUB_API_ENDPOINT_FOLLOWERS
                || endpoint == SAILHUB_API_ENDPOINT_FOLLOWING ) {
        emit usersAvailable(parseUsers(doc.array()), operation);
    } else if (endpoint == SAILHUB_API_ENDPOINT_REPOS) {
        emit reposAvailable(parseRepos(doc.array()), operation);
    } else if (endpoint == SAILHUB_API_ENDPOINT_REPOS_SINGLE) {
        emit repoAvailable(parseRepo(doc.object()), operation);
    }
}

Repo *ApiInterface::parseRepo(const QJsonObject &obj)
{
    auto *repo = new Repo;
    repo->setId(quint64(obj.value(QStringLiteral("id")).toInt()));
    repo->setNodeId(obj.value(QStringLiteral("node_id")).toString());
    repo->setCreatedAt(QDateTime::fromString(obj.value(QStringLiteral("created_at")).toString(), Qt::ISODate));
    repo->setUpdatedAt(QDateTime::fromString(obj.value(QStringLiteral("updated_at")).toString(), Qt::ISODate));

    repo->setArchived(obj.value(QStringLiteral("archived")).toBool());
    repo->setDefaultBranch(obj.value(QStringLiteral("default_branch")).toString());
    repo->setDescription(obj.value(QStringLiteral("description")).toString());
    repo->setDisabled(obj.value(QStringLiteral("disabled")).toBool());
    repo->setFork(obj.value(QStringLiteral("fork")).toBool());
    repo->setForks(quint32(obj.value(QStringLiteral("forks_count")).toInt()));
    repo->setFullName(obj.value(QStringLiteral("full_name")).toString());
    repo->setHasDownloads(obj.value(QStringLiteral("has_downloads")).toBool());
    repo->setHasIssues(obj.value(QStringLiteral("has_issues")).toBool());
    repo->setHasPages(obj.value(QStringLiteral("has_pages")).toBool());
    repo->setHasProjects(obj.value(QStringLiteral("has_projects")).toBool());
    repo->setHasWiki(obj.value(QStringLiteral("has_wiki")).toBool());
    repo->setHomepage(obj.value(QStringLiteral("homepage")).toString());
    repo->setLanguage(obj.value(QStringLiteral("language")).toString());

    const QJsonObject license = obj.value(QStringLiteral("license")).toObject();
    repo->setLicenseKey(license.value(QStringLiteral("spdx_id")).toString());
    repo->setLicenseName(license.value(QStringLiteral("name")).toString());
    repo->setLicenseUrl(license.value(QStringLiteral("url")).toString());

    repo->setMirrorUrl(obj.value(QStringLiteral("mirror_url")).toString());
    repo->setName(obj.value(QStringLiteral("name")).toString());
    repo->setOpenIssues(obj.value(QStringLiteral("open_issues_count")).toBool());
    repo->setOwner(parseUser(obj.value(QStringLiteral("owner")).toObject(), true));
    repo->setPrivateRepo(obj.value(QStringLiteral("private")).toBool());
    repo->setPushedAt(QDateTime::fromString(obj.value(QStringLiteral("pushed_at")).toString(), Qt::ISODate));
    repo->setScore(qreal(obj.value(QStringLiteral("score")).toDouble()));
    repo->setSize(quint64(obj.value(QStringLiteral("size")).toInt()));
    repo->setStargazers(quint32(obj.value(QStringLiteral("stargazers_count")).toInt()));
    repo->setSubscribers(quint32(obj.value(QStringLiteral("subscribers_count")).toInt()));
    repo->setWatchers(quint32(obj.value(QStringLiteral("watchers_count")).toInt()));

//#ifdef QT_DEBUG
//        qDebug() << "REPO DATA";
//        qDebug() << repo->name();
//        qDebug() << repo->language();
//        qDebug() << repo->updatedAt();
//        qDebug() << repo->stargazers();
//#endif

    return repo;
}

QList<Node *> ApiInterface::parseRepos(const QJsonArray &array)
{
    QList<Node *> repos;

    for (const auto &item : array) {
        repos.append(parseRepo(item.toObject()));
    }

    return repos;
}

User *ApiInterface::parseUser(const QJsonObject &obj, bool minimal)
{
    auto *user = new User;
    user->setLogin(obj.value(QStringLiteral("login")).toString());
    user->setId(quint64(obj.value(QStringLiteral("id")).toInt()));
    user->setNodeId(obj.value(QStringLiteral("node_id")).toString());
    user->setAvatarUrl(obj.value(QStringLiteral("avatar_url")).toString());
    user->setGravatarId(obj.value(QStringLiteral("gravatar_id")).toString());

    const QString type = obj.value(QStringLiteral("type")).toString();

    if (type == QLatin1String("Organization")) {
        user->setUserType(User::TypeOrganization);
    } else if (type == QLatin1String("User")) {
        user->setUserType(User::TypeUser);
    }

    if (!minimal) {
        user->setName(obj.value(QStringLiteral("name")).toString());
        user->setCompany(obj.value(QStringLiteral("company")).toString());
        user->setBlog(obj.value(QStringLiteral("blog")).toString());
        user->setLocation(obj.value(QStringLiteral("location")).toString());
        user->setEmail(obj.value(QStringLiteral("email")).toString());
        user->setHireable(obj.value(QStringLiteral("hireable")).toBool());
        user->setBio(obj.value(QStringLiteral("bio")).toString());
        user->setTwitterUsername(obj.value(QStringLiteral("twitter_username")).toString());
        user->setPublicGists(quint32(obj.value(QStringLiteral("public_gists")).toInt()));
        user->setPublicRepos(quint32(obj.value(QStringLiteral("public_repos")).toInt()));
        user->setFollowers(quint32(obj.value(QStringLiteral("followers")).toInt()));
        user->setFollowing(quint32(obj.value(QStringLiteral("following")).toInt()));
        user->setCreatedAt(QDateTime::fromString(obj.value(QStringLiteral("created_at")).toString(), Qt::ISODate));
        user->setUpdatedAt(QDateTime::fromString(obj.value(QStringLiteral("updated_at")).toString(), Qt::ISODate));
    }

    return user;
}

QList<Node *> ApiInterface::parseUsers(const QJsonArray &array, bool minimal)
{
    QList<Node *> users;

    for (const auto &item : array) {
        users.append(parseUser(item.toObject(), minimal));
    }

    return users;
}

QNetworkRequest ApiInterface::getRequest(const QString &endpoint, const QUrlQuery &params)
{
    QString url = SAILHUB_API_URL + endpoint;

    if (!params.isEmpty())
        url += "?" + params.query();

#ifdef QT_DEBUG
    qDebug() << QStringLiteral("QUERY STRING");
    qDebug() << url;
#endif

    QNetworkRequest request(url);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept-Encoding", "gzip");

    return request;
}

QByteArray ApiInterface::gunzip(const QByteArray &data)
{
    if (data.size() <= 4) {
            return QByteArray();
        }

        QByteArray result;

        int ret;
        z_stream strm;
        static const int CHUNK_SIZE = 1024;
        char out[CHUNK_SIZE];

        /* allocate inflate state */
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = data.size();
        strm.next_in = (Bytef*)(data.data());

        ret = inflateInit2(&strm, 15 +  32); // gzip decoding
        if (ret != Z_OK)
            return QByteArray();

        // run inflate()
        do {
            strm.avail_out = CHUNK_SIZE;
            strm.next_out = (Bytef*)(out);

            ret = inflate(&strm, Z_NO_FLUSH);
            Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     // and fall through
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return QByteArray();
            }

            result.append(out, CHUNK_SIZE - strm.avail_out);
        } while (strm.avail_out == 0);

        // clean up and return
        inflateEnd(&strm);
        return result;
}
