#include "interactable.h"

#include "reaction.h"

Interactable::Interactable(QObject *parent) :
    Node(parent)
{

}

void Interactable::updateReactionCount(quint8 reactions)
{
    if ( (reactions & Reaction::Confused) > (m_viewerReactions & Reaction::Confused) ) {
        setReactionConfusedCount(m_reactionConfusedCount + 1);
    } else if ( (reactions & Reaction::Confused) < (m_viewerReactions & Reaction::Confused) ) {
        setReactionConfusedCount(m_reactionConfusedCount - 1);
    }

    if ( (reactions & Reaction::Eyes) > (m_viewerReactions & Reaction::Eyes) ) {
        setReactionEyesCount(m_reactionEyesCount + 1);
    } else if ( (reactions & Reaction::Eyes) < (m_viewerReactions & Reaction::Eyes) ) {
        setReactionEyesCount(m_reactionEyesCount - 1);
    }

    if ( (reactions & Reaction::Heart) > (m_viewerReactions & Reaction::Heart) ) {
        setReactionHeartCount(m_reactionHeartCount + 1);
    } else if ( (reactions & Reaction::Heart) < (m_viewerReactions & Reaction::Heart) ) {
        setReactionHeartCount(m_reactionHeartCount - 1);
    }

    if ( (reactions & Reaction::Laugh) > (m_viewerReactions & Reaction::Laugh) ) {
        setReactionLaughCount(m_reactionLaughCount + 1);
    } else if ( (reactions & Reaction::Laugh) < (m_viewerReactions & Reaction::Laugh) ) {
        setReactionLaughCount(m_reactionLaughCount - 1);
    }

    if ( (reactions & Reaction::Hooray) > (m_viewerReactions & Reaction::Hooray) ) {
        setReactionHoorayCount(m_reactionHoorayCount + 1);
    } else if ( (reactions & Reaction::Hooray) < (m_viewerReactions & Reaction::Hooray) ) {
        setReactionHoorayCount(m_reactionHoorayCount - 1);
    }

    if ( (reactions & Reaction::Rocket) > (m_viewerReactions & Reaction::Rocket) ) {
        setReactionRocketCount(m_reactionRocketCount + 1);
    } else if ( (reactions & Reaction::Rocket) < (m_viewerReactions & Reaction::Rocket) ) {
        setReactionRocketCount(m_reactionRocketCount - 1);
    }

    if ( (reactions & Reaction::ThumbsDown) > (m_viewerReactions & Reaction::ThumbsDown) ) {
        setReactionThumbsDownCount(m_reactionThumbsDownCount + 1);
    } else if ( (reactions & Reaction::ThumbsDown) < (m_viewerReactions & Reaction::ThumbsDown) ) {
        setReactionThumbsDownCount(m_reactionThumbsDownCount - 1);
    }

    if ( (reactions & Reaction::ThumbsUp) > (m_viewerReactions & Reaction::ThumbsUp) ) {
        setReactionThumbsUpCount(m_reactionThumbsUpCount + 1);
    } else if ( (reactions & Reaction::ThumbsUp) < (m_viewerReactions & Reaction::ThumbsUp) ) {
        setReactionThumbsUpCount(m_reactionThumbsUpCount - 1);
    }
}

Owner *Interactable::author() const
{
    return m_author;
}

QString Interactable::body() const
{
    return m_body;
}

bool Interactable::edited() const
{
    return m_edited;
}

quint32 Interactable::reactionConfusedCount() const
{
    return m_reactionConfusedCount;
}

quint32 Interactable::reactionEyesCount() const
{
    return m_reactionEyesCount;
}

quint32 Interactable::reactionHeartCount() const
{
    return m_reactionHeartCount;
}

quint32 Interactable::reactionHoorayCount() const
{
    return m_reactionHoorayCount;
}

quint32 Interactable::reactionLaughCount() const
{
    return m_reactionLaughCount;
}

quint32 Interactable::reactionRocketCount() const
{
    return m_reactionRocketCount;
}

quint32 Interactable::reactionThumbsDownCount() const
{
    return m_reactionThumbsDownCount;
}

quint32 Interactable::reactionThumbsUpCount() const
{
    return m_reactionThumbsUpCount;
}

bool Interactable::viewerDidAuthor() const
{
    return m_viewerDidAuthor;
}

quint8 Interactable::viewerReactions() const
{
    return m_viewerReactions;
}

void Interactable::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Interactable::setBody(const QString &body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged(m_body);
}

void Interactable::setEdited(bool edited)
{
    if (m_edited == edited)
        return;

    m_edited = edited;
    emit editedChanged(m_edited);
}

void Interactable::setReactionConfusedCount(quint32 count)
{
    if (m_reactionConfusedCount == count)
        return;

    m_reactionConfusedCount = count;
    emit reactionConfusedCountChanged(m_reactionConfusedCount);
}

void Interactable::setReactionEyesCount(quint32 count)
{
    if (m_reactionEyesCount == count)
        return;

    m_reactionEyesCount = count;
    emit reactionEyesCountChanged(m_reactionEyesCount);
}

void Interactable::setReactionHeartCount(quint32 count)
{
    if (m_reactionHeartCount == count)
        return;

    m_reactionHeartCount = count;
    emit reactionHeartCountChanged(m_reactionHeartCount);
}

void Interactable::setReactionHoorayCount(quint32 count)
{
    if (m_reactionHoorayCount == count)
        return;

    m_reactionHoorayCount = count;
    emit reactionHoorayCountChanged(m_reactionHoorayCount);
}

void Interactable::setReactionLaughCount(quint32 count)
{
    if (m_reactionLaughCount == count)
        return;

    m_reactionLaughCount = count;
    emit reactionLaughCountChanged(m_reactionLaughCount);
}

void Interactable::setReactionRocketCount(quint32 count)
{
    if (m_reactionRocketCount == count)
        return;

    m_reactionRocketCount = count;
    emit reactionRocketCountChanged(m_reactionRocketCount);
}

void Interactable::setReactionThumbsDownCount(quint32 count)
{
    if (m_reactionThumbsDownCount == count)
        return;

    m_reactionThumbsDownCount = count;
    emit reactionThumbsDownCountChanged(m_reactionThumbsDownCount);
}

void Interactable::setReactionThumbsUpCount(quint32 count)
{
    if (m_reactionThumbsUpCount == count)
        return;

    m_reactionThumbsUpCount = count;
    emit reactionThumbsUpCountChanged(m_reactionThumbsUpCount);
}

void Interactable::setViewerDidAuthor(bool authored)
{
    if (m_viewerDidAuthor == authored)
        return;

    m_viewerDidAuthor = authored;
    emit viewerDidAuthorChanged(m_viewerDidAuthor);
}

void Interactable::setViewerReactions(quint8 reactions)
{
    if (m_viewerReactions == reactions)
        return;

    m_viewerReactions = reactions;
    emit viewerReactionsChanged(m_viewerReactions);
}
