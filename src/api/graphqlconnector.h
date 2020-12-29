#ifndef GRAPHQLCONNECTOR_H
#define GRAPHQLCONNECTOR_H

#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUuid>

struct GraphQLQuery {
    QString query;
    QJsonObject variables;
};

class GraphQLConnector : public QObject
{
    Q_OBJECT

public:
    explicit GraphQLConnector(const QString &endpoint, QObject *parent = nullptr);

    void sendQuery(const GraphQLQuery &query, quint8 requestType, const QByteArray &requestId = QUuid::createUuid().toByteArray());
    void setEndpoint(const QString &endpoint);
    void setToken(const QString &token);

signals:
    void requestFinished(const QJsonObject &data, quint8 type, const QByteArray &requestId);

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    QByteArray gunzip(const QByteArray &data);

    QString m_endpoint;
    QNetworkAccessManager *m_manager{new QNetworkAccessManager(this)};
    QString m_token;

};

#endif // GRAPHQLCONNECTOR_H
