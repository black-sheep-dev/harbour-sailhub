#include "repo.h"

Repo::Repo(QObject *parent) :
    Node(parent)
{

}

bool Repo::archived() const
{
    return m_archived;
}

QString Repo::defaultBranch() const
{
    return m_defaultBranch;
}

QString Repo::description() const
{
    return m_description;
}

bool Repo::disabled() const
{
    return m_disabled;
}

bool Repo::fork() const
{
    return m_fork;
}

quint32 Repo::forks() const
{
    return m_forks;
}

QString Repo::fullName() const
{
    return m_fullName;
}

bool Repo::hasDownloads() const
{
    return m_hasDownloads;
}

bool Repo::hasIssues() const
{
    return m_hasIssues;
}

bool Repo::hasPages() const
{
    return m_hasPages;
}

bool Repo::hasProjects() const
{
    return m_hasProjects;
}

bool Repo::hasWiki() const
{
    return m_hasWiki;
}

QString Repo::homepage() const
{
    return m_homepage;
}

QString Repo::language() const
{
    return m_language;
}

QString Repo::licenseKey() const
{
    return m_licenseKey;
}

QString Repo::licenseName() const
{
    return m_licenseName;
}

QString Repo::licenseUrl() const
{
    return m_licenseUrl;
}

QString Repo::mirrorUrl() const
{
    return m_mirrorUrl;
}

quint32 Repo::openIssues() const
{
    return m_openIssues;
}

User *Repo::owner() const
{
    return m_owner;
}

bool Repo::privateRepo() const
{
    return m_privateRepo;
}

QDateTime Repo::pushedAt() const
{
    return m_pushedAt;
}

qreal Repo::score() const
{
    return m_score;
}

quint64 Repo::size() const
{
    return m_size;
}

quint32 Repo::stargazers() const
{
    return m_stargazers;
}

quint32 Repo::subscribers() const
{
    return m_subscribers;
}

quint32 Repo::watchers() const
{
    return m_watchers;
}

void Repo::setArchived(bool archived)
{
    if (m_archived == archived)
        return;

    m_archived = archived;
    emit archivedChanged(m_archived);
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

void Repo::setDisabled(bool disabled)
{
    if (m_disabled == disabled)
        return;

    m_disabled = disabled;
    emit disabledChanged(m_disabled);
}

void Repo::setFork(bool fork)
{
    if (m_fork == fork)
        return;

    m_fork = fork;
    emit forkChanged(m_fork);
}

void Repo::setForks(quint32 forks)
{
    if (m_forks == forks)
        return;

    m_forks = forks;
    emit forksChanged(m_forks);
}

void Repo::setFullName(const QString &name)
{
    if (m_fullName == name)
        return;

    m_fullName = name;
    emit fullNameChanged(m_fullName);
}

void Repo::setHasDownloads(bool hasDownloads)
{
    if (m_hasDownloads == hasDownloads)
        return;

    m_hasDownloads = hasDownloads;
    emit hasDownloadsChanged(m_hasDownloads);
}

void Repo::setHasIssues(bool hasIssues)
{
    if (m_hasIssues == hasIssues)
        return;

    m_hasIssues = hasIssues;
    emit hasIssuesChanged(m_hasIssues);
}

void Repo::setHasPages(bool hasPages)
{
    if (m_hasPages == hasPages)
        return;

    m_hasPages = hasPages;
    emit hasPagesChanged(m_hasPages);
}

void Repo::setHasProjects(bool hasProjects)
{
    if (m_hasProjects == hasProjects)
        return;

    m_hasProjects = hasProjects;
    emit hasProjectsChanged(m_hasProjects);
}

void Repo::setHasWiki(bool hasWiki)
{
    if (m_hasWiki == hasWiki)
        return;

    m_hasWiki = hasWiki;
    emit hasWikiChanged(m_hasWiki);
}

void Repo::setHomepage(const QString &homepage)
{
    if (m_homepage == homepage)
        return;

    m_homepage = homepage;
    emit homepageChanged(m_homepage);
}

void Repo::setLanguage(const QString &language)
{
    if (m_language == language)
        return;

    m_language = language;
    emit languageChanged(m_language);
}

void Repo::setLicenseKey(const QString &key)
{
    if (m_licenseKey == key)
        return;

    m_licenseKey = key;
    emit licenseKeyChanged(m_licenseKey);
}

void Repo::setLicenseName(const QString &name)
{
    if (m_licenseName == name)
        return;

    m_licenseName = name;
    emit licenseNameChanged(m_licenseName);
}

void Repo::setLicenseUrl(const QString &url)
{
    if (m_licenseUrl == url)
        return;

    m_licenseUrl = url;
    emit licenseUrlChanged(m_licenseUrl);
}

void Repo::setMirrorUrl(const QString &url)
{
    if (m_mirrorUrl == url)
        return;

    m_mirrorUrl = url;
    emit mirrorUrlChanged(m_mirrorUrl);
}

void Repo::setOpenIssues(quint32 issues)
{
    if (m_openIssues == issues)
        return;

    m_openIssues = issues;
    emit openIssuesChanged(m_openIssues);
}

void Repo::setOwner(User *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged(m_owner);
}

void Repo::setPrivateRepo(bool privateRepo)
{
    if (m_privateRepo == privateRepo)
        return;

    m_privateRepo = privateRepo;
    emit privateRepoChanged(m_privateRepo);
}

void Repo::setPushedAt(const QDateTime &timestamp)
{
    if (m_pushedAt == timestamp)
        return;

    m_pushedAt = timestamp;
    emit pushedAtChanged(m_pushedAt);
}

void Repo::setScore(qreal score)
{
    if (qFuzzyCompare(m_score, score))
        return;

    m_score = score;
    emit scoreChanged(m_score);
}

void Repo::setSize(quint64 size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
}

void Repo::setStargazers(quint32 stargazers)
{
    if (m_stargazers == stargazers)
        return;

    m_stargazers = stargazers;
    emit stargazersChanged(m_stargazers);
}

void Repo::setSubscribers(quint32 subscribers)
{
    if (m_subscribers == subscribers)
        return;

    m_subscribers = subscribers;
    emit subscribersChanged(m_subscribers);
}

void Repo::setWatchers(quint32 watchers)
{
    if (m_watchers == watchers)
        return;

    m_watchers = watchers;
    emit watchersChanged(m_watchers);
}
