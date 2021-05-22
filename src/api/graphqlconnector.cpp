#include "graphqlconnector.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonParseError>
#include <QJsonDocument>
#include <utility> 
#include <zlib.h>

GraphQLConnector::GraphQLConnector(QString endpoint, QNetworkAccessManager *manager, QObject *parent) :
    QObject(parent),
    m_endpoint(std::move(endpoint)),
    m_manager(manager)
{
}

void GraphQLConnector::sendQuery(const GraphQLQuery &query, quint8 requestType, const QByteArray &requestId)
{    
    // create payload
    QJsonObject payload;
    payload.insert(QStringLiteral("query"), query.query);

    if (!query.variables.isEmpty())
        payload.insert(QStringLiteral("variables"), query.variables);

#ifdef QT_DEBUG
    qDebug() << payload;
#endif

    //create request
    QNetworkRequest request(m_endpoint);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept-Encoding", "gzip");
    request.setRawHeader("Authorization", "token " + m_token.toUtf8());
    request.setRawHeader("GraphQL-Features", "discussions_api");

    // send request
    QNetworkReply *reply = m_manager->post(request,
                                           QJsonDocument(payload).toJson(QJsonDocument::Compact));
    reply->setProperty("request_type", requestType);
    reply->setProperty("request_uuid", requestId);
    connect(reply, &QNetworkReply::finished, this, &GraphQLConnector::onRequestFinished);
}

void GraphQLConnector::setEndpoint(const QString &endpoint)
{
    m_endpoint = endpoint;
}

void GraphQLConnector::setToken(const QString &token)
{
    m_token = token;
}

QString GraphQLConnector::token() const
{
    return m_token;
}

void GraphQLConnector::onRequestFinished()
{
#ifdef QT_DEBUG
    qDebug() << "API REPLY";
#endif

    auto reply = qobject_cast<QNetworkReply *>(sender());

    if (reply == nullptr)
        return;

    // handel errors
    if (reply->error()) {
#ifdef QT_DEBUG
        qDebug() << reply->errorString();
#endif
        emit connectionError(reply->error(),
                             reply->errorString(),
                             reply->property("request_uuid").toByteArray());

        reply->deleteLater();
        return;
    }

    // read data
    const quint8 request = quint8(reply->property("request_type").toUInt());
    const QByteArray uuid = reply->property("request_uuid").toByteArray();
    const QByteArray raw = reply->readAll();
    QByteArray data = Compress::gunzip(raw);

    if (data.isEmpty())
        data = raw;

    reply->deleteLater();

    // parse response
    QJsonParseError error{};

    const QJsonObject obj = QJsonDocument::fromJson(data, &error).object();

    if (error.error) {
#ifdef QT_DEBUG
        qDebug() << "JSON PARSE ERROR";
        qDebug() << error.errorString();
#endif
        return;
    }

    emit requestFinished(obj, request, uuid);
}
