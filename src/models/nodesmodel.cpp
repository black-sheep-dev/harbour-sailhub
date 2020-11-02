#include "nodesmodel.h"

NodesModel::NodesModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

void NodesModel::addNode(Node *node)
{
    if (node == nullptr)
        return;

    if (nodeExists(node))
        return;

    beginInsertRows(QModelIndex(), m_nodes.count(), m_nodes.count());
    node->setParent(this);
    m_nodes.append(node);
    endInsertRows();
}

void NodesModel::addNodes(const QList<Node *> &nodes)
{
    if (nodes.isEmpty())
        return;

    QList<Node *> list;
    for (auto *node : nodes) {
        if (node == nullptr)
            continue;

        if (nodeExists(node))
            continue;

        node->setParent(this);
        list.append(node);
    }

    beginInsertRows(QModelIndex(), m_nodes.count(), m_nodes.count() + list.count() - 1);
    m_nodes.append(list);
    endInsertRows();
}

Node *NodesModel::nodeAt(int index)
{
    if (index < 0 || index >= m_nodes.count())
        return nullptr;

    return m_nodes.at(index);
}

Node *NodesModel::nodeById(quint32 id)
{
    for (auto *node : m_nodes) {
        if (node->id() == id)
            return node;
    }

    return nullptr;
}

Node *NodesModel::nodeById(const QString &id)
{
    for (auto *node : m_nodes) {
        if (node->nodeId() == id)
            return node;
    }

    return nullptr;
}

QList<Node *> NodesModel::nodes() const
{
    return m_nodes;
}

void NodesModel::removeNode(int index)
{
    if (index < 0 || index >= m_nodes.count())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_nodes.takeAt(index)->deleteLater();
    endRemoveRows();
}

void NodesModel::removeNode(Node *node)
{
    const int idx = m_nodes.indexOf(node);

    if (idx < 0)
        return;

    beginRemoveRows(QModelIndex(), idx, idx);
    m_nodes.takeAt(idx)->deleteLater();
    endRemoveRows();
}

void NodesModel::reset()
{
    beginResetModel();
    qDeleteAll(m_nodes.begin(), m_nodes.end());
    m_nodes.clear();
    endResetModel();
}

void NodesModel::setNodes(const QList<Node *> &nodes)
{
    beginResetModel();
    if (!m_nodes.isEmpty())
        qDeleteAll(m_nodes.begin(), m_nodes.end());

    for (auto *node : nodes) {
        node->setParent(this);
    }

    m_nodes = nodes;
    endResetModel();

    setLoading(false);
}

bool NodesModel::loading() const
{
    return m_loading;
}

void NodesModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

bool NodesModel::nodeExists(Node *node) const
{
    for (const auto *n : m_nodes) {
        if (n->nodeId() == node->nodeId())
            return true;
    }

    return false;
}

int NodesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_nodes.count();
}

QVariant NodesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto *node = m_nodes.at(index.row());

    switch (role) {
    case IdRole:
        return node->id();

    case NameRole:
        return node->name();

    case NodeIdRole:
        return node->nodeId();

    case CreatedAtRole:
        return node->createdAt();

    case UpdatedAtRole:
        return node->updatedAt();

    case IdxRole:
        return index.row();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NodesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole]           = "id";
    roles[NameRole]         = "name";
    roles[NodeIdRole]       = "nodeId";
    roles[CreatedAtRole]    = "createdAt";
    roles[UpdatedAtRole]    = "updatedAt";
    roles[IdxRole]          = "idx";

    return roles;
}
