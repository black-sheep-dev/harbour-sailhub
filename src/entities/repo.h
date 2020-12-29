#ifndef REPO_H
#define REPO_H

#include "node.h"

#include <QJsonObject>

#include "language.h"
#include "user.h"

#include "src/entities/license.h"
#include "src/entities/owner.h"

struct RepoListItem {
    QString description;
    Language language;
    QString name;
    QString nodeId;
    QString owner;
    quint32 stargazerCount;
};

class Repo : public Node
{
    Q_OBJECT

    Q_PROPERTY(quint32 contributorCount READ contributorCount WRITE setContributorCount NOTIFY contributorCountChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(quint32 forkCount READ forkCount WRITE setForkCount NOTIFY forkCountChanged)
    Q_PROPERTY(QString homepageUrl READ homepageUrl WRITE setHomepageUrl NOTIFY homepageUrlChanged)
    Q_PROPERTY(bool isPrivate READ isPrivate WRITE setIsPrivate NOTIFY isPrivateChanged)
    Q_PROPERTY(quint32 issueCount READ issuesCount WRITE setIssuesCount NOTIFY issuesCountChanged)
    Q_PROPERTY(License* license READ license WRITE setLicense NOTIFY licenseChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Owner* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(quint32 pullRequestCount READ pullRequestsCount WRITE setPullRequestsCount NOTIFY pullRequestsCountChanged)
    Q_PROPERTY(QString readme READ readme WRITE setReadme NOTIFY readmeChanged)
    Q_PROPERTY(quint32 stargazerCount READ stargazerCount WRITE setStargazerCount NOTIFY stargazerCountChanged)
    Q_PROPERTY(quint32 watcherCount READ watcherCount WRITE setWatcherCount NOTIFY watcherCountChanged)

public:
    enum RepoType {
        Undefined,
        User,
        Fork
    };
    Q_ENUM(RepoType)

    explicit Repo(QObject *parent = nullptr);

    quint32 contributorCount() const;
    QString description() const;
    quint32 forkCount() const;
    QString homepageUrl() const;
    bool isPrivate() const;
    quint32 issuesCount() const;
    License *license() const;
    QString name() const;
    Owner *owner() const;
    quint32 pullRequestsCount() const;
    QString readme() const;
    quint32 stargazerCount() const;
    quint32 watcherCount() const;

signals:
    void contributorCountChanged(quint32 count);
    void descriptionChanged(const QString &description);
    void forkCountChanged(quint32 count);
    void homepageUrlChanged(const QString &url);
    void isPrivateChanged(bool isPrivate);
    void issuesCountChanged(quint32 count);
    void licenseChanged(License *license);
    void nameChanged(const QString &name);
    void ownerChanged(Owner *owner);
    void pullRequestsCountChanged(quint32 count);
    void readmeChanged(const QString &readme);
    void stargazerCountChanged(quint32 count);
    void watcherCountChanged(quint32 count); 

public slots:
    void setContributorCount(quint32 count);
    void setDescription(const QString &description);
    void setForkCount(quint32 count);
    void setHomepageUrl(const QString &url);
    void setIsPrivate(bool isPrivate);
    void setIssuesCount(quint32 count);
    void setLicense(License *license);
    void setName(const QString &name);
    void setOwner(Owner *owner);
    void setPullRequestsCount(quint32 count);
    void setReadme(const QString &readme);
    void setStargazerCount(quint32 count);
    void setWatcherCount(quint32 count);

private:
    quint32 m_contributorCount{0};
    QString m_description;
    quint32 m_forkCount{0};
    QString m_homepageUrl;
    bool m_isPrivate{false};
    quint32 m_issueCount{0};
    License *m_license;
    QString m_name;
    Owner *m_owner;
    quint32 m_pullRequestCount{0};
    quint32 m_stargazerCount{0};
    QString m_readme;
    quint32 m_watcherCount{0};

};

#endif // REPO_H
