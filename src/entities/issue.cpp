#include "issue.h"

#include "QJsonObject"

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/enums/repositorypermission.h"

// List Item
IssueListItem::IssueListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    closed = data.value(ApiKey::CLOSED).toBool();
    commentCount = DataUtils::DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject());
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    createdAtTimeSpan = DataUtils::timeSpanText(createdAt, true);
    number = data.value(ApiKey::NUMBER).toInt();
    repository = data.value(ApiKey::REPOSITORY).toObject()
                         .value(ApiKey::NAME_WITH_OWNER).toString();
    state = IssueState::fromString(data.value(ApiKey::STATE).toString());
    title = data.value(ApiKey::TITLE).toString();
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    updatedAtTimeSpan = DataUtils::timeSpanText(updatedAt, true);
}

// Object
Issue::Issue(QObject *parent) :
    Interactable(parent)
{

}

Issue::Issue(const QJsonObject &data, QObject *parent) :
    Interactable(parent)
{
    setData(data);
}

void Issue::setData(const QJsonObject &data)
{
    Interactable::setData(data);

    setAssigneeCount(DataUtils::DataUtils::getTotalCount(data.value(ApiKey::ASSIGNEES).toObject()));
    setTitle(data.value(ApiKey::TITLE).toString());
    setNumber(data.value(ApiKey::NUMBER).toInt());

    const QJsonObject repo = data.value(ApiKey::REPOSITORY).toObject();
    setRepository(repo.value(ApiKey::NAME_WITH_OWNER).toString());
    setRepositoryId(repo.value(ApiKey::ID).toString());
    setRepositoryPermission(RepositoryPermission::fromString(repo.value(ApiKey::VIEWER_PERMISSION).toString()));
    setState(IssueState::fromString(data.value(ApiKey::STATE).toString()));
    setCommentCount(DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject()));
    setEdited(updatedAt() > createdAt());
    setLabelCount(DataUtils::getTotalCount(data.value(ApiKey::LABELS).toObject()));
    setLocked(data.value(ApiKey::LOCKED).toBool());
    setParticipantCount(DataUtils::getTotalCount(data.value(ApiKey::PARTICIPANTS).toObject()));

    // subscription
    setViewerSubscription(SubscriptionState::fromString(data.value(ApiKey::VIEWER_SUBSCRIPTION).toString()));
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

quint8 Issue::state() const
{
    return m_state;
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

void Issue::setState(quint8 states)
{
    if (m_state == states)
        return;

    m_state = states;
    emit stateChanged(m_state);
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
