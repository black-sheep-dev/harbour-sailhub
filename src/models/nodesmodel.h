#ifndef NODESMODEL_H
#define NODESMODEL_H

#include <QAbstractListModel>

#include "src/entities/node.h"

class NodesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)

public:
    QList<Node *> m_nodes;

    enum NodeRoles {
        IdRole      = Qt::UserRole + 1,
        NameRole,
        NodeIdRole,
        CreatedAtRole,
        UpdatedAtRole,
        IdxRole,
        CustomRole  = Qt::UserRole + 20
    };
    Q_ENUM(NodeRoles)

    explicit NodesModel(QObject *parent = nullptr);

    void addNode(Node *node);
    void addNodes(const QList<Node *> &nodes);
    Node *nodeAt(int index);
    Node *nodeById(quint32 id);
    Node *nodeById(const QString &id);
    QList<Node *> nodes() const;
    Q_INVOKABLE void removeNode(int index);
    void removeNode(Node *node);
    Q_INVOKABLE void reset();
    void setNodes(const QList<Node *> &nodes);

    // properties
    bool loading() const;

signals:
    void loadingChanged(bool loading);

public slots:
    void setLoading(bool loading);

private:
    bool nodeExists(Node *node) const;

    bool m_loading{false};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // NODESMODEL_H
