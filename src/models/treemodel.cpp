#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

void TreeModel::setItems(const QList<TreeItemListItem> &items)
{
    beginResetModel();
    m_items.clear();
    m_items = items;
    endResetModel();

    setLoading(false);
}

bool TreeModel::loading() const
{
    return m_loading;
}

void TreeModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = m_items.at(index.row());

    switch (role) {
    case NameRole:
        return item.name;

    case PathRole:
        return item.path;

    case TypeRole:
        return item.type;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole]         = "name";
    roles[PathRole]         = "path";
    roles[TypeRole]         = "type";

    return roles;
}
