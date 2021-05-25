#ifndef REACTION_H
#define REACTION_H

#include <QObject>

struct ReactionListItem {    
    quint32 count{0};
    quint8 type{0};
    bool viewerReacted{false};
};

class Reaction : public QObject {
    Q_GADGET

public:
    enum ReactionType {
        None            = 0x00,
        ThumbsUp        = 0x01,
        ThumbsDown      = 0x02,
        Laugh           = 0x04,
        Hooray          = 0x08,
        Confused        = 0x10,
        Heart           = 0x20,
        Rocket          = 0x40,
        Eyes            = 0x80
    };
    Q_ENUM(ReactionType)
    Q_DECLARE_FLAGS(ReactionTypes, ReactionType)

    static QString content(quint8 reaction) {
        switch (reaction) {
        case ThumbsUp:
            return QStringLiteral("THUMBS_UP");

        case ThumbsDown:
            return QStringLiteral("THUMBS_DOWN");

        case Laugh:
            return QStringLiteral("LAUGH");

        case Hooray:
            return QStringLiteral("HOORAY");

        case Confused:
            return QStringLiteral("CONFUSED");

        case Heart:
            return QStringLiteral("HEART");

        case Rocket:
            return QStringLiteral("ROCKET");

        case Eyes:
            return QStringLiteral("EYES");

        default:
            return QString();
        }
    };
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Reaction::ReactionTypes)

#endif // REACTION_H
