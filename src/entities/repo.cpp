#include "repo.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/enums/repositorypermission.h"

// List Item
RepoListItem::RepoListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    description = DataUtils::removeEmojiTags(data.value(ApiKey::SHORT_DESCRIPTION_HTML).toString());
    flags = DataUtils::getRepoFlags(data);
    lockReason = RepositoryLockReason::fromString(data.value(ApiKey::LOCK_REASON).toString());
    ownerAvatar = data.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::AVATAR_URL).toString();

    ownerLogin = data.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::LOGIN).toString();


    pushedAt = QDateTime::fromString(data.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    stargazerCount = quint32(data.value(ApiKey::STARGAZER_COUNT).toInt());

    const QJsonObject lang = data.value(ApiKey::PRIMARY_LANGUAGE).toObject();
    language.name = lang.value(ApiKey::NAME).toString();
    language.color = lang.value(ApiKey::COLOR).toString();
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
}

// Object
Repo::Repo(QObject *parent) :
    Node(parent)
{

}

Repo::Repo(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Repo::setData(const QJsonObject &data)
{
    Node::setData(data);

    QStringList branches;

    const QJsonArray nodes = data.value(ApiKey::REFS).toObject().value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        branches.append(node.toObject().value(ApiKey::NAME).toString());
    }
    setBranches(branches);

    setContributorCount(DataUtils::getTotalCount(data.value(ApiKey::MENTIONABLE_USERS).toObject()));
    setDefaultBranch(data.value(ApiKey::DEFAULT_BRANCH_REF).toObject()
                           .value(ApiKey::NAME).toString());
    setDescription(data.value(ApiKey::DESCRIPTION).toString());
    setDiscussionCount(DataUtils::getTotalCount(data.value(ApiKey::DISCUSSIONS).toObject()));
    setFlags(DataUtils::getRepoFlags(data));
    setForkCount(data.value(ApiKey::FORK_COUNT).toInt());
    setHasFundingLinks(data.value(ApiKey::FUNDING_LINKS).toArray().count() > 0);
    setHomepageUrl(data.value(ApiKey::HOMEPAGE_URL).toString());
    setIssuesCount(DataUtils::getTotalCount(data.value(ApiKey::ISSUES).toObject()));
    setLabelCount(DataUtils::getTotalCount(data.value(ApiKey::LABELS).toObject()));
    setLockReason(RepositoryLockReason::fromString(data.value(ApiKey::LOCK_REASON).toString()));
    setProjects(DataUtils::getTotalCount(data.value(ApiKey::PROJECTS).toObject()));
    setReleaseCount(DataUtils::getTotalCount(data.value(ApiKey::RELEASES).toObject()));
    setPullRequestsCount(DataUtils::getTotalCount(data.value(ApiKey::PULL_REQUESTS).toObject()));
    setReleaseCount(DataUtils::getTotalCount(data.value(ApiKey::RELEASES).toObject()));
    setStargazerCount(data.value(ApiKey::STARGAZER_COUNT).toInt());
    setViewerHasStarred(data.value(ApiKey::VIEWER_HAS_STARRED).toBool());
    setViewerSubscription(data.value(ApiKey::VIEWER_SUBSCRIPTION).toInt());
    setVulnerabilityAlertCount(DataUtils::getTotalCount(data.value(ApiKey::VULNERABILITY_ALERTS).toObject()));
    setWatcherCount(DataUtils::getTotalCount(data.value(ApiKey::WATCHERS).toObject()));

    const QJsonObject lic = data.value(ApiKey::LICENSE_INFO).toObject();
    auto license = new License(this);
    license->setName(lic.value(ApiKey::SPDX_ID).toString());
    license->setUrl(lic.value(ApiKey::URL).toString());
    setLicense(license);


    Owner *owner = DataUtils::ownerFromJson(data.value(ApiKey::OWNER).toObject());
    if (owner != nullptr) {
        owner->setParent(this);
        setOwner(owner);
    }

    const QJsonObject parentRepo = data.value(ApiKey::PARENT).toObject();
    setParentId(parentRepo.value(ApiKey::ID).toString());
    setParentName(parentRepo.value(ApiKey::NAME_WITH_OWNER).toString());


    // features
    quint8 features{Repo::FeatureNone};

    if (data.value(ApiKey::HAS_ISSUES_ENABLED).toBool())
        features |= Repo::FeatureIssues;

    if (data.value(ApiKey::HAS_PROJECTS_ENABLED).toBool())
        features |= Repo::FeatureProjects;

    if (data.value(ApiKey::HAS_WIKI_ENABLED).toBool())
        features |= Repo::FeatureWiki;

    setFeatures(features);

    // permisson
    setViewerPermission(RepositoryPermission::fromString(data.value(ApiKey::VIEWER_PERMISSION).toString()));

    // subscription
    setViewerSubscription(SubscriptionState::fromString(data.value(ApiKey::VIEWER_SUBSCRIPTION).toString()));
}

