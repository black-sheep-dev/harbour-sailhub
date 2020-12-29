#include "node.h"

Node::Node(QObject *parent) :
    QObject(parent)
{

}

QString Node::nodeId() const
{
    return m_nodeId;
}

void Node::setNodeId(const QString &id)
{
    if (m_nodeId == id)
        return;

    m_nodeId = id;
    emit nodeIdChanged(m_nodeId);
}
