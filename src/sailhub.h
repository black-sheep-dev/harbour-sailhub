#ifndef SAILHUB_H
#define SAILHUB_H

#include <QObject>

#include "api/apiinterface.h"

#include <keepalive/backgroundactivity.h>

class SailHub : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
    Q_PROPERTY(quint32 newNotificationsAvailable READ newNotificationsAvailable NOTIFY newNotificationsAvailableChanged)
    Q_PROPERTY(bool notify READ notify WRITE setNotify NOTIFY notifyChanged)
    Q_PROPERTY(quint8 notificationUpdateInterval READ notificationUpdateInterval WRITE setNotificationUpdateInterval NOTIFY notificationUpdateIntervalChanged)

public:    
    explicit SailHub(QObject *parent = nullptr);
    ~SailHub() override;

    // new
    Q_INVOKABLE ApiInterface *api();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void saveSettings();

    // properties
    const QString &accessToken() const;
    bool notify() const;
    quint8 notificationUpdateInterval() const;
    quint32 newNotificationsAvailable() const;

signals:
    // properties
    void accessTokenChanged(const QString &token);
    void notifyChanged(bool notify);
    void notificationUpdateIntervalChanged(quint8 notificationUpdateInterval);
    void newNotificationsAvailableChanged();

public slots:
    // properties
    void setAccessToken(const QString &token);
    void setNotify(bool notify);
    void setNotificationUpdateInterval(quint8 notificationUpdateInterval);

private slots:
    void onBackgroundActivityRunning();
    void onNotificationsAvailable(const QList<NotificationListItem> &items);

private:
    enum UpdateInterval {
        FiveMinutes,
        TenMinutes,
        FifteenMinutes,
        ThirtyMinutes,
        OneHour
    };

    // wallet
    void loadCredentials();
    void resetCredentials();
    void storeCredentials();


    // settings
    void readSettings();
    void writeSettings();

    ApiInterface *m_api{new ApiInterface(this)};
    BackgroundActivity *m_backgroundActivity{nullptr};
    QStringList m_notifications;
    BackgroundActivity::Frequency m_frequency{BackgroundActivity::FifteenMinutes};

    // properties
    QString m_accessToken;
    bool m_notify{false};
    quint16 m_notificationUpdateInterval{UpdateInterval::FifteenMinutes};
    quint32 m_newNotificationsAvailable{0};
};

#endif // SAILHUB_H
