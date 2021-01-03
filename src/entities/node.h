#ifndef NODE_H
#define NODE_H

#include <QObject>

class Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString nodeId READ nodeId WRITE setNodeId NOTIFY nodeIdChanged)

public:
    explicit Node(QObject *parent = nullptr);

    QString name() const;
    QString nodeId() const;

signals:
    void nameChanged(const QString &name);
    void nodeIdChanged(const QString &id);

public slots:
    void setName(const QString &name);
    void setNodeId(const QString &id);

private:
    QString m_name;
    QString m_nodeId;
};

#endif // NODE_H
