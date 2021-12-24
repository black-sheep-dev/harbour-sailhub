#include "sailhub.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QFile>
#include <QSettings>
#include <QStandardPaths>

#include <notification.h>

#include "wallet.h"

SailHub::SailHub(QObject *parent) :
    QObject(parent)
{
    readSettings();

    loadCredentials();

    connect(m_api, &ApiInterface::notificationsAvailable, this, &SailHub::onNotificationsAvailable);
}

SailHub::~SailHub()
{
    writeSettings();
}

ApiInterface *SailHub::api()
{
    return m_api;
}

void SailHub::initialize()
{
    // init api if key is available
    if (m_api->token().isEmpty())
        return;

    m_api->getNotifications();
}

void SailHub::reset()
{
    resetCredentials();
}

void SailHub::saveSettings()
{
    writeSettings();
    storeCredentials();
}

const QString &SailHub::accessToken() const
{
    return m_accessToken;
}

bool SailHub::notify() const
{
    return m_notify;
}

quint8 SailHub::notificationUpdateInterval() const
{
    return m_notificationUpdateInterval;
}

void SailHub::setAccessToken(const QString &token)
{
    if (m_accessToken == token)
        return;

    m_accessToken = token;
    emit accessTokenChanged(m_accessToken);

    // functionality
    m_api->setToken(token);
}

void SailHub::setNotify(bool notify)
{
    if (m_notify == notify)
        return;

    m_notify = notify;
    emit notifyChanged(m_notify);

    // functionality
    if (m_notify) {
        if (m_backgroundActivity == nullptr) {
            m_backgroundActivity = new BackgroundActivity(this);
            connect(m_backgroundActivity, &BackgroundActivity::running,
                    this, &SailHub::onBackgroundActivityRunning);
        }
        m_backgroundActivity->wait(m_frequency);

    } else {
        m_backgroundActivity->stop();
        m_backgroundActivity->deleteLater();
        m_backgroundActivity = nullptr;
    }
}

void SailHub::setNotificationUpdateInterval(quint8 notificationUpdateInterval)
{
    if (m_notificationUpdateInterval == notificationUpdateInterval)
        return;

    m_notificationUpdateInterval = notificationUpdateInterval;
    emit notificationUpdateIntervalChanged(m_notificationUpdateInterval);

    // functionality
    switch (m_notificationUpdateInterval) {
    case FiveMinutes:
        m_frequency = BackgroundActivity::FiveMinutes;
        break;

    case TenMinutes:
        m_frequency = BackgroundActivity::TenMinutes;
        break;

    case FifteenMinutes:
        m_frequency = BackgroundActivity::FifteenMinutes;
        break;

    case ThirtyMinutes:
        m_frequency = BackgroundActivity::ThirtyMinutes;
        break;

    case OneHour:
        m_frequency = BackgroundActivity::OneHour;
        break;

    default:
        m_frequency = BackgroundActivity::FifteenMinutes;
        break;
    }
}

void SailHub::onBackgroundActivityRunning()
{
#ifdef QT_DEBUG
    qDebug() << "BACKGROUND ACTIVITY RUNNING: " << QDateTime::currentDateTime();
#endif

    // update notifications
    m_api->getNotifications();

    if (m_backgroundActivity == nullptr)
        return;

    m_backgroundActivity->wait(m_frequency);
}

