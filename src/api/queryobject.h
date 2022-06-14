#ifndef QUERYOBJECT_H
#define QUERYOBJECT_H

#include <QObject>

class QueryObject : public QObject
{
    Q_OBJECT
public:
    explicit QueryObject(QObject *parent = nullptr);

signals:

};

#endif // QUERYOBJECT_H
