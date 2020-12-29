#ifndef PAGINATIONMODEL_H
#define PAGINATIONMODEL_H

#include <QAbstractListModel>

#include "src/api/queries.h"

struct PageInfo {
    bool hasNextPage{false};
    QString lastItemCursor;
    quint32 totalCount{0};
};

class PaginationModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool hasNextPage READ hasNextPage WRITE setHasNextPage NOTIFY hasNextPageChanged)
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(quint8 itemCount READ itemCount WRITE setItemCount NOTIFY itemCountChanged)
    Q_PROPERTY(QString lastItemCursor READ lastItemCursor WRITE setLastItemCursor NOTIFY lastItemCursorChanged)
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(quint8 modelType READ modelType WRITE setModelType NOTIFY modelTypeChanged)
    Q_PROPERTY(QByteArray uuid READ uuid WRITE setUuid NOTIFY uuidChanged)

public:
    explicit PaginationModel(QObject *parent = nullptr);

    void setPageInfo(const PageInfo &info);

    // properties
    bool hasNextPage() const;
    QString identifier() const;
    quint8 itemCount() const;
    QString lastItemCursor() const;
    bool loading() const;
    quint8 modelType() const;
    QByteArray uuid() const;

signals:
    // properties
    void hasNextPageChanged(bool hasNextPage);
    void identifierChanged(const QString &identifier);
    void itemCountChanged(quint8 itemCount);
    void lastItemCursorChanged(const QString &cursor);
    void loadingChanged(bool loading);
    void modelTypeChanged(quint8 modelType);
    void uuidChanged(const QByteArray &uuid);

public slots:
    // properties
    void setHasNextPage(bool hasNextPage);
    void setIdentifier(const QString &identifier);
    void setItemCount(quint8 count);
    void setLastItemCursor(const QString &cursor);
    void setLoading(bool loading);
    void setModelType(quint8 modelType);
    void setUuid(const QByteArray &uuid);

private:
    // properties
    bool m_hasNextPage{false};
    QString m_identifier;
    quint8 m_itemCount{20};
    QString m_lastItemCursor;
    bool m_loading{true};
    quint8 m_modelType{0};
    QByteArray m_uuid;

};

#endif // PAGINATIONMODEL_H
