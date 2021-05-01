#ifndef PAGINATIONMODEL_H
#define PAGINATIONMODEL_H

#include "basemodel.h"


struct PageInfo {
    bool hasNextPage{false};
    QString lastItemCursor;
    quint32 totalCount{0};
};

class PaginationModel : public BaseModel
{
    Q_OBJECT

    Q_PROPERTY(bool hasNextPage READ hasNextPage WRITE setHasNextPage NOTIFY hasNextPageChanged)
    Q_PROPERTY(quint8 itemCount READ itemCount WRITE setItemCount NOTIFY itemCountChanged)
    Q_PROPERTY(QString lastItemCursor READ lastItemCursor WRITE setLastItemCursor NOTIFY lastItemCursorChanged)
    Q_PROPERTY(QString searchPattern READ searchPattern WRITE setSearchPattern NOTIFY searchPatternChanged)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(quint32 sortRole READ sortRole WRITE setSortRole NOTIFY sortRoleChanged)
    Q_PROPERTY(quint8 state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(quint32 totalCount READ totalCount WRITE setTotalCount NOTIFY totalCountChanged)


public:
    explicit PaginationModel(QObject *parent = nullptr);

    Q_INVOKABLE void reset();
    void setPageInfo(const PageInfo &info);
    QJsonObject defaultQueryVariables() const;

    // properties
    bool hasNextPage() const;
    quint8 itemCount() const;
    QString lastItemCursor() const;
    QString searchPattern() const;
    Qt::SortOrder sortOrder() const;
    quint32 sortRole() const;
    quint8 state() const;
    quint32 totalCount() const;

signals:
    // properties
    void hasNextPageChanged(bool hasNextPage);
    void itemCountChanged(quint8 itemCount);
    void lastItemCursorChanged(const QString &cursor);
    void searchPatternChanged(const QString &pattern);
    void sortOrderChanged(Qt::SortOrder order);
    void sortRoleChanged(quint32 role);
    void stateChanged(quint8 state);
    void totalCountChanged(quint32 count);

public slots:
    // properties
    void setHasNextPage(bool hasNextPage);
    void setItemCount(quint8 count);
    void setLastItemCursor(const QString &cursor);
    void setSearchPattern(const QString &pattern);
    void setSortOrder(Qt::SortOrder order);
    void setSortRole(quint32 role);
    void setState(quint8 state);
    void setTotalCount(quint32 count);

private:
    // properties
    bool m_hasNextPage{false};
    quint8 m_itemCount{20};
    QString m_lastItemCursor;
    QString m_searchPattern;
    Qt::SortOrder m_sortOrder{Qt::AscendingOrder};
    quint32 m_sortRole{0};
    quint8 m_state{0};
    quint32 m_totalCount{0};

    // virtual
public:
    virtual void clear() = 0;
    virtual void parseQueryResult(const QJsonObject &data);
    virtual GraphQLQuery query() const;
    virtual QString sortField() const;
};

#endif // PAGINATIONMODEL_H
