#ifndef REPO_H
#define REPO_H

#include "node.h"

#include <QDateTime>
#include <QJsonObject>

#include "language.h"
#include "user.h"

#include "src/enums/repositorylockreason.h"
#include "src/enums/subscriptionstate.h"
#include "src/entities/license.h"
#include "src/entities/owner.h"

struct RepoListItem : public NodeListItem {
    RepoListItem() = default;
    RepoListItem(const QJsonObject &data);

    QDateTime createdAt;
    QString description;
    quint16 flags{0};
    Language language;
    quint8 lockReason{RepositoryLockReason::Unknown};
    QString ownerAvatar;
    QString ownerLogin;
    QDateTime pushedAt;
    quint32 stargazerCount{0};
    QDateTime updatedAt;
};

class Repo : public Node
{
    Q_OBJECT

    Q_PROPERTY(QStringList branches READ branches WRITE setBranches NOTIFY branchesChanged)
    Q_PROPERTY(quint32 contributorCount READ contributorCount WRITE setContributorCount NOTIFY contributorCountChanged)
    Q_PROPERTY(QString defaultBranch READ defaultBranch WRITE setDefaultBranch NOTIFY defaultBranchChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(quint32 discussionCount READ discussionCount WRITE setDiscussionCount NOTIFY discussionCountChanged)
    Q_PROPERTY(quint8 features READ features WRITE setFeatures NOTIFY featuresChanged)
    Q_PROPERTY(quint16 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(quint32 forkCount READ forkCount WRITE setForkCount NOTIFY forkCountChanged)
    Q_PROPERTY(bool hasFundingLinks READ hasFundingLinks WRITE setHasFundingLinks NOTIFY hasFundingLinksChanged)
    Q_PROPERTY(QString homepageUrl READ homepageUrl WRITE setHomepageUrl NOTIFY homepageUrlChanged)
    Q_PROPERTY(quint32 issueCount READ issuesCount WRITE setIssuesCount NOTIFY issuesCountChanged)
    Q_PROPERTY(quint32 labelCount READ labelCount WRITE setLabelCount NOTIFY labelCountChanged)
    Q_PROPERTY(License* license READ license WRITE setLicense NOTIFY licenseChanged)
    Q_PROPERTY(quint8 lockReason READ lockReason WRITE setLockReason NOTIFY lockReasonChanged)
    Q_PROPERTY(Owner* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(QString parentId READ parentId WRITE setParentId NOTIFY parentIdChanged)
    Q_PROPERTY(QString parentName READ parentName WRITE setParentName NOTIFY parentNameChanged)
    Q_PROPERTY(quint32 projects READ projects WRITE setProjects NOTIFY projectsChanged)
    Q_PROPERTY(quint32 pullRequestCount READ pullRequestsCount WRITE setPullRequestsCount NOTIFY pullRequestsCountChanged)
    Q_PROPERTY(quint32 releaseCount READ releaseCount WRITE setReleaseCount NOTIFY releaseCountChanged)
    Q_PROPERTY(quint32 stargazerCount READ stargazerCount WRITE setStargazerCount NOTIFY stargazerCountChanged)
    Q_PROPERTY(bool viewerHasStarred READ viewerHasStarred WRITE setViewerHasStarred NOTIFY viewerHasStarredChanged)
    Q_PROPERTY(quint8 viewerPermission READ viewerPermission WRITE setViewerPermission NOTIFY viewerPermissionChanged)
    Q_PROPERTY(quint8 viewerSubscription READ viewerSubscription WRITE setViewerSubscription NOTIFY viewerSubscriptionChanged)
    Q_PROPERTY(quint32 vulnerabilityAlertCount READ vulnerabilityAlertCount WRITE setVulnerabilityAlertCount NOTIFY vulnerabilityAlertCountChanged)
    Q_PROPERTY(quint32 watcherCount READ watcherCount WRITE setWatcherCount NOTIFY watcherCountChanged)

public:
    enum RepoFeature {
        FeatureNone         = 0x00,
        FeatureIssues       = 0x01,
        FeatureProjects     = 0x02,
        FeatureWiki         = 0x04
    };
    Q_ENUM(RepoFeature)
    Q_DECLARE_FLAGS(RepoFeatures, RepoFeature)

    enum RepoFlag {
        FlagNone                        = 0x0000,
        IsArchived                      = 0x0001,
        IsBlankIssuesEnabled            = 0x0002,
        IsDisabled                      = 0x0004,
        IsEmpty                         = 0x0008,
        IsFork                          = 0x0010,
        IsInOrganization                = 0x0020,
        IsLocked                        = 0x0040,
        IsMirror                        = 0x0080,
        IsPrivate                       = 0x0100,
        IsSecurityPolicyEnabled         = 0x0200,
        IsTemplate                      = 0x0400,
        IsUserConfigurationRepository   = 0x0800
    };
    Q_ENUM(RepoFlag)
    Q_DECLARE_FLAGS(RepoFlags, RepoFlag)

    enum RepoPermission {
        PermissionNone,
        PermissionAdmin,
        PermissionMaintain,
        PermissionRead,
        PermissionTriage,
        PermissionWrite
    };
    Q_ENUM(RepoPermission)

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
    Repo(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    const QStringList &branches() const;
    quint32 contributorCount() const;
    const QString &defaultBranch() const;
    const QString &description() const;
    quint32 discussionCount() const;
    quint8 features() const;
    quint16 flags() const;
    quint32 forkCount() const;
    bool hasFundingLinks() const;
    const QString &homepageUrl() const;
    quint32 issuesCount() const;
    quint32 labelCount() const;
    License *license() const;
    quint8 lockReason() const;
    Owner *owner() const;
    const QString &parentId() const;
    const QString &parentName() const;
    quint32 projects() const;
    quint32 pullRequestsCount() const;
    quint32 releaseCount() const;
    quint32 stargazerCount() const;
    bool viewerHasStarred() const;
    quint8 viewerPermission() const;
    quint8 viewerSubscription() const;
    quint32 vulnerabilityAlertCount() const;
    quint32 watcherCount() const;

signals:
    // properties
    void branchesChanged();
    void contributorCountChanged();
    void defaultBranchChanged();
    void descriptionChanged();
    void discussionCountChanged();
    void featuresChanged();
    void flagsChanged();
    void forkCountChanged();
    void hasFundingLinksChanged();
    void homepageUrlChanged();
    void issuesCountChanged();
    void labelCountChanged();
    void licenseChanged();
    void lockReasonChanged();
    void ownerChanged();
    void parentIdChanged();
    void parentNameChanged();
    void projectsChanged();
    void pullRequestsCountChanged();
    void releaseCountChanged();
    void stargazerCountChanged();
    void viewerHasStarredChanged();
    void viewerPermissionChanged();
    void viewerSubscriptionChanged();
    void vulnerabilityAlertCountChanged();
    void watcherCountChanged();

public slots:
    // properties
    void setBranches(const QStringList &branches);
    void setContributorCount(quint32 count);
    void setDefaultBranch(const QString &branch);
    void setDescription(const QString &description);
    void setDiscussionCount(quint32 count);
    void setFeatures(quint8 features);
    void setFlags(quint16 flags);
    void setForkCount(quint32 count);
    void setHasFundingLinks(bool hasFundingLinks);
    void setHomepageUrl(const QString &url);
    void setIssuesCount(quint32 count);
    void setLabelCount(quint32 count);
    void setLicense(License *license);
    void setLockReason(quint8 reason);
    void setOwner(Owner *owner);
    void setParentId(const QString &id);
    void setParentName(const QString &name);
    void setProjects(quint32 projects);
    void setPullRequestsCount(quint32 count);
    void setReleaseCount(quint32 releaseCount);
    void setStargazerCount(quint32 count);
    void setViewerHasStarred(bool starred);
    void setViewerPermission(quint8 permission);
    void setViewerSubscription(quint8 state);
    void setVulnerabilityAlertCount(quint32 count);
    void setWatcherCount(quint32 count);

private:
    // properties
    QStringList m_branches;
    quint32 m_contributorCount{0};
    QString m_defaultBranch;
    QString m_description;
    quint32 m_discussionCount{0};
    quint8 m_features{FeatureNone};
    quint16 m_flags{FlagNone};
    quint32 m_forkCount{0};
    bool m_hasFundingLinks{false};
    QString m_homepageUrl;
    quint32 m_issueCount{0};
    quint32 m_labelCount{0};
    License *m_license{nullptr};
    quint8 m_lockReason{RepositoryLockReason::Unknown};
    Owner *m_owner{nullptr};
    QString m_parentId;
    QString m_parentName;
    quint32 m_projects{0};
    quint32 m_pullRequestCount{0};
    quint32 m_stargazerCount{0};
    quint32 m_releaseCount{0};
    bool m_viewerHasStarred{false};
    quint8 m_viewerPermission{PermissionNone};
    quint8 m_viewerSubscription{SubscriptionState::Ignored};
    quint32 m_vulnerabilityAlertCount{0};
    quint32 m_watcherCount{0};
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Repo::RepoFeatures)
Q_DECLARE_OPERATORS_FOR_FLAGS(Repo::RepoFlags)

#endif // REPO_H
