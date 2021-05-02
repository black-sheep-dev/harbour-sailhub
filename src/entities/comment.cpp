#include "comment.h"

Comment::Comment(QObject *parent) :
    Interactable(parent)
{

}

QString Comment::bodyExcerpt() const
{
    return m_bodyExcerpt;
}

void Comment::setBodyExcerpt(const QString &excerpt)
{
    if (m_bodyExcerpt == excerpt)
        return;

    m_bodyExcerpt = excerpt;
    emit bodyExcerptChanged(m_bodyExcerpt);
}


