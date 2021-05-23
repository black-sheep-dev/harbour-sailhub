#ifndef ISSUESTATE_H
#define ISSUESTATE_H

#include <QObject>

class IssueState {
    Q_GADGET
public:
    enum State {
        Unknown     = 0x0,
        Closed      = 0x1,
        Open        = 0x2
    };
    Q_ENUM(State)
    Q_DECLARE_FLAGS(States, State)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("CLOSED")) {
            return IssueState::Closed;
        } else if (str == QLatin1String("OPEN")) {
            return IssueState::Open;
        }

        return IssueState::Unknown;
    }

    static QString toString(quint8 reason){
        switch (reason) {
        case IssueState::Closed:
            return QStringLiteral("CLOSED");

        case IssueState::Open:
            return QStringLiteral("OPEN");

        default:
            return QString();
        }
    }
};
Q_DECLARE_OPERATORS_FOR_FLAGS(IssueState::States)

#endif // ISSUESTATE_H
