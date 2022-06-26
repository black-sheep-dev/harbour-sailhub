#include "queryobject.h"

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

QJsonObject &QueryObject::result()
{
    return m_result;
}

void QueryObject::setResult(const QJsonObject &result)
{
    m_result = result;
    emit resultChanged();
}

const QString &QueryObject::resultNodePath() const
{
    return m_resultNodePath;
}

void QueryObject::setResultNodePath(const QString &path)
{
    if (m_resultNodePath == path)
        return;
    m_resultNodePath = path;
    emit resultNodePathChanged();
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


