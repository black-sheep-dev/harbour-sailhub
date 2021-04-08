#ifndef GRAPHQLQUERY_H
#define GRAPHQLQUERY_H

#include <QJsonObject>

struct GraphQLQuery {
    QString query;
    QJsonObject variables;
};

#endif // GRAPHQLQUERY_H
