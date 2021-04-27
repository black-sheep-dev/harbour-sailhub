#include "discussioncomment.h"

DiscussionComment::DiscussionComment(QObject *parent) :
    Interactable(parent)
{

}

bool DiscussionComment::createdViaEmail() const
{
    return m_createdViaEmail;
}

QDateTime DiscussionComment::deletedAt() const
{
    return m_deletedAt;
}

Owner *DiscussionComment::editor() const
{
    return m_editor;
}

bool DiscussionComment::includesCreatedEdit() const
{
    return m_includesCreatedEdit;
}

bool DiscussionComment::isAnswer() const
{
    return m_isAnswer;
}

bool DiscussionComment::isMinimized() const
{
    return m_isMinimized;
}

QString DiscussionComment::minimizedReason() const
{
    return m_minimizedReason;
}

quint32 DiscussionComment::replyCount() const
{
    return m_replyCount;
}

QString DiscussionComment::replyToId() const
{
    return m_replyToId;
}

void DiscussionComment::setCreatedViaEmail(bool createdViaEmail)
{
    if (m_createdViaEmail == createdViaEmail)
        return;

    m_createdViaEmail = createdViaEmail;
    emit createdViaEmailChanged(m_createdViaEmail);
}

void DiscussionComment::setDeletedAt(const QDateTime &deletedAt)
{
    if (m_deletedAt == deletedAt)
        return;

    m_deletedAt = deletedAt;
    emit deletedAtChanged(m_deletedAt);
}

void DiscussionComment::setEditor(Owner *editor)
{
    if (m_editor == editor)
        return;

    m_editor = editor;
    emit editorChanged(m_editor);
}

void DiscussionComment::setIncludesCreatedEdit(bool includesCreatedEdit)
{
    if (m_includesCreatedEdit == includesCreatedEdit)
        return;

    m_includesCreatedEdit = includesCreatedEdit;
    emit includesCreatedEditChanged(m_includesCreatedEdit);
}

void DiscussionComment::setIsAnswer(bool isAnswer)
{
    if (m_isAnswer == isAnswer)
        return;

    m_isAnswer = isAnswer;
    emit isAnswerChanged(m_isAnswer);
}

void DiscussionComment::setIsMinimized(bool isMinimized)
{
    if (m_isMinimized == isMinimized)
        return;

    m_isMinimized = isMinimized;
    emit isMinimizedChanged(m_isMinimized);
}

void DiscussionComment::setMinimizedReason(const QString &minimizedReason)
{
    if (m_minimizedReason == minimizedReason)
        return;

    m_minimizedReason = minimizedReason;
    emit minimizedReasonChanged(m_minimizedReason);
}

void DiscussionComment::setReplyCount(quint32 replyCount)
{
    if (m_replyCount == replyCount)
        return;

    m_replyCount = replyCount;
    emit replyCountChanged(m_replyCount);
}

void DiscussionComment::setReplyToId(const QString &replyToId)
{
    if (m_replyToId == replyToId)
        return;

    m_replyToId = replyToId;
    emit replyToIdChanged(m_replyToId);
}
