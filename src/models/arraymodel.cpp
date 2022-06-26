#include "arraymodel.h"

#include <QJsonObject>

ArrayModel::ArrayModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int ArrayModel::count() const
{
    return m_items.count();
}

void ArrayModel::addItems(const QJsonArray &items)
{
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count() + items.count() - 1);
    for (const auto &item : items) {
        m_items.append(item);
    }
    endInsertRows();
    emit countChanged();
}

void ArrayModel::clear()
{
    beginResetModel();
    m_items = QJsonArray();
    endResetModel();
    emit countChanged();
}

int ArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant ArrayModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == ItemRole) {
        return m_items.at(index.row()).toObject();
    }

    return QVariant();
}

QHash<int, QByteArray> ArrayModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemRole] = "item";
    return roles;
}
