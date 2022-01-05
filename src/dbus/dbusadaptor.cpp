#include "dbusadaptor.h"

#include <QDebug>

DBusAdaptor::DBusAdaptor(QObject *parent) :
    QDBusAbstractAdaptor(parent)
{

}

void DBusAdaptor::addStar(const QString &username, const QString &reponame)
{
    qDebug() << "DBusAdaptor::addStar: " << username << "/" << reponame;
    emit pleaseAddStar(username, reponame);
}

void DBusAdaptor::openUrl(const QStringList &arguments)
{
    qDebug() << "DBusAdaptor::openUrl" << arguments;
    if (arguments.length() >= 1) {
        const QString &urlToOpen = arguments.first();
        if (urlToOpen.contains("?")) {
            emit pleaseOpenUrl(urlToOpen.left(urlToOpen.indexOf("?")));
        } else {
            emit pleaseOpenUrl(urlToOpen);
        }
    }
}
