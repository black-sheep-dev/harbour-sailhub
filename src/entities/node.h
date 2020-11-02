#ifndef NODE_H
#define NODE_H

#include <QObject>

#include <QDateTime>

class Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(quint64 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString nodeId READ nodeId WRITE setNodeId NOTIFY nodeIdChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)

public:
    explicit Node(QObject *parent = nullptr);

    QDateTime createdAt() const;
    quint64 id() const;
    QString name() const;
    QString nodeId() const;
    QDateTime updatedAt() const;

signals:
    void createdAtChanged(const QDateTime &timestamp);
    void idChanged(quint64 id);
    void nameChanged(const QString &name);
    void nodeIdChanged(const QString &id);
    void updatedAtChanged(const QDateTime &timestamp);

public slots:
    void setCreatedAt(const QDateTime &timestamp);
    void setId(quint64 id);
    void setNodeId(const QString &id);
    void setName(const QString &name);
    void setUpdatedAt(const QDateTime &timestamp);

private:
    QDateTime m_createdAt;
    quint64 m_id{0};
    QString m_name;
    QString m_nodeId;
    QDateTime m_updatedAt;
};

#endif // NODE_H
