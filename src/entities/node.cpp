#include "node.h"

Node::Node(QObject *parent) :
    QObject(parent)
{

}

QDateTime Node::createdAt() const
{
    return m_createdAt;
}

quint64 Node::id() const
{
    return m_id;
}

QString Node::name() const
{
    return m_name;
}

QString Node::nodeId() const
{
    return m_nodeId;
}

QDateTime Node::updatedAt() const
{
    return m_updatedAt;
}


void Node::setCreatedAt(const QDateTime &timestamp)
{
    if (m_createdAt == timestamp)
        return;

    m_createdAt = timestamp;
    emit createdAtChanged(m_createdAt);
}


void Node::setId(quint64 id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Node::setNodeId(const QString &id)
{
    if (m_nodeId == id)
        return;

    m_nodeId = id;
    emit nodeIdChanged(m_nodeId);
}

void Node::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Node::setUpdatedAt(const QDateTime &timestamp)
{
    if (m_updatedAt == timestamp)
        return;

    m_updatedAt = timestamp;
    emit updatedAtChanged(m_updatedAt);
}
