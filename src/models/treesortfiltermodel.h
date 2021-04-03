#ifndef TREESORTFILTERMODEL_H
#define TREESORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class TreeSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TreeSortFilterModel(QObject *parent = nullptr);

    Q_INVOKABLE void sortModel();

    // QSortFilterProxyModel interface
protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // TREESORTFILTERMODEL_H
