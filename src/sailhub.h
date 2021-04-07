#ifndef SAILHUB_H
#define SAILHUB_H

#include <QObject>

#include <Sailfish/Secrets/secretmanager.h>

#include "api/apiinterface.h"

class SailHub : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)

public:
    explicit SailHub(QObject *parent = nullptr);
    ~SailHub() override;

    // new
    Q_INVOKABLE ApiInterface *api();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void saveSettings();

    // properties
    QString accessToken() const;

signals:
    // properties
    void accessTokenChanged(const QString &token);

public slots:
    // properties
    void setAccessToken(const QString &token);

private slots:
    void onApiError(quint8 error, const QString &msg);

private:
    // sailfish secrets
    void createCollection();
    void deleteCollection();
    void loadCredentials();
    void storeCredentials();

    // settings
    void readSettings();
    void writeSettings();

    ApiInterface *m_api{new ApiInterface(this)};
    Sailfish::Secrets::SecretManager m_secretManager;
    Sailfish::Secrets::Secret::Identifier m_secretsIdentifier;

    // properties
    QString m_accessToken;
};

#endif // SAILHUB_H
