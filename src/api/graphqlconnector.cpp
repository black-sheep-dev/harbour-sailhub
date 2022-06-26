#include "graphqlconnector.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QSettings>
#include <QStandardPaths>

#include "compressor.h"
#include "keys.h"

static const QString GITHUB_API_ENDPOINT    = QStringLiteral("https://api.github.com/graphql");

GraphQLConnector::GraphQLConnector(QObject *parent) :
    QObject(parent)
{
    readSettings();
}

GraphQLConnector::~GraphQLConnector()
{
    writeSettings();
}

void GraphQLConnector::request(QueryObject *query)
{
    if (query == nullptr) {
        return;
    }

    query->setReady(false);
    query->setError(QueryObject::ErrorNone);

    //create request
    QNetworkRequest request(GITHUB_API_ENDPOINT);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept-Encoding", "gzip");
    request.setRawHeader("Authorization", "token " + m_token.toUtf8());
    //request.setRawHeader("GraphQL-Features", "discussions_api");

    // create payload
    auto q = query->query().simplified();

    if (q.startsWith("query")) {
        q.insert(q.indexOf('{') + 1, " rateLimit { remaining resetAt } ");
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("query"), q);

    if (!query->variables().isEmpty()) {
        payload.insert(QStringLiteral("variables"), query->variables());
    }

#ifdef QT_DEBUG
    qDebug() << payload;
#endif

    // send request
    const auto uuid = QUuid::createUuid().toByteArray();
    m_queryObjects.insert(uuid, query);

    QNetworkReply *reply = m_manager->post(request,
                                           QJsonDocument(payload).toJson(QJsonDocument::Compact));
    reply->setProperty("uuid", uuid);
    connect(reply, &QNetworkReply::finished, this, &GraphQLConnector::onRequestFinished);
}

quint16 GraphQLConnector::remaining() const
{
    return m_remaining;
}

const QDateTime &GraphQLConnector::resetAt() const
{
    return m_resetAt;
}

const QString &GraphQLConnector::token() const
{
    return m_token;
}

void GraphQLConnector::setToken(const QString &token)
{
    if (m_token == token) {
        return;
    }
    m_token = token;
    emit tokenChanged();
    writeSettings();
}

void GraphQLConnector::onRequestFinished()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        return;
    }

    auto query = m_queryObjects.take(reply->property("uuid").toByteArray());

    if (query == nullptr) {
        return;
    }

    if (reply->error()) {
        switch (reply->error()) {

        case QNetworkReply::AuthenticationRequiredError:
            query->setError(QueryObject::ErrorUnauthorized);
            break;

        case QNetworkReply::TimeoutError:
            query->setError(QueryObject::ErrorTimeout);
            break;


        default:
            query->setError(QueryObject::ErrorUndefined);
            break;
        }

        reply->deleteLater();
        query->setReady(true);
        return;
    }

    const QByteArray data = Compressor::gunzip(reply->readAll());
    reply->deleteLater();

    // parse response
    QJsonParseError error{};

    const auto obj = QJsonDocument::fromJson(data, &error).object();

#ifdef QT_DEBUG
    qDebug() << obj;
#endif

    if (error.error) {
        query->setError(QueryObject::ErrorInvalidData);
        query->setReady(true);
        return;
    }

    if (obj.keys().contains(ApiKey::ERROR)) {
        query->setError(QueryObject::ErrorQuery);
        query->setReady(true);
        return;
    }

    auto result = obj.value(ApiKey::DATA).toObject();

    if (result.contains(ApiKey::RATE_LIMIT)) {
        m_remaining = result.value(ApiKey::RATE_LIMIT).toObject().value(ApiKey::REMAINING).toInt();
        m_resetAt = QDateTime::fromString(result.value(ApiKey::RATE_LIMIT).toObject().value(ApiKey::RESET_AT).toString(), Qt::ISODate);
        result.remove(ApiKey::RATE_LIMIT);
    }

    // pick node from path
    if (!query->resultNodePath().isEmpty()) {
        const auto keys = query->resultNodePath().split(".");
        for (const auto &key : keys) {
            result = result.value(key).toObject();
        }
    }

    query->setResult(result);
    query->setReady(true);
}

void GraphQLConnector::readSettings()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/sailhub/sailhub.conf";

    if (!QFile(path).exists()) {
           path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/harbour-sailhub/harbour-sailhub.conf";
    }

    QSettings settings(path, QSettings::NativeFormat);

    settings.beginGroup("APP");
    setToken(settings.value("token").toString());
    settings.endGroup();
}

void GraphQLConnector::writeSettings()
{
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/sailhub/sailhub.conf", QSettings::NativeFormat);

    settings.beginGroup("APP");
    settings.setValue("token", m_token);
    settings.endGroup();
}
