#ifndef NODE_H
#define NODE_H

#include <QObject>

class Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nodeId READ nodeId WRITE setNodeId NOTIFY nodeIdChanged)

public:
    explicit Node(QObject *parent = nullptr);

    QString nodeId() const;

signals:
    void nodeIdChanged(const QString &id);

public slots:
    void setNodeId(const QString &id);

private:
    QString m_nodeId;
};

#endif // NODE_H
