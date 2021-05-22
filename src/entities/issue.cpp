#include "issue.h"

Issue::Issue(QObject *parent) :
    Interactable(parent)
{

}

quint32 Issue::assigneeCount() const
{
    return m_assigneeCount;
}

quint32 Issue::commentCount() const
{
    return m_commentCount;
}

quint32 Issue::labelCount() const
{
    return m_labelCount;
}

bool Issue::locked() const
{
    return m_locked;
}

quint32 Issue::number() const
{
    return m_number;
}

quint32 Issue::participantCount() const
{
    return m_participantCount;
}

QString Issue::repository() const
{
    return m_repository;
}

quint8 Issue::repositoryPermission() const
{
    return m_repositoryPermission;
}

QString Issue::repositoryId() const
{
    return m_repositoryId;
}

quint8 Issue::states() const
{
    return m_states;
}

QString Issue::title() const
{
    return m_title;
}

quint8 Issue::viewerSubscription() const
{
    return m_viewerSubscription;
}

void Issue::setAssigneeCount(quint32 count)
{
    if (m_assigneeCount == count)
        return;

    m_assigneeCount = count;
    emit assigneeCountChanged(m_assigneeCount);
}

void Issue::setCommentCount(quint32 count)
{
    if (m_commentCount == count)
        return;

    m_commentCount = count;
    emit commentCountChanged(m_commentCount);
}

void Issue::setLabelCount(quint32 count)
{
    if (m_labelCount == count)
        return;

    m_labelCount = count;
    emit labelCountChanged(m_labelCount);
}

void Issue::setLocked(bool locked)
{
    if (m_locked == locked)
        return;

    m_locked = locked;
    emit lockedChanged(m_locked);
}

void Issue::setNumber(quint32 number)
{
    if (m_number == number)
        return;

    m_number = number;
    emit numberChanged(m_number);
}

void Issue::setParticipantCount(quint32 count)
{
    if (m_participantCount == count)
        return;

    m_participantCount = count;
    emit participantCountChanged(m_participantCount);
}

void Issue::setRepository(const QString &repository)
{
    if (m_repository == repository)
        return;

    m_repository = repository;
    emit repositoryChanged(m_repository);
}

void Issue::setRepositoryId(const QString &id)
{
    if (m_repositoryId == id)
        return;

    m_repositoryId = id;
    emit repositoryIdChanged(m_repositoryId);
}

void Issue::setRepositoryPermission(quint8 permission)
{
    if (m_repositoryPermission == permission)
        return;

    m_repositoryPermission = permission;
    emit repositoryPermissionChanged(m_repositoryPermission);
}

void Issue::setStates(quint8 states)
{
    if (m_states == states)
        return;

    m_states = states;
    emit statesChanged(m_states);
}

void Issue::setTitle(const QString &title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void Issue::setViewerSubscription(quint8 subscription)
{
    if (m_viewerSubscription == subscription)
        return;

    m_viewerSubscription = subscription;
    emit viewerSubscriptionChanged(m_viewerSubscription);
}
