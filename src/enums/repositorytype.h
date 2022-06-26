#ifndef REPOSITORYTYPE_H
#define REPOSITORYTYPE_H

#include <QObject>

class RepositoryType {
    Q_GADGET
public:
    enum Type {
        Default,
        Fork,
        Starred
    };
    Q_ENUM(Type)
};


#endif // REPOSITORYTYPE_H
