#ifndef SAILHUB_H
#define SAILHUB_H

#include <QObject>

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
    Q_INVOKABLE void saveSettings();

    // properties
    QString accessToken() const;

signals:
    // properties
    void accessTokenChanged(const QString &token);

public slots:
    // properties
    void setAccessToken(const QString &token);

private:
    void readSettings();
    void writeSettings();

    ApiInterface *m_api{new ApiInterface(this)};

    // properties
    QString m_accessToken;
};

#endif // SAILHUB_H
