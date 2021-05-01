#include "paginationmodel.h"

#include <QJsonObject>

#include "src/api/datautils.h"
#include "src/api/queryvars.h"

PaginationModel::PaginationModel(QObject *parent) :
    BaseModel(parent)
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
    vars.insert(QueryVar::NODE_ID, identifier());

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

quint8 PaginationModel::itemCount() const
{
    return m_itemCount;
}

QString PaginationModel::lastItemCursor() const
{
    return m_lastItemCursor;
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

void PaginationModel::setHasNextPage(bool hasNextPage)
{
    if (m_hasNextPage == hasNextPage)
        return;

    m_hasNextPage = hasNextPage;
    emit hasNextPageChanged(m_hasNextPage);
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
