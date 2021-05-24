#include "gist.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
GistListItem::GistListItem(const QJsonObject &obj) :
    NodeListItem(obj)
{
    description = obj.value(ApiKey::DESCRIPTION).toString();
    isPublic = obj.value(ApiKey::IS_PUBLIC).toBool();
    commentCount = DataUtils::getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    fileCount = DataUtils::getTotalCount(obj.value(ApiKey::FILES).toObject());
    forkCount = DataUtils::getTotalCount(obj.value(ApiKey::FORKS).toObject());
    stargazerCount = obj.value(ApiKey::STARGAZER_COUNT).toInt();
    createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    pushedAt = QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

    const QJsonObject owner = obj.value(ApiKey::OWNER).toObject();

    ownerLogin = owner.value(ApiKey::LOGIN).toString();
    ownerAvatar = owner.value(ApiKey::AVATAR_URL).toString();
}

// Object
Gist::Gist(QObject *parent) :
    Node(parent)
{

}

quint32 Gist::commetCount() const
{
    return m_commetCount;
}

QDateTime Gist::createdAt() const
{
    return m_createdAt;
}

QString Gist::description() const
{
    return m_description;
}

quint32 Gist::fileCount() const
{
    return m_fileCount;
}

quint32 Gist::forkCount() const
{
    return m_forkCount;
}

bool Gist::isFork() const
{
    return m_isFork;
}

bool Gist::isPublic() const
{
    return m_isPublic;
}

Owner *Gist::owner() const
{
    return m_owner;
}

QDateTime Gist::pushedAt() const
{
    return m_pushedAt;
}

quint32 Gist::stargazerCount() const
{
    return m_stargazerCount;
}

QDateTime Gist::updatedAt() const
{
    return m_updatedAt;
}

bool Gist::viewerHasStarred() const
{
    return m_viewerHasStarred;
}

void Gist::setCommetCount(quint32 count)
{
    if (m_commetCount == count)
        return;

    m_commetCount = count;
    emit commetCountChanged(m_commetCount);
}

void Gist::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged(m_createdAt);
}

void Gist::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(m_description);
}

void Gist::setFileCount(quint32 count)
{
    if (m_fileCount == count)
        return;

    m_fileCount = count;
    emit fileCountChanged(m_fileCount);
}

void Gist::setForkCount(quint32 count)
{
    if (m_forkCount == count)
        return;

    m_forkCount = count;
    emit forkCountChanged(m_forkCount);
}

void Gist::setIsFork(bool isFork)
{
    if (m_isFork == isFork)
        return;

    m_isFork = isFork;
    emit isForkChanged(m_isFork);
}

void Gist::setIsPublic(bool isPublic)
{
    if (m_isPublic == isPublic)
        return;

    m_isPublic = isPublic;
    emit isPublicChanged(m_isPublic);
}

void Gist::setOwner(Owner *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged(m_owner);
}

void Gist::setPushedAt(const QDateTime &pushedAt)
{
    if (m_pushedAt == pushedAt)
        return;

    m_pushedAt = pushedAt;
    emit pushedAtChanged(m_pushedAt);
}

void Gist::setStargazerCount(quint32 count)
{
    if (m_stargazerCount == count)
        return;

    m_stargazerCount = count;
    emit stargazerCountChanged(m_stargazerCount);
}

void Gist::setUpdatedAt(const QDateTime &updatedAt)
{
    if (m_updatedAt == updatedAt)
        return;

    m_updatedAt = updatedAt;
    emit updatedAtChanged(m_updatedAt);
}

void Gist::setViewerHasStarred(bool starred)
{
    if (m_viewerHasStarred == starred)
        return;

    m_viewerHasStarred = starred;
    emit viewerHasStarredChanged(m_viewerHasStarred);
}
