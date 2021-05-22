#ifndef MERGESTATESTATUS_H
#define MERGESTATESTATUS_H

#include <QObject>

class MergeStateStatus {
    Q_GADGET
public:
    enum Status {
        Unknown,
        Behind,
        Blocked,
        Clean,
        Dirty,
        Draft,
        HasHooks,
        Unstable
    };
    Q_ENUM(Status)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("UNKNOWN")) {
            return MergeStateStatus::Unknown;
        } else if (str == QLatin1String("BEHIND")) {
            return MergeStateStatus::Behind;
        } else if (str == QLatin1String("BLOCKED")) {
            return MergeStateStatus::Blocked;
        } else if (str == QLatin1String("CLEAN")) {
            return MergeStateStatus::Clean;
        } else if (str == QLatin1String("DIRTY")) {
            return MergeStateStatus::Dirty;
        } else if (str == QLatin1String("DRAFT")) {
            return MergeStateStatus::Draft;
        } else if (str == QLatin1String("HAS_HOOKS")) {
            return MergeStateStatus::HasHooks;
        } else if (str == QLatin1String("UNSTABLE")) {
            return MergeStateStatus::Unstable;
        }

        return MergeStateStatus::Unknown;
    }

    static QString toString(quint8 status){
        switch (status) {
        case MergeStateStatus::Unknown:
            return QStringLiteral("UNKNOWN");

        case MergeStateStatus::Behind:
            return QStringLiteral("BEHIND");

        case MergeStateStatus::Blocked:
            return QStringLiteral("BLOCKED");

        case MergeStateStatus::Clean:
            return QStringLiteral("CLEAN");

        case MergeStateStatus::Dirty:
            return QStringLiteral("DIRTY");

        case MergeStateStatus::Draft:
            return QStringLiteral("DRAFT");

        case MergeStateStatus::HasHooks:
            return QStringLiteral("HAS_HOOKS");

        case MergeStateStatus::Unstable:
            return QStringLiteral("UNSTABLE");

        default:
            return QString();
        }
    }
};

#endif // MERGESTATESTATUS_H
