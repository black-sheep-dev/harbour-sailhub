#include "sailhub.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QSettings>

#include <Sailfish/Secrets/createcollectionrequest.h>
#include <Sailfish/Secrets/deletecollectionrequest.h>
#include <Sailfish/Secrets/deletesecretrequest.h>
#include <Sailfish/Secrets/storesecretrequest.h>
#include <Sailfish/Secrets/storedsecretrequest.h>

#include <notification.h>

const QString SAILHUB_COLLECTION_NAME            = QStringLiteral("sailhub");
const QString SAILHUB_COLLECTION_NAME_DEBUG      = QStringLiteral("sailhubdebug");

SailHub::SailHub(QObject *parent) :
    QObject(parent),
    m_secretsIdentifier(Sailfish::Secrets::Secret::Identifier(
                                QStringLiteral("secrets"),
                                #ifdef QT_DEBUG
                                    SAILHUB_COLLECTION_NAME_DEBUG,
                                #else
                                    SAILHUB_COLLECTION_NAME,
                                #endif
                                Sailfish::Secrets::SecretManager::DefaultEncryptedStoragePluginName))
{
    readSettings();
    loadCredentials();

    connect(m_api, &ApiInterface::apiError, this, &SailHub::onApiError);
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
    if (m_api->token().isEmpty())
        return;

    m_api->getNotifications();
}

void SailHub::reset()
{
    deleteCollection();
}

void SailHub::saveSettings()
{
    writeSettings();
}

QString SailHub::accessToken() const
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
    storeCredentials();
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

