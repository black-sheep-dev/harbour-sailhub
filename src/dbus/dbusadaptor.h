#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#include <QDBusAbstractAdaptor>

class DBusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.nubecula.sailhub")

public:
    explicit DBusAdaptor(QObject *parent = nullptr);

signals:
    void pleaseAddStar(const QString &username, const QString &reponame);
    void pleaseOpenUrl(const QString &url);

public slots:
    void addStar(const QString &username, const QString &reponame);
    void openUrl(const QStringList &arguments);
};

#endif // DBUSADAPTOR_H
