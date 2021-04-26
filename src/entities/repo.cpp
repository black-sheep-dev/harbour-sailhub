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

quint32 Repo::forkCount() const
{
    return m_forkCount;
}

QString Repo::homepageUrl() const
{
    return m_homepageUrl;
}

bool Repo::isPrivate() const
{
    return m_isPrivate;
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

QString Repo::readme() const
{
    return m_readme;
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

void Repo::setForkCount(quint32 count)
{
    if (m_forkCount == count)
        return;

    m_forkCount = count;
    emit forkCountChanged(m_forkCount);
}

void Repo::setHomepageUrl(const QString &url)
{
    if (m_homepageUrl == url)
        return;

    m_homepageUrl = url;
    emit homepageUrlChanged(m_homepageUrl);
}

void Repo::setIsPrivate(bool isPrivate)
{
    if (m_isPrivate == isPrivate)
        return;

    m_isPrivate = isPrivate;
    emit isPrivateChanged(m_isPrivate);
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

void Repo::setReadme(const QString &readme)
{
    if (m_readme == readme)
        return;

    m_readme = readme;
    emit readmeChanged(m_readme);
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

void Repo::setWatcherCount(quint32 count)
{
    if (m_watcherCount == count)
        return;

    m_watcherCount = count;
    emit watcherCountChanged(m_watcherCount);
}
