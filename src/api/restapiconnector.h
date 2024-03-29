#ifndef RESTAPICONNECTOR_H
#define RESTAPICONNECTOR_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QUuid>

class RestApiConnector : public QObject
{
    Q_OBJECT

public:
    explicit RestApiConnector(QNetworkAccessManager *manager, QObject *parent = nullptr);

    void setToken(const QString &token);
    const QString &token() const;

    void get(const QString &endpoint, quint8 requestType, const QByteArray &requestId = QUuid::createUuid().toByteArray());

signals:
    void connectionError(quint16 error, const QString &msg, const QByteArray &requestId);
    void requestFinished(const QJsonDocument &data, quint8 requestType, const QByteArray &requestId);

private slots:
    void onRequestFinished();

private:
    QNetworkRequest getRequest(const QString &endpoint);

    QNetworkAccessManager *m_manager{nullptr};
    QString m_token;

};

#endif // RESTAPICONNECTOR_H
