#ifndef GRAPHQLCONNECTOR_H
#define GRAPHQLCONNECTOR_H

#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUuid>

#include "queryobject.h"

class GraphQLConnector : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 remaining READ remaining NOTIFY remainingChanged)
    Q_PROPERTY(QDateTime resetAt READ resetAt NOTIFY resetAtChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)

public:
    explicit GraphQLConnector(QObject *parent = nullptr);
    ~GraphQLConnector();

    Q_INVOKABLE void init() {};
    Q_INVOKABLE void request(QueryObject *query);

    // properties
    quint16 remaining() const;
    const QDateTime &resetAt() const;

    const QString &token() const;
    void setToken(const QString &token);

signals:
    // properties
    void remainingChanged();
    void resetAtChanged(); 
    void tokenChanged();

private slots:
    void onRequestFinished();

private:
    void readSettings();
    void writeSettings();

    QNetworkAccessManager *m_manager{new QNetworkAccessManager(this)};

    QHash<QByteArray, QueryObject*> m_queryObjects;

    // properties
    quint16 m_remaining{0};
    QDateTime m_resetAt;
    QString m_token{""};
};

#endif // GRAPHQLCONNECTOR_H
