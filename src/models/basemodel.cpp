#include "basemodel.h"

#include <QUuid>

BaseModel::BaseModel(QObject *parent) :
    QAbstractListModel(parent),
    m_uuid(QUuid::createUuid().toByteArray())
{

}

QString BaseModel::identifier() const
{
    return m_identifier;
}

bool BaseModel::loading() const
{
    return m_loading;
}

quint8 BaseModel::modelType() const
{
    return m_modelType;
}

QByteArray BaseModel::uuid() const
{
    return m_uuid;
}

void BaseModel::setIdentifier(const QString &identifier)
{
    if (m_identifier == identifier)
        return;

    m_identifier = identifier;
    emit identifierChanged(m_identifier);
}

void BaseModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

void BaseModel::setModelType(quint8 modelType)
{
    if (m_modelType == modelType)
        return;

    m_modelType = modelType;
    emit modelTypeChanged(m_modelType);
}

void BaseModel::setUuid(const QByteArray &uuid)
{
    if (m_uuid == uuid)
        return;

    m_uuid = uuid;
    emit uuidChanged(m_uuid);
}

void BaseModel::parseQueryResult(const QJsonObject &data)
{
    Q_UNUSED(data)
}

GraphQLQuery BaseModel::query() const
{
    return GraphQLQuery();
}
