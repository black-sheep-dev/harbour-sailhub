#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractListModel>

#include "src/entities/treeitem.h"

class TreeModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)

public:
    enum TreeItemRoles {
        NameRole            = Qt::UserRole + 1,
        PathRole,
        TypeRole
    };
    Q_ENUM(TreeItemRoles)

    explicit TreeModel(QObject *parent = nullptr);

    void setItems(const QList<TreeItemListItem> &items);

    // properties
    bool loading() const;
signals:
    // properties
    void loadingChanged(bool loading);

public slots:
    // properties
    void setLoading(bool loading);

private:
    QList<TreeItemListItem> m_items;

    // properties
    bool m_loading{false};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // TREEMODEL_H
