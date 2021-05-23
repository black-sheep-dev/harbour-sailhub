#ifndef NODE_H
#define NODE_H

#include <QObject>

struct NodeListItem {
    NodeListItem() = default;
    NodeListItem(const QJsonObject &obj);

    QString name;
    QString nodeId;
    quint32 viewerAbilities{0};
};

class Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString nodeId READ nodeId WRITE setNodeId NOTIFY nodeIdChanged)
    Q_PROPERTY(quint32 viewerAbilities READ viewerAbilities WRITE setViewerAbilities NOTIFY viewerAbilitiesChanged)

public:
    explicit Node(QObject *parent = nullptr);

    QString name() const;
    QString nodeId() const;
    quint32 viewerAbilities() const;

signals:
    void nameChanged(const QString &name);
    void nodeIdChanged(const QString &id);
    void viewerAbilitiesChanged(quint32 abilities);

public slots:
    void setName(const QString &name);
    void setNodeId(const QString &id); 
    void setViewerAbilities(quint32 abilities);

private:
    QString m_name;
    QString m_nodeId;
    quint32 m_viewerAbilities{0};
};

#endif // NODE_H
