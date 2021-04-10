#ifndef REACTION_H
#define REACTION_H

#include <QObject>

class Reaction : public QObject {

    Q_GADGET

public:
    enum ReactionType {
        Undefined       = 0x00,
        Confused        = 0x01,
        Eyes            = 0x02,
        Heart           = 0x04,
        Hooray          = 0x08,
        Laugh           = 0x10,
        Rocket          = 0x20,
        ThumbsDown      = 0x40,
        ThumbsUp        = 0x80
    };
    Q_ENUM(ReactionType)
    Q_DECLARE_FLAGS(ReactionTypes, ReactionType)

    static QString value(quint16 reaction) {
        switch (reaction) {
        case Confused:
            return QStringLiteral("CONFUSED");

        case Eyes:
            return QStringLiteral("EYES");

        case Heart:
            return QStringLiteral("HEART");

        case Hooray:
            return QStringLiteral("HOORAY");

        case Laugh:
            return QStringLiteral("LAUGH");

        case Rocket:
            return QStringLiteral("ROCKET");

        case ThumbsDown:
            return QStringLiteral("THUMBS_DOWN");

        case ThumbsUp:
            return QStringLiteral("THUMBS_UP");

        default:
            return QString();
        }
    }
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Reaction::ReactionTypes)

#endif // REACTION_H
