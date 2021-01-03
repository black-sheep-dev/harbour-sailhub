#include "graphqlconnector.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonParseError>
#include <QJsonDocument>

#include <zlib.h>

GraphQLConnector::GraphQLConnector(const QString &endpoint, QObject *parent) :
    QObject(parent),
    m_endpoint(endpoint)
{
    connect(m_manager, &QNetworkAccessManager::finished, this, &GraphQLConnector::onRequestFinished);
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

    // send request
    QNetworkReply *reply = m_manager->post(request,
                                           QJsonDocument(payload).toJson(QJsonDocument::Compact));
    reply->setProperty("request_type", requestType);
    reply->setProperty("request_uuid", requestId);
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

void GraphQLConnector::onRequestFinished(QNetworkReply *reply)
{
#ifdef QT_DEBUG
    qDebug() << "API REPLY";
#endif

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
    QByteArray data = gunzip(raw);

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

QByteArray GraphQLConnector::gunzip(const QByteArray &data)
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
