#include "repo.h"

Repo::Repo(QObject *parent) :
    Node(parent)
{

}

QStringList Repo::branches() const
{
    return m_branches;
}

quint32 Repo::contributorCount() const
{
    return m_contributorCount;
}

QString Repo::defaultBranch() const
{
    return m_defaultBranch;
}

QString Repo::description() const
{
    return m_description;
}

quint32 Repo::discussionCount() const
{
    return m_discussionCount;
}

quint8 Repo::features() const
{
    return m_features;
}

quint32 Repo::forkCount() const
{
    return m_forkCount;
}

bool Repo::hasFundingLinks() const
{
    return m_hasFundingLinks;
}

QString Repo::homepageUrl() const
{
    return m_homepageUrl;
}

bool Repo::isArchived() const
{
    return m_isArchived;
}

bool Repo::isDisabled() const
{
    return m_isDisabled;
}

bool Repo::isEmpty() const
{
    return m_isEmpty;
}

bool Repo::isFork() const
{
    return m_isFork;
}

bool Repo::isInOrganization() const
{
    return m_isInOrganization;
}

bool Repo::isLocked() const
{
    return m_isLocked;
}

bool Repo::isMirror() const
{
    return m_isMirror;
}

bool Repo::isPrivate() const
{
    return m_isPrivate;
}

bool Repo::isTemplate() const
{
    return m_isTemplate;
}

quint32 Repo::issuesCount() const
{
    return m_issueCount;
}

License *Repo::license() const
{
    return m_license;
}

Owner *Repo::owner() const
{
    return m_owner;
}

quint32 Repo::projects() const
{
    return m_projects;
}

quint32 Repo::pullRequestsCount() const
{
    return m_pullRequestCount;
}

quint32 Repo::releaseCount() const
{
    return m_releaseCount;
}

quint32 Repo::stargazerCount() const
{
    return m_stargazerCount;
}

bool Repo::viewerCanSubscribe() const
{
    return m_viewerCanSubscribe;
}

bool Repo::viewerHasStarred() const
{
    return m_viewerHasStarred;
}

quint8 Repo::viewerPermission() const
{
    return m_viewerPermission;
}

quint8 Repo::viewerSubscription() const
{
    return m_viewerSubscription;
}

quint32 Repo::vulnerabilityAlertCount() const
{
    return m_vulnerabilityAlertCount;
}

quint32 Repo::watcherCount() const
{
    return m_watcherCount;
}

void Repo::setBranches(const QStringList &branches)
{
    if (m_branches == branches)
        return;

    m_branches = branches;
    emit branchesChanged(m_branches);
}

void Repo::setContributorCount(quint32 count)
{
    if (m_contributorCount == count)
        return;

    m_contributorCount = count;
    emit contributorCountChanged(m_contributorCount);
}

void Repo::setDefaultBranch(const QString &branch)
{
    if (m_defaultBranch == branch)
        return;

    m_defaultBranch = branch;
    emit defaultBranchChanged(m_defaultBranch);
}

void Repo::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
}

void Repo::setDiscussionCount(quint32 count)
{
    if (m_discussionCount == count)
        return;

    m_discussionCount = count;
    emit discussionCountChanged(m_discussionCount);
}

void Repo::setFeatures(quint8 features)
{
    if (m_features == features)
        return;

    m_features = features;
    emit featuresChanged(m_features);
}

void Repo::setForkCount(quint32 count)
{
    if (m_forkCount == count)
        return;

    m_forkCount = count;
    emit forkCountChanged(m_forkCount);
}

void Repo::setHasFundingLinks(bool hasFundingLinks)
{
    if (m_hasFundingLinks == hasFundingLinks)
        return;

    m_hasFundingLinks = hasFundingLinks;
    emit hasFundingLinksChanged(m_hasFundingLinks);
}

void Repo::setHomepageUrl(const QString &url)
{
    if (m_homepageUrl == url)
        return;

    m_homepageUrl = url;
    emit homepageUrlChanged(m_homepageUrl);
}

void Repo::setIsArchived(bool isArchived)
{
    if (m_isArchived == isArchived)
        return;

    m_isArchived = isArchived;
    emit isArchivedChanged(m_isArchived);
}

