#include "release.h"

Release::Release(QObject *parent) :
    Node(parent)
{

}

Owner *Release::author() const
{
    return m_author;
}

QDateTime Release::createdAt() const
{
    return m_createdAt;
}

QString Release::description() const
{
    return m_description;
}

bool Release::isDraft() const
{
    return m_isDraft;
}

bool Release::isLatest() const
{
    return m_isLatest;
}

bool Release::isPrerelease() const
{
    return m_isPrerelease;
}

QDateTime Release::publishedAt() const
{
    return m_publishedAt;
}

QString Release::repository() const
{
    return m_repository;
}

QString Release::tagCommit() const
{
    return m_tagCommit;
}

QString Release::tagName() const
{
    return m_tagName;
}

void Release::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Release::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged(m_createdAt);
}

void Release::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
}

void Release::setIsDraft(bool isDraft)
{
    if (m_isDraft == isDraft)
        return;

    m_isDraft = isDraft;
    emit isDraftChanged(m_isDraft);
}

void Release::setIsLatest(bool isLatest)
{
    if (m_isLatest == isLatest)
        return;

    m_isLatest = isLatest;
    emit isLatestChanged(m_isLatest);
}

void Release::setIsPrerelease(bool isPrerelease)
{
    if (m_isPrerelease == isPrerelease)
        return;

    m_isPrerelease = isPrerelease;
    emit isPrereleaseChanged(m_isPrerelease);
}

void Release::setPublishedAt(const QDateTime &publishedAt)
{
    if (m_publishedAt == publishedAt)
        return;

    m_publishedAt = publishedAt;
    emit publishedAtChanged(m_publishedAt);
}

void Release::setRepository(const QString &repository)
{
    if (m_repository == repository)
        return;

    m_repository = repository;
    emit repositoryChanged(m_repository);
}

void Release::setTagCommit(const QString &tagCommit)
{
    if (m_tagCommit == tagCommit)
        return;

    m_tagCommit = tagCommit;
    emit tagCommitChanged(m_tagCommit);
}

void Release::setTagName(const QString &tagName)
{
    if (m_tagName == tagName)
        return;

    m_tagName = tagName;
    emit tagNameChanged(m_tagName);
}
