#ifndef PULLREQUESTSTATE_H
#define PULLREQUESTSTATE_H

#include <QObject>

class PullRequestState {
    Q_GADGET
public:
    enum State {
        Unknown     = 0x0,
        Closed      = 0x1,
        Merged      = 0x2,
        Open        = 0x4
    };
    Q_ENUM(State)
    Q_DECLARE_FLAGS(States, State)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("CLOSED")) {
            return PullRequestState::Closed;
        } else if (str == QLatin1String("MERGED")) {
            return PullRequestState::Merged;
        } else if (str == QLatin1String("OPEN")) {
            return PullRequestState::Open;
        }

        return PullRequestState::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case PullRequestState::Closed:
            return QStringLiteral("CLOSED");

        case PullRequestState::Merged:
            return QStringLiteral("MERGED");

        case PullRequestState::Open:
            return QStringLiteral("OPEN");

        default:
            return QString();
        }
    }
};
Q_DECLARE_OPERATORS_FOR_FLAGS(PullRequestState::States)

#endif // PULLREQUESTSTATE_H
