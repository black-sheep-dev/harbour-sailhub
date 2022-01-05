#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H

#include <QObject>

#include "dbusadaptor.h"

const QString INTERFACE_NAME = "org.nubecula.sailhub";

class DBusInterface : public QObject
{
    Q_OBJECT
public:
    explicit DBusInterface(QObject *parent = nullptr);

    DBusAdaptor *getDBusAdaptor();

private:
    DBusAdaptor *m_adaptor{nullptr};

};

#endif // DBUSINTERFACE_H
