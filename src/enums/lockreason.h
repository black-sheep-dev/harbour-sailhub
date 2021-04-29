#ifndef LOCKREASON_H
#define LOCKREASON_H

#include <QObject>

class LockReason {
    Q_GADGET
public:
    enum Reason {
        Unknown,
        OffTopic,
        Resolved,
        Spam,
        TooHeated
    };
    Q_ENUM(Reason)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("OFF_TOPIC")) {
            return LockReason::OffTopic;
        } else if (str == QLatin1String("RESOLVED")) {
            return LockReason::Resolved;
        } else if (str == QLatin1String("SPAM")) {
            return LockReason::Spam;
        } else if (str == QLatin1String("TOO_HEATED")) {
            return LockReason::TooHeated;
        }

        return LockReason::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case LockReason::OffTopic:
            return QStringLiteral("OFF_TOPIC");

        case LockReason::Resolved:
            return QStringLiteral("RESOLVED");

        case LockReason::Spam:
            return QStringLiteral("SPAM");

        case LockReason::TooHeated:
            return QStringLiteral("TOO_HEATED");

        default:
            return QString();
        }
    }
};

#endif // LOCKREASON_H
