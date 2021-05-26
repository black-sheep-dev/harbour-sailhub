#ifndef PROFILESTATUS_H
#define PROFILESTATUS_H

#include "node.h"

#include <QDateTime>

class ProfileStatus : public Node
{
    Q_OBJECT

    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString emoji READ emoji WRITE setEmoji NOTIFY emojiChanged)
    Q_PROPERTY(QString emojiImage READ emojiImage WRITE setEmojiImage NOTIFY emojiImageChanged)
    Q_PROPERTY(QDateTime expiresAt READ expiresAt WRITE setExpiresAt NOTIFY expiresAtChanged)
    Q_PROPERTY(quint8 expireStatus READ expireStatus WRITE setExpireStatus NOTIFY expireStatusChanged)
    Q_PROPERTY(bool indicatesLimitedAvailability READ indicatesLimitedAvailability WRITE setIndicatesLimitedAvailability NOTIFY indicatesLimitedAvailabilityChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString organization READ organization WRITE setOrganization NOTIFY organizationChanged)
    Q_PROPERTY(QString organizationId READ organizationId WRITE setOrganizationId NOTIFY organizationIdChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)

public:
    enum ExpireStatus {
        Never,
        InThirtyMinutes,
        InOneHour,
        InFourHours,
        Today,
        ThisWeek
    };
    Q_ENUM(ExpireStatus)

    explicit ProfileStatus(QObject *parent = nullptr);
    ProfileStatus(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    QDateTime createdAt() const;
    QString emoji() const;
    QString emojiImage() const;
    QDateTime expiresAt() const;
    quint8 expireStatus() const;
    bool indicatesLimitedAvailability() const;
    QString message() const;
    QString organization() const;
    QString organizationId() const;
    QDateTime updatedAt() const;

signals:
    void createdAtChanged(const QDateTime &createdAt);
    void emojiChanged(const QString &emoji);
    void emojiImageChanged(const QString &image);
    void expiresAtChanged(const QDateTime &expiresAt);
    void expireStatusChanged(quint8 expireStatus);
    void indicatesLimitedAvailabilityChanged(bool indicatesLimitedAvailability);
    void messageChanged(const QString &message);
    void organizationChanged(const QString &organization);
    void organizationIdChanged(const QString &id);
    void updatedAtChanged(const QDateTime &updatedAt);

public slots:
    void setCreatedAt(const QDateTime &createdAt);
    void setEmoji(const QString &emoji);
    void setEmojiImage(const QString &image);
    void setExpiresAt(const QDateTime &expiresAt);
    void setExpireStatus(quint8 expireStatus);
    void setIndicatesLimitedAvailability(bool indicatesLimitedAvailability);
    void setMessage(const QString &message);
    void setOrganization(const QString &organization);
    void setOrganizationId(const QString &id);
    void setUpdatedAt(const QDateTime &updatedAt);

private:
    QDateTime m_createdAt;
    QString m_emoji;
    QString m_emojiImage;
    QDateTime m_expiresAt;
    quint8 m_expireStatus{ExpireStatus::Never};
    bool m_indicatesLimitedAvailability{false};
    QString m_message;
    QString m_organization;
    QString m_organizationId;
    QDateTime m_updatedAt;
};

#endif // PROFILESTATUS_H
