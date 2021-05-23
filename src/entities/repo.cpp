#include "repo.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
RepoListItem::RepoListItem(const QJsonObject &obj) :
    NodeListItem(obj)
{
    createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    description = DataUtils::removeEmojiTags(obj.value(ApiKey::SHORT_DESCRIPTION_HTML).toString());
    flags = DataUtils::getRepoFlags(obj);
    lockReason = RepositoryLockReason::fromString(obj.value(ApiKey::LOCK_REASON).toString());
    ownerAvatar = obj.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::AVATAR_URL).toString();
    ownerLogin = obj.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::LOGIN).toString();
    pushedAt = QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    stargazerCount = quint32(obj.value(ApiKey::STARGAZER_COUNT).toInt());

    const QJsonObject lang = obj.value(ApiKey::PRIMARY_LANGUAGE).toObject();
    language.name = lang.value(ApiKey::NAME).toString();
    language.color = lang.value(ApiKey::COLOR).toString();
    updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
}

// Object
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

quint16 Repo::flags() const
{
    return m_flags;
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

quint32 Repo::issuesCount() const
{
    return m_issueCount;
}

quint32 Repo::labelCount() const
{
    return m_labelCount;
}

License *Repo::license() const
{
    return m_license;
}

quint8 Repo::lockReason() const
{
    return m_lockReason;
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

void Repo::setFlags(quint16 flags)
{
    if (m_flags == flags)
        return;

    m_flags = flags;
    emit flagsChanged(m_flags);
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

void Repo::setIssuesCount(quint32 count)
{
    if (m_issueCount == count)
        return;

    m_issueCount = count;
    emit issuesCountChanged(m_issueCount);
}

void Repo::setLabelCount(quint32 count)
{
    if (m_labelCount == count)
        return;

    m_labelCount = count;
    emit labelCountChanged(m_labelCount);
}

void Repo::setLicense(License *license)
{
    if (m_license == license)
        return;

    m_license = license;
    emit licenseChanged(m_license);
}

void Repo::setLockReason(quint8 reason)
{
    if (m_lockReason == reason)
        return;

    m_lockReason = reason;
    emit lockReasonChanged(m_lockReason);
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
