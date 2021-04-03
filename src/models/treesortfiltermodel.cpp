#include "treesortfiltermodel.h"

#include "treemodel.h"

#include <QDebug>

TreeSortFilterModel::TreeSortFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void TreeSortFilterModel::sortModel()
{
    sort(0, Qt::AscendingOrder);
}

bool TreeSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    //const QVariant leftData = sourceModel()->data(source_left);
    //const QVariant rightData = sourceModel()->data(source_right);

    const quint8 leftType = sourceModel()->data(source_left, TreeModel::TypeRole).toInt();
    const quint8 rightType = sourceModel()->data(source_right, TreeModel::TypeRole).toInt();


    if (leftType > rightType) {
//        const QString leftName = sourceModel()->data(source_left, TreeModel::NameRole).toString();
//        const QString rightName = sourceModel()->data(source_right, TreeModel::NameRole).toString();

//        return (QString::localeAwareCompare(leftName, rightName) < 0);
        return true;
    } else {
        return false;
    }
}