void SailHub::onApiError(quint8 error, const QString &msg)
{
    Notification notification;
    notification.setAppName(tr("SailHub"));


    if (error == ApiInterface::ErrorUnauthorized) {
        notification.setIcon(QStringLiteral("image://theme/icon-lock-locked"));
        notification.setCategory(QStringLiteral("x-sailhub.unauthorized"));
        notification.setSummary(tr("Unauthorized"));
        notification.setBody(tr("Did you provide a valid access token?"));
        notification.setRemoteAction(Notification::remoteAction(
                                        QStringLiteral("default"),
                                        tr("Default"),
                                        QStringLiteral("harbour.sailhub.service"),
                                        QStringLiteral("/harbour/sailhub/service"),
                                        QStringLiteral("harbour.sailhub.service"),
                                        QStringLiteral("token")
                                     ));

    } else {
        notification.setIcon(QStringLiteral("image://theme/icon-lock-warning"));
        notification.setCategory(QStringLiteral("x-sailhub.error"));
        notification.setSummary(tr("Error"));
        notification.setPreviewBody(tr("An error occured when connecting to GitHub!"));
        notification.setBody(tr("An error occured when connecting to GitHub!") + " " + msg);
//        notification.setRemoteAction(Notification::remoteAction(
//                                        QStringLiteral("default"),
//                                        tr("Default"),
//                                        QStringLiteral("harbour.sailhub.service"),
//                                        QStringLiteral("/harbour/sailhub/service"),
//                                        QStringLiteral("harbour.sailhub.service"),
//                                        QStringLiteral("open")
//                                     ));
    }

    notification.publish();
    connect(&notification, &Notification::clicked, &notification, &Notification::close);
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
    if (!m_notify)
        return;

    for (const auto &item : items) {
        if (m_notifications.contains(item.id))
            continue;

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
}

void SailHub::createCollection()
{
#ifndef DISABLE_SAILFISH_SECRETS

    Sailfish::Secrets::CreateCollectionRequest createCollection;
    createCollection.setManager(&m_secretManager);
    createCollection.setCollectionLockType(Sailfish::Secrets::CreateCollectionRequest::DeviceLock);
    createCollection.setDeviceLockUnlockSemantic(Sailfish::Secrets::SecretManager::DeviceLockKeepUnlocked);
    createCollection.setUserInteractionMode(Sailfish::Secrets::SecretManager::SystemInteraction);
    createCollection.setCollectionName(
                                   #ifdef QT_DEBUG
                                       SAILHUB_COLLECTION_NAME_DEBUG
                                   #else
                                       SAILHUB_COLLECTION_NAME
                                   #endif
                                       );
    createCollection.setStoragePluginName(Sailfish::Secrets::SecretManager::DefaultEncryptedStoragePluginName);
    createCollection.setEncryptionPluginName(Sailfish::Secrets::SecretManager::DefaultEncryptedStoragePluginName);
    createCollection.startRequest();
    createCollection.waitForFinished();

#ifdef QT_DEBUG
    qDebug() << createCollection.result().code();
    qDebug() << createCollection.result().errorMessage();
#endif

#endif
}

void SailHub::deleteCollection()
{
#ifndef DISABLE_SAILFISH_SECRETS

    Sailfish::Secrets::DeleteCollectionRequest deleteCollection;
    deleteCollection.setManager(&m_secretManager);
    deleteCollection.setCollectionName(
                    #ifdef QT_DEBUG
                        SAILHUB_COLLECTION_NAME_DEBUG
                    #else
                        SAILHUB_COLLECTION_NAME
                    #endif
                );
    deleteCollection.setStoragePluginName(Sailfish::Secrets::SecretManager::DefaultEncryptedStoragePluginName);
    deleteCollection.setUserInteractionMode(Sailfish::Secrets::SecretManager::SystemInteraction);
    deleteCollection.startRequest();
    deleteCollection.waitForFinished();


#ifdef QT_DEBUG
    qDebug() << deleteCollection.result().code();
    qDebug() << deleteCollection.result().errorMessage();
#endif

#endif
}

void SailHub::loadCredentials()
{
#ifndef DISABLE_SAILFISH_SECRETS
    auto fetchCode = new Sailfish::Secrets::StoredSecretRequest;

    fetchCode->setManager(&m_secretManager);
    fetchCode->setUserInteractionMode(Sailfish::Secrets::SecretManager::SystemInteraction);
    fetchCode->setIdentifier(m_secretsIdentifier);

    fetchCode->startRequest();
    fetchCode->waitForFinished();

#ifdef QT_DEBUG
    qDebug() << QStringLiteral("CREDENTIALS LOADED");
    qDebug() << fetchCode->result().code();

    if (fetchCode->result().errorCode() > 0) {
        qDebug() << fetchCode->result().errorCode();
        qDebug() << fetchCode->result().errorMessage();
    }
#endif

    if (fetchCode->result().code() != Sailfish::Secrets::Result::Succeeded) {
        fetchCode->deleteLater();
        return;
    }

    setAccessToken(fetchCode->secret().data());

    fetchCode->deleteLater();

#endif
}

void SailHub::storeCredentials()
{
#ifndef DISABLE_SAILFISH_SECRETS

    // reset and create
    deleteCollection();
    createCollection();

    // store data in wallet
    Sailfish::Secrets::Secret secret(m_secretsIdentifier);
    secret.setData(m_accessToken.toUtf8());

    Sailfish::Secrets::StoreSecretRequest storeCode;
    storeCode.setManager(&m_secretManager);
    storeCode.setSecretStorageType(Sailfish::Secrets::StoreSecretRequest::CollectionSecret);
    storeCode.setUserInteractionMode(Sailfish::Secrets::SecretManager::SystemInteraction);
    storeCode.setSecret(secret);
    storeCode.startRequest();
    storeCode.waitForFinished();

    if (storeCode.result().errorCode())
        return;

    #ifdef QT_DEBUG
        qDebug() << storeCode.result().code();
        qDebug() << storeCode.result().errorMessage();
    #endif

#endif
}

void SailHub::readSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("APP"));
    m_api->setPaginationCount(quint8(settings.value(QStringLiteral("pagination"), 20).toInt()));
    setNotificationUpdateInterval(settings.value(QStringLiteral("notification_update_interval"), UpdateInterval::FifteenMinutes).toUInt());
    setNotify(settings.value(QStringLiteral("notify"), false).toBool());


#ifdef DISABLE_SAILFISH_SECRETS
    setAccessToken(settings.value(QStringLiteral("token")).toString());
#endif
    settings.endGroup();
}

void SailHub::writeSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("APP"));
    settings.setValue(QStringLiteral("pagination"), m_api->paginationCount());
    settings.setValue(QStringLiteral("notify"), m_notify);
    settings.setValue(QStringLiteral("notification_update_interval"), m_notificationUpdateInterval);

#ifdef DISABLE_SAILFISH_SECRETS
    settings.setValue(QStringLiteral("token"), m_accessToken);
#endif
    settings.endGroup();
}
