#include "discussion.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/enums/lockreason.h"

// List Item
DiscussionListItem::DiscussionListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    const QJsonObject cat = data.value(ApiKey::CATEGORY).toObject();
    category = cat.value(ApiKey::NAME).toString();
    emoji = DataUtils::getEmojiLinkFromString(cat.value(ApiKey::EMOJI_HTML).toString());

    commentCount = DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject());
    locked = data.value(ApiKey::LOCKED).toBool();
    lockReason = LockReason::fromString(data.value(ApiKey::ACTIVE_LOCK_REASON).toString());
    title = data.value(ApiKey::TITLE).toString();

    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    createdAtTimeSpan = DataUtils::timeSpanText(createdAt, true);
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    updatedAtTimeSpan = DataUtils::timeSpanText(updatedAt, true);

    const QJsonObject author = data.value(ApiKey::AUTHOR).toObject();
    authorLogin = author.value(ApiKey::LOGIN).toString();
    authorAvatar = author.value(ApiKey::AVATAR_URL).toString();
}

// Object
Discussion::Discussion(QObject *parent) :
    Interactable(parent)
{

}

Discussion::Discussion(const QJsonObject &data, QObject *parent) :
    Interactable(parent)
{
    setData(data);
}

void Discussion::setData(const QJsonObject &data)
{
    Interactable::setData(data);

    setActiveLockReason(LockReason::fromString(data.value(ApiKey::ACTIVE_LOCK_REASON).toString()));
    setAnswerChosenAt(QDateTime::fromString(data.value(ApiKey::ANSWER_CHOSEN_AT).toString(), Qt::ISODate));
    setAnswerChosenBy(DataUtils::ownerFromJson(data.value(ApiKey::ANSWER_CHOSEN_BY).toObject()));

    const QJsonObject category = data.value(ApiKey::CATEGORY).toObject();
    setCategory(category.value(ApiKey::NAME).toString());
    setCategoryId(category.value(ApiKey::ID).toString());
    setCategoryEmoji(DataUtils::getEmojiLinkFromString(category.value(ApiKey::EMOJI_HTML).toString()));

    setCommentCount(DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject()));
    setCreatedViaEmail(data.value(ApiKey::CREATED_VIA_EMAIL).toBool());
    setEditor(DataUtils::ownerFromJson(data.value(ApiKey::EDITOR).toObject()));
    setLocked(data.value(ApiKey::LOCKED).toBool());
    setNumber(data.value(ApiKey::NUMBER).toInt());
    setPublishedAt(QDateTime::fromString(data.value(ApiKey::PUBLISHED_AT).toString(), Qt::ISODate));

    const QJsonObject repo = data.value(ApiKey::REPOSITORY).toObject();
    setRepository(repo.value(ApiKey::NAME_WITH_OWNER).toString());
    setRepositoryId(repo.value(ApiKey::ID).toString());
    setTitle(data.value(ApiKey::TITLE).toString());
    setViewerSubscription(SubscriptionState::fromString(data.value(ApiKey::VIEWER_SUBSCRIPTION).toString()));
}

quint8 Discussion::activeLockReason() const
{
    return m_activeLockReason;
}

QDateTime Discussion::answerChosenAt() const
{
    return m_answerChosenAt;
}

Owner *Discussion::answerChosenBy() const
{
    return m_answerChosenBy;
}

QString Discussion::category() const
{
    return m_category;
}

QString Discussion::categoryEmoji() const
{
    return m_categoryEmoji;
}

QString Discussion::categoryId() const
{
    return m_categoryId;
}

quint32 Discussion::commentCount() const
{
    return m_commentCount;
}

bool Discussion::createdViaEmail() const
{
    return m_createdViaEmail;
}

Owner *Discussion::editor() const
{
    return m_editor;
}

bool Discussion::locked() const
{
    return m_locked;
}

quint32 Discussion::number() const
{
    return m_number;
}

QDateTime Discussion::publishedAt() const
{
    return m_publishedAt;
}

QString Discussion::repository() const
{
    return m_repository;
}

QString Discussion::repositoryId() const
{
    return m_repositoryId;
}

QString Discussion::title() const
{
    return m_title;
}

quint8 Discussion::viewerSubscription() const
{
    return m_viewerSubscription;
}

void Discussion::setActiveLockReason(quint8 reason)
{
    if (m_activeLockReason == reason)
        return;

    m_activeLockReason = reason;
    emit activeLockReasonChanged(m_activeLockReason);
}

void Discussion::setAnswerChosenAt(const QDateTime &answerChosenAt)
{
    if (m_answerChosenAt == answerChosenAt)
        return;

    m_answerChosenAt = answerChosenAt;
    emit answerChosenAtChanged(m_answerChosenAt);
}

void Discussion::setAnswerChosenBy(Owner *answerChosenBy)
{
    if (m_answerChosenBy == answerChosenBy)
        return;

    m_answerChosenBy = answerChosenBy;
    emit answerChosenByChanged(m_answerChosenBy);
}

void Discussion::setCategory(const QString &category)
{
    if (m_category == category)
        return;

    m_category = category;
    emit categoryChanged(m_category);
}

void Discussion::setCategoryEmoji(const QString &emoji)
{
    if (m_categoryEmoji == emoji)
        return;

    m_categoryEmoji = emoji;
    emit categoryEmojiChanged(m_categoryEmoji);
}

void Discussion::setCategoryId(const QString &id)
{
    if (m_categoryId == id)
        return;

    m_categoryId = id;
    emit categoryIdChanged(m_categoryId);
}

void Discussion::setCommentCount(quint32 count)
{
    if (m_commentCount == count)
        return;

    m_commentCount = count;
    emit commentCountChanged(m_commentCount);
}

void Discussion::setCreatedViaEmail(bool createdViaEmail)
{
    if (m_createdViaEmail == createdViaEmail)
        return;

    m_createdViaEmail = createdViaEmail;
    emit createdViaEmailChanged(m_createdViaEmail);
}

void Discussion::setEditor(Owner *editor)
{
    if (m_editor == editor)
        return;

    m_editor = editor;
    emit editorChanged(m_editor);
}

void Discussion::setLocked(bool locked)
{
    if (m_locked == locked)
        return;

    m_locked = locked;
    emit lockedChanged(m_locked);
}

void Discussion::setNumber(quint32 number)
{
    if (m_number == number)
        return;

    m_number = number;
    emit numberChanged(m_number);
}

void Discussion::setPublishedAt(const QDateTime &publishedAt)
{
    if (m_publishedAt == publishedAt)
        return;

    m_publishedAt = publishedAt;
    emit publishedAtChanged(m_publishedAt);
}

void Discussion::setRepository(const QString &repository)
{
    if (m_repository == repository)
        return;

    m_repository = repository;
    emit repositoryChanged(m_repository);
}

void Discussion::setRepositoryId(const QString &id)
{
    if (m_repositoryId == id)
        return;

    m_repositoryId = id;
    emit repositoryIdChanged(m_repositoryId);
}

void Discussion::setTitle(const QString &title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void Discussion::setViewerSubscription(quint8 subscription)
{
    if (m_viewerSubscription == subscription)
        return;

    m_viewerSubscription = subscription;
    emit viewerSubscriptionChanged(m_viewerSubscription);
}
