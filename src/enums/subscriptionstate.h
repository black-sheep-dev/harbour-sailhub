#ifndef SUBSCRIPTIONSTATE_H
#define SUBSCRIPTIONSTATE_H

#include <QObject>

class SubscriptionState {
    Q_GADGET
public:
    enum State {
        Unknown,
        Ignored,
        Subscribed,
        Unsubscribed
    };
    Q_ENUM(State)

    static quint8 fromString(const QString &str) {
        if (str == QLatin1String("IGNORED")) {
            return SubscriptionState::Ignored;
        } else if (str == QLatin1String("SUBSCRIBED")) {
            return SubscriptionState::Subscribed;
        } else if (str == QLatin1String("UNSUBSCRIBED")) {
            return SubscriptionState::Unsubscribed;
        }

        return SubscriptionState::Unknown;
    }

    static QString toString(quint8 state) {
        switch (state) {
        case SubscriptionState::Ignored:
            return QStringLiteral("IGNORED");

        case SubscriptionState::Subscribed:
            return QStringLiteral("SUBSCRIBED");

        case SubscriptionState::Unsubscribed:
            return QStringLiteral("UNSUBSCRIBED");

        default:
            return QString();
        }
    }
};

#endif // SUBSCRIPTIONSTATE_H
