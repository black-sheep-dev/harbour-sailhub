#ifndef ARRAYMODEL_H
#define ARRAYMODEL_H

#include <QAbstractListModel>

#include <QJsonArray>

class ArrayModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum ArrayRoles {
        ItemRole = Qt::UserRole + 1
    };
    Q_ENUM(ArrayRoles)

    explicit ArrayModel(QObject *parent = nullptr);

    int count() const;

signals:
    void countChanged();

public slots:
    void addItems(const QJsonArray &items);
    void clear();

private:
    QJsonArray m_items;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;


};

#endif // ARRAYMODEL_H
