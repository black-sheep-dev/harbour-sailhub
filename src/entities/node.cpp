#include "node.h"

#include <QJsonObject>

#include "src/api/keys.h"
#include "src/api/datautils.h"

// List Item
NodeListItem::NodeListItem(const QJsonObject &data)
{
    nodeId = data.value(ApiKey::ID).toString();
    name = data.value(ApiKey::NAME).toString();
    viewerAbilities = DataUtils::getViewerAbilities(data);
}

// Object
Node::Node(QObject *parent) :
    QObject(parent)
{

}

Node::Node(const QJsonObject &data, QObject *parent) :
    QObject(parent)
{
    setData(data);
}

void Node::setData(const QJsonObject &data)
{
    setNodeId(data.value(ApiKey::ID).toString());
    setName(data.value(ApiKey::NAME).toString());
    setViewerAbilities(DataUtils::getViewerAbilities(data));
}

const QString &Node::name() const
{
    return m_name;
}

const QString &Node::nodeId() const
{
    return m_nodeId;
}

quint32 Node::viewerAbilities() const
{
    return m_viewerAbilities;
}

void Node::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

void Node::setNodeId(const QString &id)
{
    if (m_nodeId == id)
        return;

    m_nodeId = id;
    emit nodeIdChanged();
}

void Node::setViewerAbilities(quint32 viewerAbilities)
{
    if (m_viewerAbilities == viewerAbilities)
        return;

    m_viewerAbilities = viewerAbilities;
    emit viewerAbilitiesChanged();
}
