#include "profilestatus.h"

ProfileStatus::ProfileStatus(QObject *parent) :
    Node(parent)
{

}

QDateTime ProfileStatus::createdAt() const
{
    return m_createdAt;
}

QString ProfileStatus::emoji() const
{
    return m_emoji;
}

QString ProfileStatus::emojiImage() const
{
    return m_emojiImage;
}

QDateTime ProfileStatus::expiresAt() const
{
    return m_expiresAt;
}

quint8 ProfileStatus::expireStatus() const
{
    return m_expireStatus;
}

bool ProfileStatus::indicatesLimitedAvailability() const
{
    return m_indicatesLimitedAvailability;
}

QString ProfileStatus::message() const
{
    return m_message;
}

QString ProfileStatus::organization() const
{
    return m_organization;
}

QString ProfileStatus::organizationId() const
{
    return m_organizationId;
}

QDateTime ProfileStatus::updatedAt() const
{
    return m_updatedAt;
}

void ProfileStatus::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged(m_createdAt);
}

void ProfileStatus::setEmoji(const QString &emoji)
{
    if (m_emoji == emoji)
        return;

    m_emoji = emoji;
    emit emojiChanged(m_emoji);
}

void ProfileStatus::setEmojiImage(const QString &image)
{
    if (m_emojiImage == image)
        return;

    m_emojiImage = image;
    emit emojiImageChanged(m_emojiImage);
}

void ProfileStatus::setExpiresAt(const QDateTime &expiresAt)
{
    if (m_expiresAt == expiresAt)
        return;

    m_expiresAt = expiresAt;
    emit expiresAtChanged(m_expiresAt);
}

void ProfileStatus::setExpireStatus(quint8 expireStatus)
{
    if (m_expireStatus == expireStatus)
        return;

    m_expireStatus = expireStatus;
    emit expireStatusChanged(m_expireStatus);

    // functionality
    const QDate today = QDateTime::currentDateTimeUtc().date();

    switch (expireStatus) {
    case Never:
        setExpiresAt(QDateTime());
        break;

    case InThirtyMinutes:
        setExpiresAt(QDateTime::currentDateTimeUtc().addSecs(30*60));
        break;

    case InOneHour:
        setExpiresAt(QDateTime::currentDateTimeUtc().addSecs(60*60));
        break;

    case InFourHours:
        setExpiresAt(QDateTime::currentDateTimeUtc().addSecs(4*60*60));
        break;

    case Today:
        setExpiresAt(QDateTime(today.addDays(1), QTime(), Qt::UTC));
        break;

    case ThisWeek:
        setExpiresAt(QDateTime(today.addDays(8 - today.dayOfWeek()), QTime(), Qt::UTC));
        break;

    default:
        setExpiresAt(QDateTime());
        break;
    }
}

void ProfileStatus::setIndicatesLimitedAvailability(bool indicatesLimitedAvailability)
{
    if (m_indicatesLimitedAvailability == indicatesLimitedAvailability)
        return;

    m_indicatesLimitedAvailability = indicatesLimitedAvailability;
    emit indicatesLimitedAvailabilityChanged(m_indicatesLimitedAvailability);
}

void ProfileStatus::setMessage(const QString &message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(m_message);
}

void ProfileStatus::setOrganization(const QString &organization)
{
    if (m_organization == organization)
        return;

    m_organization = organization;
    emit organizationChanged(m_organization);
}

void ProfileStatus::setOrganizationId(const QString &id)
{
    if (m_organizationId == id)
        return;

    m_organizationId = id;
    emit organizationIdChanged(m_organizationId);
}

void ProfileStatus::setUpdatedAt(const QDateTime &updatedAt)
{
    if (m_updatedAt == updatedAt)
        return;

    m_updatedAt = updatedAt;
    emit updatedAtChanged(m_updatedAt);
}
