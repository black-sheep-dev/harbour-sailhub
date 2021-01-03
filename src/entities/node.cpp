#include "node.h"

Node::Node(QObject *parent) :
    QObject(parent)
{

}

QString Node::name() const
{
    return m_name;
}

QString Node::nodeId() const
{
    return m_nodeId;
}

void Node::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Node::setNodeId(const QString &id)
{
    if (m_nodeId == id)
        return;

    m_nodeId = id;
    emit nodeIdChanged(m_nodeId);
}
