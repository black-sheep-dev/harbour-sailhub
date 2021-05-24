#ifndef REPOSITORYPERMISSION_H
#define REPOSITORYPERMISSION_H

#include <QObject>

class RepositoryPermission {
    Q_GADGET
public:
    enum Permission {
        Unknown,
        Admin,
        Maintain,
        Read,
        Triage,
        Write
    };
    Q_ENUM(Permission)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("ADMIN")) {
            return RepositoryPermission::Admin;
        } else if (str == QLatin1String("MAINTAIN")) {
            return RepositoryPermission::Maintain;
        } else if (str == QLatin1String("READ")) {
            return RepositoryPermission::Read;
        } else if (str == QLatin1String("TRIAGE")) {
            return RepositoryPermission::Triage;
        } else if (str == QLatin1String("WRITE")) {
            return RepositoryPermission::Write;
        }

        return RepositoryPermission::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case RepositoryPermission::Admin:
            return QStringLiteral("ADMIN");

        case RepositoryPermission::Maintain:
            return QStringLiteral("MAINTAIN");

        case RepositoryPermission::Read:
            return QStringLiteral("READ");

        case RepositoryPermission::Triage:
            return QStringLiteral("TRIAGE");

        case RepositoryPermission::Write:
            return QStringLiteral("WRITE");

        default:
            return QString();
        }
    }
};


#endif // REPOSITORYPERMISSION_H