void SailHub::onNotificationsAvailable(const QList<NotificationListItem> &items)
{
    m_newNotificationsAvailable = 0;

    for (const auto &item : items) {
        if (item.unread) {
            m_newNotificationsAvailable++;
        }
    }

    emit newNotificationsAvailableChanged();

    if (!m_notify)
        return;

    for (const auto &item : items) {
        if (!item.unread) {
            continue;
        }

        if (m_notifications.contains(item.id)) {
            continue;
        }

        Notification notification;
        notification.setAppName(tr("SailHub"));

        switch (item.reason) {
        case NotificationObject::Assign:
            notification.setSummary("Assignment");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-invitation"));
            break;

        case NotificationObject::Author:
            notification.setSummary("Thread created");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-information"));
            break;

        case NotificationObject::Comment:
            notification.setSummary("Commented");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-chat"));
            break;

        case NotificationObject::Invitation:
            notification.setSummary("Invitation");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-invitation"));
            break;

        case NotificationObject::Manual:
            notification.setSummary("Subscribed");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-installed"));
            break;

        case NotificationObject::Mention:
            notification.setSummary("Mentioned");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-sms"));
            break;

        case NotificationObject::ReviewRequest:
            notification.setSummary("Review request");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-information"));
            break;

        case NotificationObject::SecurityAlert:
            notification.setSummary("Security Alert");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-warning"));
            break;

        case NotificationObject::StateChange:
            notification.setSummary("Thread state changed");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-information"));
            break;

        case NotificationObject::Subscribed:
            notification.setSummary("Subscribed");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-installed"));
            break;

        case NotificationObject::TeamMention:
            notification.setSummary("Team mentioned");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-information"));
            break;

        default:
            notification.setSummary("Notification");
            notification.setIcon(QStringLiteral("image://theme/icon-lock-information"));
            break;
        }

        notification.setCategory(QStringLiteral("x-sailhub.info"));
        //notification.setPreviewBody(item.title);
        notification.setBody(item.title);
        notification.setRemoteAction(Notification::remoteAction(
                                        QStringLiteral("default"),
                                        tr("Default"),
                                        QStringLiteral("harbour.sailhub.service"),
                                        QStringLiteral("/harbour/sailhub/service"),
                                        QStringLiteral("harbour.sailhub.service"),
                                        QStringLiteral("open")
                                     ));

        notification.publish();
        connect(&notification, &Notification::clicked, &notification, &Notification::close);

        // save notified item id
        m_notifications.append(item.id);
    }

    emit newNotificationsAvailable();
}

void SailHub::loadCredentials()
{
    Wallet wallet(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/SailHub/secret.wal",
                  (unsigned char *)(APP_SECRET_KEY),
                  (unsigned char *)(APP_SECRET_IV),
                  this);

    setAccessToken(QString::fromUtf8(wallet.requestEntry("token")));
}

void SailHub::resetCredentials()
{
    Wallet wallet(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/SailHub/secret.wal",
                  (unsigned char *)(APP_SECRET_KEY),
                  (unsigned char *)(APP_SECRET_IV),
                  this);

    wallet.reset();
    setAccessToken(QString());
}

void SailHub::storeCredentials()
{
    Wallet wallet(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/SailHub/secret.wal",
                  (unsigned char *)(APP_SECRET_KEY),
                  (unsigned char *)(APP_SECRET_IV),
                  this);

    wallet.setEntry("token", m_accessToken.toUtf8());
}

void SailHub::readSettings()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/SailHub/sailhub.conf";

    if (!QFile(path).exists()) {
           path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/harbour-sailhub/harbour-sailhub.conf";
    }

    QSettings settings(path, QSettings::NativeFormat);


    settings.beginGroup(QStringLiteral("APP"));
    m_api->setPaginationCount(quint8(settings.value(QStringLiteral("pagination"), 20).toInt()));
    setNotificationUpdateInterval(settings.value(QStringLiteral("notification_update_interval"), UpdateInterval::FifteenMinutes).toUInt());
    setNotify(settings.value(QStringLiteral("notify"), false).toBool());
    settings.endGroup();
}

void SailHub::writeSettings()
{
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/org.nubecula/SailHub/sailhub.conf", QSettings::NativeFormat);

    settings.beginGroup(QStringLiteral("APP"));
    settings.setValue(QStringLiteral("pagination"), m_api->paginationCount());
    settings.setValue(QStringLiteral("notify"), m_notify);
    settings.setValue(QStringLiteral("notification_update_interval"), m_notificationUpdateInterval);
    settings.endGroup();
}

quint32 SailHub::newNotificationsAvailable() const
{
    return m_newNotificationsAvailable;
}
