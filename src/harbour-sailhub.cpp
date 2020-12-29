#include <QtQuick>

#include <sailfishapp.h>

#include "sailhub.h"
//#include "entities/language.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(QStringLiteral("nubecula.org"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("nubecula.org"));

    qmlRegisterType<ApiInterface>("org.nubecula.harbour.sailhub", 1, 0, "Api");
    qmlRegisterType<License>("org.nubecula.harbour.sailhub", 1, 0, "License");
    qmlRegisterType<Owner>("org.nubecula.harbour.sailhub", 1, 0, "Owner");
    qmlRegisterType<Repo>("org.nubecula.harbour.sailhub", 1, 0, "Repo");
    qmlRegisterType<ReposModel>("org.nubecula.harbour.sailhub", 1, 0, "ReposModel");
    qmlRegisterType<User>("org.nubecula.harbour.sailhub", 1, 0, "User");
    qmlRegisterType<UsersModel>("org.nubecula.harbour.sailhub", 1, 0, "UsersModel");

    qmlRegisterSingletonType<SailHub>("org.nubecula.harbour.sailhub",
                                              1,
                                              0,
                                              "SailHub",
                                              [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {

        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        auto *hub = new SailHub();

        return hub;
    });


    return SailfishApp::main(argc, argv);
}
