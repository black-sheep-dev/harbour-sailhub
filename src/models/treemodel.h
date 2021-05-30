#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "basemodel.h"

#include "src/entities/treeitem.h"

class TreeModel : public BaseModel
{
    Q_OBJECT

    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

public:
    enum ModelType {
        Undefined,
        Commit,
        Repository
    };
    Q_ENUM(ModelType)

    enum TreeItemRoles {
        ExtensionRole   = Qt::UserRole + 1,
        FileTypeRole,
        NameRole,
        PathRole,
        TypeRole
    };
    Q_ENUM(TreeItemRoles)

    explicit TreeModel(QObject *parent = nullptr);

    void setItems(const QList<TreeItemListItem> &items);

    // properties
    QString branch() const;
    QString path() const;

signals:
    // properties
    void branchChanged(const QString &branch);
    void pathChanged(const QString &path);

public slots:
    // properties
    void setBranch(const QString &branch);
    void setPath(const QString &path);

private:
    QList<TreeItemListItem> m_items;

    // properties
    QString m_branch{QStringLiteral("master")};
    QString m_path{QStringLiteral("/")};


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // BaseModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
        GraphQLQuery query() const override;

};

#endif // TREEMODEL_H
