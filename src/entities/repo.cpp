#include "repo.h"

Repo::Repo(QObject *parent) :
    Node(parent)
{

}

quint32 Repo::contributorCount() const
{
    return m_contributorCount;
}

QString Repo::description() const
{
    return m_description;
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

QString Repo::name() const
{
    return m_name;
}

Owner *Repo::owner() const
{
    return m_owner;
}

quint32 Repo::pullRequestsCount() const
{
    return m_pullRequestCount;
}

QString Repo::readme() const
{
    return m_readme;
}

quint32 Repo::stargazerCount() const
{
    return m_stargazerCount;
}

quint32 Repo::watcherCount() const
{
    return m_watcherCount;
}

void Repo::setContributorCount(quint32 count)
{
    if (m_contributorCount == count)
        return;

    m_contributorCount = count;
    emit contributorCountChanged(m_contributorCount);
}

void Repo::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
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

void Repo::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Repo::setOwner(Owner *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged(m_owner);
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

void Repo::setStargazerCount(quint32 count)
{
    if (m_stargazerCount == count)
        return;

    m_stargazerCount = count;
    emit stargazerCountChanged(m_stargazerCount);
}

void Repo::setWatcherCount(quint32 count)
{
    if (m_watcherCount == count)
        return;

    m_watcherCount = count;
    emit watcherCountChanged(m_watcherCount);
}
