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
    bool isPrivate{false};
    QString name;
    QString nodeId;
    QString owner;
    quint32 stargazerCount{0};
};

class Repo : public Node
{
    Q_OBJECT

    Q_PROPERTY(QStringList branches READ branches WRITE setBranches NOTIFY branchesChanged)
    Q_PROPERTY(quint32 contributorCount READ contributorCount WRITE setContributorCount NOTIFY contributorCountChanged)
    Q_PROPERTY(QString defaultBranch READ defaultBranch WRITE setDefaultBranch NOTIFY defaultBranchChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(quint32 forkCount READ forkCount WRITE setForkCount NOTIFY forkCountChanged)
    Q_PROPERTY(QString homepageUrl READ homepageUrl WRITE setHomepageUrl NOTIFY homepageUrlChanged)
    Q_PROPERTY(bool isPrivate READ isPrivate WRITE setIsPrivate NOTIFY isPrivateChanged)
    Q_PROPERTY(quint32 issueCount READ issuesCount WRITE setIssuesCount NOTIFY issuesCountChanged)
    Q_PROPERTY(License* license READ license WRITE setLicense NOTIFY licenseChanged)
    Q_PROPERTY(Owner* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(quint32 projects READ projects WRITE setProjects NOTIFY projectsChanged)
    Q_PROPERTY(quint32 pullRequestCount READ pullRequestsCount WRITE setPullRequestsCount NOTIFY pullRequestsCountChanged)
    Q_PROPERTY(QString readme READ readme WRITE setReadme NOTIFY readmeChanged)
    Q_PROPERTY(quint32 releases READ releases WRITE setReleases NOTIFY releasesChanged)
    Q_PROPERTY(quint32 stargazerCount READ stargazerCount WRITE setStargazerCount NOTIFY stargazerCountChanged)
    Q_PROPERTY(bool viewerCanSubscribe READ viewerCanSubscribe WRITE setViewerCanSubscribe NOTIFY viewerCanSubscribeChanged)
    Q_PROPERTY(bool viewerHasStarred READ viewerHasStarred WRITE setViewerHasStarred NOTIFY viewerHasStarredChanged)
    Q_PROPERTY(quint8 viewerSubscription READ viewerSubscription WRITE setViewerSubscription NOTIFY viewerSubscriptionChanged)
    Q_PROPERTY(quint32 watcherCount READ watcherCount WRITE setWatcherCount NOTIFY watcherCountChanged)

public:
    enum RepoSubscription {
        SubscriptionIgnored,
        Subscribed,
        Unsubscribed
    };
    Q_ENUM(RepoSubscription)

    enum RepoType {
        Undefined,
        Fork,
        Organization,
        Search,
        Starred,
        User,
        Watched
    };
    Q_ENUM(RepoType)

    explicit Repo(QObject *parent = nullptr);

    QStringList branches() const;
    quint32 contributorCount() const;
    QString defaultBranch() const;
    QString description() const;
    quint32 forkCount() const;
    QString homepageUrl() const;
    bool isPrivate() const;
    quint32 issuesCount() const;
    License *license() const;
    Owner *owner() const;
    quint32 projects() const;
    quint32 pullRequestsCount() const;
    QString readme() const;
    quint32 releases() const;
    quint32 stargazerCount() const;
    bool viewerCanSubscribe() const;
    bool viewerHasStarred() const;
    quint8 viewerSubscription() const;
    quint32 watcherCount() const;

signals:
    void branchesChanged(const QStringList &branches);
    void contributorCountChanged(quint32 count);
    void defaultBranchChanged(const QString &branch);
    void descriptionChanged(const QString &description);
    void forkCountChanged(quint32 count);
    void homepageUrlChanged(const QString &url);
    void isPrivateChanged(bool isPrivate);
    void issuesCountChanged(quint32 count);
    void licenseChanged(License *license);
    void ownerChanged(Owner *owner);
    void projectsChanged(quint32 projects);
    void pullRequestsCountChanged(quint32 count);
    void readmeChanged(const QString &readme);
    void releasesChanged(quint32 releases);
    void stargazerCountChanged(quint32 count);
    void viewerCanSubscribeChanged(bool subscribable);
    void viewerHasStarredChanged(bool starred);
    void viewerSubscriptionChanged(quint8 state);
    void watcherCountChanged(quint32 count); 

public slots:
    void setBranches(const QStringList &branches);
    void setContributorCount(quint32 count);
    void setDefaultBranch(const QString &branch);
    void setDescription(const QString &description);
    void setForkCount(quint32 count);
    void setHomepageUrl(const QString &url);
    void setIsPrivate(bool isPrivate);
    void setIssuesCount(quint32 count);
    void setLicense(License *license);
    void setOwner(Owner *owner);
    void setProjects(quint32 projects);
    void setPullRequestsCount(quint32 count);
    void setReadme(const QString &readme);
    void setReleases(quint32 releases);
    void setStargazerCount(quint32 count);
    void setViewerCanSubscribe(bool subscribable);
    void setViewerHasStarred(bool starred);
    void setViewerSubscription(quint8 state);
    void setWatcherCount(quint32 count);

private:
    QStringList m_branches;
    quint32 m_contributorCount{0};
    QString m_defaultBranch;
    QString m_description;
    quint32 m_forkCount{0};
    QString m_homepageUrl;
    bool m_isPrivate{false};
    quint32 m_issueCount{0};
    License *m_license;
    Owner *m_owner;
    quint32 m_projects{0};
    quint32 m_pullRequestCount{0};
    quint32 m_stargazerCount{0};
    QString m_readme;
    quint32 m_releases{0};
    bool m_viewerCanSubscribe{false};
    bool m_viewerHasStarred{false};
    quint8 m_viewerSubscription{SubscriptionIgnored};
    quint32 m_watcherCount{0};
};

#endif // REPO_H
