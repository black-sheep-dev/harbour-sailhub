#include "comment.h"

Comment::Comment(QObject *parent) :
    Node(parent)
{

}

Owner *Comment::author() const
{
    return m_author;
}

QString Comment::body() const
{
    return m_body;
}

QDateTime Comment::createdAt() const
{
    return m_createdAt;
}

QString Comment::createdAtTimeSpan() const
{
    return m_createdAtTimeSpan;
}

bool Comment::edited() const
{
    return m_edited;
}

QDateTime Comment::lastEditAt() const
{
    return m_lastEditAt;
}

bool Comment::viewerCanDelete() const
{
    return m_viewerCanDelete;
}

bool Comment::viewerCanReact() const
{
    return m_viewerCanReact;
}

bool Comment::viewerCanUpdate() const
{
    return m_viewerCanUpdate;
}

bool Comment::viewerDidAuthor() const
{
    return m_viewerDidAuthor;
}

void Comment::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Comment::setBody(const QString &body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged(m_body);
}

void Comment::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged(m_createdAt);
}

void Comment::setCreatedAtTimeSpan(QString createdAtTimeSpan)
{
    if (m_createdAtTimeSpan == createdAtTimeSpan)
        return;

    m_createdAtTimeSpan = createdAtTimeSpan;
    emit createdAtTimeSpanChanged(m_createdAtTimeSpan);
}

void Comment::setEdited(bool edited)
{
    if (m_edited == edited)
        return;

    m_edited = edited;
    emit editedChanged(m_edited);
}

void Comment::setLastEditAt(const QDateTime &lastEditAt)
{
    if (m_lastEditAt == lastEditAt)
        return;

    m_lastEditAt = lastEditAt;
    emit lastEditAtChanged(m_lastEditAt);
}

void Comment::setViewerCanDelete(bool viewerCanDelete)
{
    if (m_viewerCanDelete == viewerCanDelete)
        return;

    m_viewerCanDelete = viewerCanDelete;
    emit viewerCanDeleteChanged(m_viewerCanDelete);
}

void Comment::setViewerCanReact(bool viewerCanReact)
{
    if (m_viewerCanReact == viewerCanReact)
        return;

    m_viewerCanReact = viewerCanReact;
    emit viewerCanReactChanged(m_viewerCanReact);
}

void Comment::setViewerCanUpdate(bool viewerCanUpdate)
{
    if (m_viewerCanUpdate == viewerCanUpdate)
        return;

    m_viewerCanUpdate = viewerCanUpdate;
    emit viewerCanUpdateChanged(m_viewerCanUpdate);
}

void Comment::setViewerDidAuthor(bool viewerDidAuthor)
{
    if (m_viewerDidAuthor == viewerDidAuthor)
        return;

    m_viewerDidAuthor = viewerDidAuthor;
    emit viewerDidAuthorChanged(m_viewerDidAuthor);
}
