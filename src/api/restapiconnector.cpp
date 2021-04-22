#include "restapiconnector.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "src/tools/compress.h"

RestApiConnector::RestApiConnector(QNetworkAccessManager *manager, QObject *parent) :
    QObject(parent),
    m_manager(manager)
{

}

void RestApiConnector::setToken(const QString &token)
{
    m_token = token;
}

QString RestApiConnector::token() const
{
    return m_token;
}

void RestApiConnector::get(const QString &endpoint, quint8 requestType, const QByteArray &requestId)
{
    //create request
    QNetworkRequest request = getRequest(endpoint);

    // send request
    QNetworkReply *reply = m_manager->get(request);
    reply->setProperty("request_type", requestType);
    reply->setProperty("request_uuid", requestId);
    connect(reply, &QNetworkReply::finished, this, &RestApiConnector::onRequestFinished);
}

void RestApiConnector::onRequestFinished()
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
        emit connectionError(reply->error(), reply->errorString());

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

    const QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error) {
#ifdef QT_DEBUG
        qDebug() << "JSON PARSE ERROR";
        qDebug() << error.errorString();
#endif
        return;
    }

    emit requestFinished(doc, request, uuid);
}

QNetworkRequest RestApiConnector::getRequest(const QString &endpoint)
{
    QNetworkRequest request(QStringLiteral("https://api.github.com") + endpoint);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Accept", "application/vnd.github.v3+json");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept-Encoding", "gzip");
    request.setRawHeader("Authorization", "token " + m_token.toUtf8());

    return request;
}