const QStringList &Repo::branches() const
{
    return m_branches;
}

quint32 Repo::contributorCount() const
{
    return m_contributorCount;
}

const QString &Repo::defaultBranch() const
{
    return m_defaultBranch;
}

const QString &Repo::description() const
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

const QString &Repo::homepageUrl() const
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

const QString &Repo::parentId() const
{
    return m_parentId;
}

const QString &Repo::parentName() const
{
    return m_parentName;
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
    emit branchesChanged();
}

void Repo::setContributorCount(quint32 count)
{
    if (m_contributorCount == count)
        return;

    m_contributorCount = count;
    emit contributorCountChanged();
}

void Repo::setDefaultBranch(const QString &branch)
{
    if (m_defaultBranch == branch)
        return;

    m_defaultBranch = branch;
    emit defaultBranchChanged();
}

void Repo::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged();
}

void Repo::setDiscussionCount(quint32 count)
{
    if (m_discussionCount == count)
        return;

    m_discussionCount = count;
    emit discussionCountChanged();
}

void Repo::setFeatures(quint8 features)
{
    if (m_features == features)
        return;

    m_features = features;
    emit featuresChanged();
}

void Repo::setFlags(quint16 flags)
{
    if (m_flags == flags)
        return;

    m_flags = flags;
    emit flagsChanged();
}

void Repo::setForkCount(quint32 count)
{
    if (m_forkCount == count)
        return;

    m_forkCount = count;
    emit forkCountChanged();
}

void Repo::setHasFundingLinks(bool hasFundingLinks)
{
    if (m_hasFundingLinks == hasFundingLinks)
        return;

    m_hasFundingLinks = hasFundingLinks;
    emit hasFundingLinksChanged();
}

void Repo::setHomepageUrl(const QString &url)
{
    if (m_homepageUrl == url)
        return;

    m_homepageUrl = url;
    emit homepageUrlChanged();
}

void Repo::setIssuesCount(quint32 count)
{
    if (m_issueCount == count)
        return;

    m_issueCount = count;
    emit issuesCountChanged();
}

void Repo::setLabelCount(quint32 count)
{
    if (m_labelCount == count)
        return;

    m_labelCount = count;
    emit labelCountChanged();
}

void Repo::setLicense(License *license)
{
    if (m_license == license)
        return;

    m_license = license;
    emit licenseChanged();
}

void Repo::setLockReason(quint8 reason)
{
    if (m_lockReason == reason)
        return;

    m_lockReason = reason;
    emit lockReasonChanged();
}

void Repo::setOwner(Owner *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged();
}

void Repo::setParentId(const QString &id)
{
    if (m_parentId == id)
        return;

    m_parentId = id;
    emit parentIdChanged();
}

void Repo::setParentName(const QString &name)
{
    if (m_parentName == name)
        return;

    m_parentName = name;
    emit parentNameChanged();
}

void Repo::setProjects(quint32 projects)
{
    if (m_projects == projects)
        return;

    m_projects = projects;
    emit projectsChanged();
}

void Repo::setPullRequestsCount(quint32 count)
{
    if (m_pullRequestCount == count)
        return;

    m_pullRequestCount = count;
    emit pullRequestsCountChanged();
}

void Repo::setReleaseCount(quint32 releases)
{
    if (m_releaseCount == releases)
        return;

    m_releaseCount = releases;
    emit releaseCountChanged();
}

void Repo::setStargazerCount(quint32 count)
{
    if (m_stargazerCount == count)
        return;

    m_stargazerCount = count;
    emit stargazerCountChanged();
}

void Repo::setViewerHasStarred(bool starred)
{
    if (m_viewerHasStarred == starred)
        return;

    m_viewerHasStarred = starred;
    emit viewerHasStarredChanged();
}

void Repo::setViewerPermission(quint8 permission)
{
    if (m_viewerPermission == permission)
        return;

    m_viewerPermission = permission;
    emit viewerPermissionChanged();
}

void Repo::setViewerSubscription(quint8 viewerSubscription)
{
    if (m_viewerSubscription == viewerSubscription)
        return;

    m_viewerSubscription = viewerSubscription;
    emit viewerSubscriptionChanged();
}

void Repo::setVulnerabilityAlertCount(quint32 count)
{
    if (m_vulnerabilityAlertCount == count)
        return;

    m_vulnerabilityAlertCount = count;
    emit vulnerabilityAlertCountChanged();
}

void Repo::setWatcherCount(quint32 count)
{
    if (m_watcherCount == count)
        return;

    m_watcherCount = count;
    emit watcherCountChanged();
}
