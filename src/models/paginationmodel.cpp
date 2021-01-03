#include "paginationmodel.h"

#include <QUuid>

PaginationModel::PaginationModel(QObject *parent) :
    QAbstractListModel(parent),
    m_uuid(QUuid::createUuid().toByteArray())
{

}

void PaginationModel::reset()
{
    setHasNextPage(false);
    setLastItemCursor(QString());

    clear();
}

void PaginationModel::setPageInfo(const PageInfo &info)
{
    setHasNextPage(info.hasNextPage);
    setLastItemCursor(info.lastItemCursor);
    setTotalCount((info.totalCount));
}

bool PaginationModel::hasNextPage() const
{
    return m_hasNextPage;
}

QString PaginationModel::identifier() const
{
    return m_identifier;
}

quint8 PaginationModel::itemCount() const
{
    return m_itemCount;
}

QString PaginationModel::lastItemCursor() const
{
    return m_lastItemCursor;
}

bool PaginationModel::loading() const
{
    return m_loading;
}

quint8 PaginationModel::modelType() const
{
    return m_modelType;
}

quint32 PaginationModel::totalCount() const
{
    return m_totalCount;
}

QByteArray PaginationModel::uuid() const
{
    return m_uuid;
}

void PaginationModel::setHasNextPage(bool hasNextPage)
{
    if (m_hasNextPage == hasNextPage)
        return;

    m_hasNextPage = hasNextPage;
    emit hasNextPageChanged(m_hasNextPage);
}

void PaginationModel::setIdentifier(const QString &identifier)
{
    if (m_identifier == identifier)
        return;

    m_identifier = identifier;
    emit identifierChanged(m_identifier);
}

void PaginationModel::setItemCount(quint8 count)
{
    if (m_itemCount == count)
        return;

    m_itemCount = count;
    emit itemCountChanged(m_itemCount);
}

void PaginationModel::setLastItemCursor(const QString &cursor)
{
    if (m_lastItemCursor == cursor)
        return;

    m_lastItemCursor = cursor;
    emit lastItemCursorChanged(m_lastItemCursor);
}

void PaginationModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

void PaginationModel::setModelType(quint8 modelType)
{
    if (m_modelType == modelType)
        return;

    m_modelType = modelType;
    emit modelTypeChanged(m_modelType);
}

void PaginationModel::setTotalCount(quint32 count)
{
    if (m_totalCount == count)
        return;

    m_totalCount = count;
    emit totalCountChanged(m_totalCount);
}

void PaginationModel::setUuid(const QByteArray &uuid)
{
    if (m_uuid == uuid)
        return;

    m_uuid = uuid;
    emit uuidChanged(m_uuid);
}
