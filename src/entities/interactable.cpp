#include "interactable.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"

#include "reaction.h"

Interactable::Interactable(QObject *parent) :
    Node(parent)
{

}

Interactable::Interactable(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Interactable::setData(const QJsonObject &data)
{
    Node::setData(data);

    // author
    auto author = DataUtils::ownerFromJson(data.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(this);
        setAuthor(author);
    }

    setViewerDidAuthor(data.value(ApiKey::VIEWER_DID_AUTHOR).toBool());

    // body
    //setBody(data.value(ApiKey::BODY_HTML).toString());
    setBody(data.value(ApiKey::BODY).toString());
    //qDebug() << "BODY: " << body();

    // reactions
    const QJsonArray reactionGroups = data.value(ApiKey::REACTION_GROUPS).toArray();

    if (reactionGroups.isEmpty())
        return;

    quint8 viewerReactions{Reaction::None};

    for (const auto &item : reactionGroups) {
        const QJsonObject group = item.toObject();
        const QString content = group.value(ApiKey::CONTENT).toString();
        const bool viewerReacted = group.value(ApiKey::VIEWER_HAS_REACTED).toBool();
        const quint32 count = DataUtils::getTotalCount(group.value(ApiKey::USERS).toObject());

        if (content == QLatin1String("CONFUSED")) {
            setReactionConfusedCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Confused;

        } else if (content == QLatin1String("EYES")) {
            setReactionEyesCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Eyes;

        } else if (content == QLatin1String("HEART")) {
            setReactionHeartCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Heart;

        } else if (content == QLatin1String("HOORAY")) {
            setReactionHoorayCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Hooray;

        } else if (content == QLatin1String("LAUGH")) {
            setReactionLaughCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Laugh;

        } else if (content == QLatin1String("ROCKET")) {
            setReactionRocketCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Rocket;

        } else if (content == QLatin1String("THUMBS_DOWN")) {
            setReactionThumbsDownCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::ThumbsDown;

        } else if (content == QLatin1String("THUMBS_UP")) {
            setReactionThumbsUpCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::ThumbsUp;

        }
    }

    setViewerReactions(viewerReactions);

    // timespamps
    setCreatedAt(QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    setCreatedAtTimeSpan(DataUtils::timeSpanText(createdAt(), true));
    setLastEditedAt(QDateTime::fromString(data.value(ApiKey::LAST_EDITED_AT).toString(), Qt::ISODate));
    setUpdatedAt(QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate));
    setUpdatedAtTimeSpan(DataUtils::timeSpanText(updatedAt()));
    setEdited(createdAt() < lastEditedAt());
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

const QString &Interactable::body() const
{
    return m_body;
}

const QDateTime &Interactable::createdAt() const
{
    return m_createdAt;
}

const QString &Interactable::createdAtTimeSpan() const
{
    return m_createdAtTimeSpan;
}

bool Interactable::edited() const
{
    return m_edited;
}

const QDateTime &Interactable::lastEditedAt() const
{
    return m_lastEditedAt;
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

const QDateTime &Interactable::updatedAt() const
{
    return m_updatedAt;
}

const QString &Interactable::updatedAtTimeSpan() const
{
    return m_updatedAtTimeSpan;
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
    emit authorChanged();
}

void Interactable::setBody(const QString &body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged();
}

void Interactable::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged();
}

void Interactable::setCreatedAtTimeSpan(const QString &createdAtTimeSpan)
{
    if (m_createdAtTimeSpan == createdAtTimeSpan)
        return;

    m_createdAtTimeSpan = createdAtTimeSpan;
    emit createdAtTimeSpanChanged();
}

void Interactable::setEdited(bool edited)
{
    if (m_edited == edited)
        return;

    m_edited = edited;
    emit editedChanged();
}

void Interactable::setLastEditedAt(const QDateTime &lastEditAt)
{
    if (m_lastEditedAt == lastEditAt)
        return;

    m_lastEditedAt = lastEditAt;
    emit lastEditedAtChanged();
}

void Interactable::setReactionConfusedCount(quint32 count)
{
    if (m_reactionConfusedCount == count)
        return;

    m_reactionConfusedCount = count;
    emit reactionConfusedCountChanged();
}

void Interactable::setReactionEyesCount(quint32 count)
{
    if (m_reactionEyesCount == count)
        return;

    m_reactionEyesCount = count;
    emit reactionEyesCountChanged();
}

void Interactable::setReactionHeartCount(quint32 count)
{
    if (m_reactionHeartCount == count)
        return;

    m_reactionHeartCount = count;
    emit reactionHeartCountChanged();
}

void Interactable::setReactionHoorayCount(quint32 count)
{
    if (m_reactionHoorayCount == count)
        return;

    m_reactionHoorayCount = count;
    emit reactionHoorayCountChanged();
}

void Interactable::setReactionLaughCount(quint32 count)
{
    if (m_reactionLaughCount == count)
        return;

    m_reactionLaughCount = count;
    emit reactionLaughCountChanged();
}

void Interactable::setReactionRocketCount(quint32 count)
{
    if (m_reactionRocketCount == count)
        return;

    m_reactionRocketCount = count;
    emit reactionRocketCountChanged();
}

void Interactable::setReactionThumbsDownCount(quint32 count)
{
    if (m_reactionThumbsDownCount == count)
        return;

    m_reactionThumbsDownCount = count;
    emit reactionThumbsDownCountChanged();
}

void Interactable::setReactionThumbsUpCount(quint32 count)
{
    if (m_reactionThumbsUpCount == count)
        return;

    m_reactionThumbsUpCount = count;
    emit reactionThumbsUpCountChanged();
}

void Interactable::setUpdatedAt(const QDateTime &updatedAt)
{
    if (m_updatedAt == updatedAt)
        return;

    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

void Interactable::setUpdatedAtTimeSpan(const QString &updatedAtTimeSpan)
{
    if (m_updatedAtTimeSpan == updatedAtTimeSpan)
        return;

    m_updatedAtTimeSpan = updatedAtTimeSpan;
    emit updatedAtTimeSpanChanged();
}

void Interactable::setViewerDidAuthor(bool authored)
{
    if (m_viewerDidAuthor == authored)
        return;

    m_viewerDidAuthor = authored;
    emit viewerDidAuthorChanged();
}

void Interactable::setViewerReactions(quint8 reactions)
{
    if (m_viewerReactions == reactions)
        return;

    m_viewerReactions = reactions;
    emit viewerReactionsChanged();
}
