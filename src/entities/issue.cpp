#include "issue.h"

Issue::Issue(QObject *parent) :
    Node(parent)
{

}

Owner *Issue::author() const
{
    return m_author;
}

quint32 Issue::commentCount() const
{
    return m_commentCount;
}

quint8 Issue::states() const
{
    return m_states;
}

QString Issue::title() const
{
    return m_title;
}

void Issue::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Issue::setCommentCount(quint32 count)
{
    if (m_commentCount == count)
        return;

    m_commentCount = count;
    emit commentCountChanged(m_commentCount);
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
