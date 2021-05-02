#ifndef REPOSITORYLOCKREASON_H
#define REPOSITORYLOCKREASON_H

#include <QObject>

class RepositoryLockReason {
    Q_GADGET
public:
    enum Reason {
        Unknown,
        Billing,
        Migrating,
        Moving,
        Rename
    };
    Q_ENUM(Reason)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("BILLING")) {
            return RepositoryLockReason::Billing;
        } else if (str == QLatin1String("MIGRATING")) {
            return RepositoryLockReason::Migrating;
        } else if (str == QLatin1String("MOVING")) {
            return RepositoryLockReason::Moving;
        } else if (str == QLatin1String("RENAME")) {
            return RepositoryLockReason::Rename;
        }

        return RepositoryLockReason::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case RepositoryLockReason::Billing:
            return QStringLiteral("BILLING");

        case RepositoryLockReason::Migrating:
            return QStringLiteral("MIGRATING");

        case RepositoryLockReason::Moving:
            return QStringLiteral("MOVING");

        case RepositoryLockReason::Rename:
            return QStringLiteral("RENAME");

        default:
            return QString();
        }
    }
};

#endif // REPOSITORYLOCKREASON_H
