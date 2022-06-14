#include "queryobject.h"

#include <QDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonParseError>

#include "compressor.h"
#include "keys.h"

QueryObject::QueryObject(QObject *parent) :
    QObject(parent)
{

}

quint8 QueryObject::error() const
{
    return m_error;
}

void QueryObject::setError(quint8 error)
{
    if (m_error == error)
        return;
    m_error = error;
    emit errorChanged();
}


const QString &QueryObject::query() const
{
    return m_query;
}

void QueryObject::setQuery(const QString &query)
{
    if (m_query == query)
        return;
    m_query = query;
    emit queryChanged();
}

bool QueryObject::ready() const
{
    return m_ready;
}

void QueryObject::setReady(bool ready)
{
    if (m_ready == ready)
        return;
    m_ready = ready;
    emit readyChanged();
}

const QJsonObject &QueryObject::result() const
{
    return m_result;
}

void QueryObject::setResult(const QJsonObject &result)
{
    if (m_result == result)
        return;
    m_result = result;
    emit resultChanged();
}

void QueryObject::onResultAvailable()
{
    setReady(true);

    auto reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        return;
    }

    if (reply->error()) {
        switch (reply->error()) {

        case QNetworkReply::AuthenticationRequiredError:
            setError(ErrorUnauthorized);
            break;

        case QNetworkReply::TimeoutError:
            setError(ErrorTimeout);
            break;


        default:
            setError(ErrorUndefined);
            break;
        }

        reply->deleteLater();
        return;
    }

    const QByteArray data = Compressor::gunzip(reply->readAll());
    reply->deleteLater();

    // parse response
    QJsonParseError error{};

    const auto obj = QJsonDocument::fromJson(data, &error).object();
    qDebug() << obj;
    m_result = obj.value(ApiKey::DATA).toObject().value(ApiKey::NODE).toObject();

    if (error.error) {
        setError(ErrorInvalidData);
    }

    emit resultChanged();
}

const QJsonObject &QueryObject::variables() const
{
    return m_variables;
}

void QueryObject::setVariables(const QJsonObject &variables)
{
    if (m_variables == variables)
        return;
    m_variables = variables;
    emit variablesChanged();
}
