#ifndef VIEWER_H
#define VIEWER_H

#include <QObject>

class Viewer : public QObject
{
    Q_GADGET

public:
    enum Ability {
        CanNone                 = 0x0000,
        CanAdminister           = 0x0001,
        CanApplySuggestion      = 0x0002,
        CanCreateProjects       = 0x0004,
        CanDelete               = 0x0008,
        CanDeleteHeadRef        = 0x0010,
        CanDisableAutoMerge     = 0x0020,
        CanEnableAutoMerge      = 0x0040,
        CanReact                = 0x0080,
        CanSubscribe            = 0x0100,
        CanUpdate               = 0x0200,
        CanUpdateTopics         = 0x0400
    };
    Q_ENUM(Ability)
    Q_DECLARE_FLAGS(Abilities, Ability)

};
Q_DECLARE_OPERATORS_FOR_FLAGS(Viewer::Abilities)

#endif // VIEWER_H
