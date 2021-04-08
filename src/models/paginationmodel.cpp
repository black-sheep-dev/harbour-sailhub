#include "paginationmodel.h"

#include <QJsonObject>
#include <QUuid>

#include "src/api/datautils.h"
#include "src/api/queryvars.h"

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

QJsonObject PaginationModel::defaultQueryVariables() const
{
    QJsonObject vars;

    // identifier as NODE_ID
    vars.insert(QueryVar::NODE_ID, m_identifier);

    // sort field
    const QString field = sortField();

    if (!field.isEmpty())
        vars.insert(QueryVar::ORDER_FIELD, field);

    // sort order
    if (m_sortOrder == Qt::AscendingOrder)
        vars.insert(QueryVar::ORDER_DIRECTION, QStringLiteral("ASC"));
    else
        vars.insert(QueryVar::ORDER_DIRECTION, QStringLiteral("DESC"));

    // if next insert item cursor
    if (!m_lastItemCursor.isEmpty()) {
        vars.insert(QueryVar::ITEM_CURSOR, m_lastItemCursor);
    }

    return vars;
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

QString PaginationModel::searchPattern() const
{
    return m_searchPattern;
}

Qt::SortOrder PaginationModel::sortOrder() const
{
    return m_sortOrder;
}

quint32 PaginationModel::sortRole() const
{
    return m_sortRole;
}

quint8 PaginationModel::state() const
{
    return m_state;
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

void PaginationModel::setSearchPattern(const QString &pattern)
{
    if (m_searchPattern == pattern)
        return;

    m_searchPattern = pattern;
    emit searchPatternChanged(m_searchPattern);
}

void PaginationModel::setSortOrder(Qt::SortOrder order)
{
    if (m_sortOrder == order)
        return;

    m_sortOrder = order;
    emit sortOrderChanged(m_sortOrder);
}

void PaginationModel::setSortRole(quint32 role)
{
    if (m_sortRole == role)
        return;

    m_sortRole = role;
    emit sortRoleChanged(m_sortRole);
}

void PaginationModel::setState(quint8 state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
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

void PaginationModel::parseQueryResult(const QJsonObject &data)
{
    Q_UNUSED(data)
}

GraphQLQuery PaginationModel::query() const
{
    return GraphQLQuery();
}

QString PaginationModel::sortField() const
{
    return QString();
}
