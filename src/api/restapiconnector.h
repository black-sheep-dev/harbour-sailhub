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
    QString token() const;

    void get(const QString &endpoint, quint8 requestType, const QByteArray &requestId = QUuid::createUuid().toByteArray());

signals:
    void connectionError(quint16 error, const QString &msg);
    void requestFinished(const QJsonDocument &data, quint8 requestType, const QByteArray &requestId);

private slots:
    void onRequestFinished();

private:
    QNetworkAccessManager *m_manager{nullptr};
    QString m_token;

};

#endif // RESTAPICONNECTOR_H
