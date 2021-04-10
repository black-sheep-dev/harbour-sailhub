#include <QtQuick>

#include <sailfishapp.h>

#include "sailhub.h"
#include "entities/file.h"
#include "models/treesortfiltermodel.h"
//#include "entities/language.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(QStringLiteral("nubecula.org"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("nubecula.org"));

    qmlRegisterType<ApiInterface>("org.nubecula.harbour.sailhub", 1, 0, "Api");
    qmlRegisterType<Comment>("org.nubecula.harbour.sailhub", 1, 0, "Comment");
    qmlRegisterType<CommentsModel>("org.nubecula.harbour.sailhub", 1, 0, "CommentsModel");
    qmlRegisterType<File>("org.nubecula.harbour.sailhub", 1, 0, "File");
    qmlRegisterType<Label>("org.nubecula.harbour.sailhub", 1, 0, "LabelEntity");
    qmlRegisterType<LabelsModel>("org.nubecula.harbour.sailhub", 1, 0, "LabelsModel");
    qmlRegisterType<License>("org.nubecula.harbour.sailhub", 1, 0, "License");
    qmlRegisterType<Issue>("org.nubecula.harbour.sailhub", 1, 0, "Issue");
    qmlRegisterType<IssuesModel>("org.nubecula.harbour.sailhub", 1, 0, "IssuesModel");
    qmlRegisterType<Organization>("org.nubecula.harbour.sailhub", 1, 0, "Organization");
    qmlRegisterType<OrganizationsModel>("org.nubecula.harbour.sailhub", 1, 0, "OrganizationsModel");
    qmlRegisterType<Owner>("org.nubecula.harbour.sailhub", 1, 0, "Owner");
    qmlRegisterType<PullRequest>("org.nubecula.harbour.sailhub", 1, 0, "PullRequest");
    qmlRegisterType<PullRequestsModel>("org.nubecula.harbour.sailhub", 1, 0, "PullRequestsModel");
    qmlRegisterType<Repo>("org.nubecula.harbour.sailhub", 1, 0, "Repo");
    qmlRegisterType<ReposModel>("org.nubecula.harbour.sailhub", 1, 0, "ReposModel");
    qmlRegisterType<TreeItem>("org.nubecula.harbour.sailhub", 1, 0, "TreeItem");
    qmlRegisterType<TreeModel>("org.nubecula.harbour.sailhub", 1, 0, "TreeModel");
    qmlRegisterType<TreeSortFilterModel>("org.nubecula.harbour.sailhub", 1, 0, "TreeSortFilterModel");
    qmlRegisterType<User>("org.nubecula.harbour.sailhub", 1, 0, "User");
    qmlRegisterType<UsersModel>("org.nubecula.harbour.sailhub", 1, 0, "UsersModel");

    qmlRegisterSingletonType<SailHub>("org.nubecula.harbour.sailhub",
                                              1,
                                              0,
                                              "SailHub",
                                              [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {

        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        auto app = new SailHub();

        return app;
    });


    return SailfishApp::main(argc, argv);
}
