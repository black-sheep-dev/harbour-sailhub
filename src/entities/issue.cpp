#include "issue.h"

Issue::Issue(QObject *parent) :
    Node(parent)
{

}

quint32 Issue::assigneeCount() const
{
    return m_assigneeCount;
}

Owner *Issue::author() const
{
    return m_author;
}

QString Issue::body() const
{
    return m_body;
}

quint32 Issue::commentCount() const
{
    return m_commentCount;
}

QDateTime Issue::createdAt() const
{
    return m_createdAt;
}

QString Issue::createdAtTimeSpan() const
{
    return m_createdAtTimeSpan;
}

bool Issue::edited() const
{
    return m_edited;
}

quint32 Issue::labelCount() const
{
    return m_labelCount;
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

quint8 Issue::states() const
{
    return m_states;
}

QString Issue::title() const
{
    return m_title;
}

QDateTime Issue::updatedAt() const
{
    return m_updatedAt;
}

void Issue::setAssigneeCount(quint32 count)
{
    if (m_assigneeCount == count)
        return;

    m_assigneeCount = count;
    emit assigneeCountChanged(m_assigneeCount);
}

void Issue::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Issue::setBody(const QString &body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged(m_body);
}

void Issue::setCommentCount(quint32 count)
{
    if (m_commentCount == count)
        return;

    m_commentCount = count;
    emit commentCountChanged(m_commentCount);
}

void Issue::setCreatedAt(const QDateTime &timestamp)
{
    if (m_createdAt == timestamp)
        return;

    m_createdAt = timestamp;
    emit createdAtChanged(m_createdAt);
}

void Issue::setCreatedAtTimeSpan(const QString &timeSpan)
{
    if (m_createdAtTimeSpan == timeSpan)
        return;

    m_createdAtTimeSpan = timeSpan;
    emit createdAtTimeSpanChanged(m_createdAtTimeSpan);
}

void Issue::setEdited(bool edited)
{
    if (m_edited == edited)
        return;

    m_edited = edited;
    emit editedChanged(m_edited);
}

void Issue::setLabelCount(quint32 count)
{
    if (m_labelCount == count)
        return;

    m_labelCount = count;
    emit labelCountChanged(m_labelCount);
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

void Issue::setUpdatedAt(const QDateTime &timestamp)
{
    if (m_updatedAt == timestamp)
        return;

    m_updatedAt = timestamp;
    emit updatedAtChanged(m_updatedAt);
}
