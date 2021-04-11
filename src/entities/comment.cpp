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

QString Comment::bodyExcerpt() const
{
    return m_bodyExcerpt;
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

void Comment::setBodyExcerpt(const QString &excerpt)
{
    if (m_bodyExcerpt == excerpt)
        return;

    m_bodyExcerpt = excerpt;
    emit bodyExcerptChanged(m_bodyExcerpt);
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

void Comment::setViewerDidAuthor(bool viewerDidAuthor)
{
    if (m_viewerDidAuthor == viewerDidAuthor)
        return;

    m_viewerDidAuthor = viewerDidAuthor;
    emit viewerDidAuthorChanged(m_viewerDidAuthor);
}