void Repo::setIsDisabled(bool isDisabled)
{
    if (m_isDisabled == isDisabled)
        return;

    m_isDisabled = isDisabled;
    emit isDisabledChanged(m_isDisabled);
}

void Repo::setIsEmpty(bool isEmpty)
{
    if (m_isEmpty == isEmpty)
        return;

    m_isEmpty = isEmpty;
    emit isEmptyChanged(m_isEmpty);
}

void Repo::setIsFork(bool isFork)
{
    if (m_isFork == isFork)
        return;

    m_isFork = isFork;
    emit isForkChanged(m_isFork);
}

void Repo::setIsInOrganization(bool isInOrganization)
{
    if (m_isInOrganization == isInOrganization)
        return;

    m_isInOrganization = isInOrganization;
    emit isInOrganizationChanged(m_isInOrganization);
}

void Repo::setIsLocked(bool isLocked)
{
    if (m_isLocked == isLocked)
        return;

    m_isLocked = isLocked;
    emit isLockedChanged(m_isLocked);
}

void Repo::setIsMirror(bool isMirror)
{
    if (m_isMirror == isMirror)
        return;

    m_isMirror = isMirror;
    emit isMirrorChanged(m_isMirror);
}

void Repo::setIsPrivate(bool isPrivate)
{
    if (m_isPrivate == isPrivate)
        return;

    m_isPrivate = isPrivate;
    emit isPrivateChanged(m_isPrivate);
}

void Repo::setIsTemplate(bool isTemplate)
{
    if (m_isTemplate == isTemplate)
        return;

    m_isTemplate = isTemplate;
    emit isTemplateChanged(m_isTemplate);
}

void Repo::setIssuesCount(quint32 count)
{
    if (m_issueCount == count)
        return;

    m_issueCount = count;
    emit issuesCountChanged(m_issueCount);
}

void Repo::setLicense(License *license)
{
    if (m_license == license)
        return;

    m_license = license;
    emit licenseChanged(m_license);
}

void Repo::setOwner(Owner *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged(m_owner);
}

void Repo::setProjects(quint32 projects)
{
    if (m_projects == projects)
        return;

    m_projects = projects;
    emit projectsChanged(m_projects);
}

void Repo::setPullRequestsCount(quint32 count)
{
    if (m_pullRequestCount == count)
        return;

    m_pullRequestCount = count;
    emit pullRequestsCountChanged(m_pullRequestCount);
}

void Repo::setReleaseCount(quint32 releases)
{
    if (m_releaseCount == releases)
        return;

    m_releaseCount = releases;
    emit releaseCountChanged(m_releaseCount);
}

void Repo::setStargazerCount(quint32 count)
{
    if (m_stargazerCount == count)
        return;

    m_stargazerCount = count;
    emit stargazerCountChanged(m_stargazerCount);
}

void Repo::setViewerCanSubscribe(bool subscribable)
{
    if (m_viewerCanSubscribe == subscribable)
        return;

    m_viewerCanSubscribe = subscribable;
    emit viewerCanSubscribeChanged(m_viewerCanSubscribe);
}

void Repo::setViewerHasStarred(bool starred)
{
    if (m_viewerHasStarred == starred)
        return;

    m_viewerHasStarred = starred;
    emit viewerHasStarredChanged(m_viewerHasStarred);
}

void Repo::setViewerPermission(quint8 permission)
{
    if (m_viewerPermission == permission)
        return;

    m_viewerPermission = permission;
    emit viewerPermissionChanged(m_viewerPermission);
}

void Repo::setViewerSubscription(quint8 viewerSubscription)
{
    if (m_viewerSubscription == viewerSubscription)
        return;

    m_viewerSubscription = viewerSubscription;
    emit viewerSubscriptionChanged(m_viewerSubscription);
}

void Repo::setVulnerabilityAlertCount(quint32 count)
{
    if (m_vulnerabilityAlertCount == count)
        return;

    m_vulnerabilityAlertCount = count;
    emit vulnerabilityAlertCountChanged(m_vulnerabilityAlertCount);
}

void Repo::setWatcherCount(quint32 count)
{
    if (m_watcherCount == count)
        return;

    m_watcherCount = count;
    emit watcherCountChanged(m_watcherCount);
}
