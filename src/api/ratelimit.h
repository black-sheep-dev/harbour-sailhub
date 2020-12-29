#ifndef RATELIMIT_H
#define RATELIMIT_H

#include <QObject>
#include <QDateTime>

struct RateLimit {
    Q_INVOKABLE quint16 limit{0};
    Q_INVOKABLE quint16 remaining{0};
    Q_INVOKABLE QDateTime reset;

    bool operator==(const RateLimit &other) const {
        return this->limit == other.limit
                && this->remaining == other.remaining
                && this->reset == other.reset;
    }
    bool operator!=(const RateLimit &other) const {
        return this->limit != other.limit
                || this->remaining != other.remaining
                || this->reset != other.reset;
    }
};
Q_DECLARE_METATYPE(RateLimit)

#endif // RATELIMIT_H
