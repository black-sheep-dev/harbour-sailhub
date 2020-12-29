#include "sailhub.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QSettings>

SailHub::SailHub(QObject *parent) :
    QObject(parent)
{
    readSettings();
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

}

void SailHub::saveSettings()
{
    writeSettings();
}

QString SailHub::accessToken() const
{
    return m_accessToken;
}

void SailHub::setAccessToken(const QString &token)
{
    if (m_accessToken == token)
        return;

    m_accessToken = token;
    emit accessTokenChanged(m_accessToken);

    // functionality
    m_api->setToken(token);;
}

void SailHub::readSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("APP"));
    m_api->setPaginationCount(quint8(settings.value(QStringLiteral("pagination"), 20).toInt()));
    setAccessToken(settings.value(QStringLiteral("token")).toString());
    settings.endGroup();
}

void SailHub::writeSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("APP"));
    settings.setValue(QStringLiteral("pagination"), m_api->paginationCount());
    settings.setValue(QStringLiteral("token"), m_accessToken);
    settings.endGroup();
}
