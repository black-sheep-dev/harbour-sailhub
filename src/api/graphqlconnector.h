#ifndef GRAPHQLCONNECTOR_H
#define GRAPHQLCONNECTOR_H

#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUuid>

#include "graphqlquery.h"

#include "src/tools/compress.h"

class GraphQLConnector : public QObject
{
    Q_OBJECT

public:
    explicit GraphQLConnector(QString endpoint, QNetworkAccessManager *manager, QObject *parent = nullptr);

    void sendQuery(const GraphQLQuery &query, quint8 requestType, const QByteArray &requestId = QUuid::createUuid().toByteArray());
    void setEndpoint(const QString &endpoint);
    void setToken(const QString &token);
    QString token() const;

signals:
    void connectionError(quint16 error, const QString &msg, const QByteArray &requestId);
    void requestFinished(const QJsonObject &data, quint8 type, const QByteArray &requestId);

private slots:
    void onRequestFinished();

private:
    QString m_endpoint;
    QNetworkAccessManager *m_manager{nullptr};
    QString m_token;

};

#endif // GRAPHQLCONNECTOR_H
