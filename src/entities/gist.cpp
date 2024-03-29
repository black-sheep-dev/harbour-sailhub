#include "gist.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
GistListItem::GistListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    description = data.value(ApiKey::DESCRIPTION).toString();
    isPublic = data.value(ApiKey::IS_PUBLIC).toBool();
    commentCount = DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject());
    fileCount = DataUtils::getTotalCount(data.value(ApiKey::FILES).toObject());
    forkCount = DataUtils::getTotalCount(data.value(ApiKey::FORKS).toObject());
    stargazerCount = data.value(ApiKey::STARGAZER_COUNT).toInt();
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    pushedAt = QDateTime::fromString(data.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

    const QJsonObject owner = data.value(ApiKey::OWNER).toObject();

    ownerLogin = owner.value(ApiKey::LOGIN).toString();
    ownerAvatar = owner.value(ApiKey::AVATAR_URL).toString();
}

// Object
Gist::Gist(QObject *parent) :
    Node(parent)
{

}

Gist::Gist(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Gist::setData(const QJsonObject &data)
{
    Node::setData(data);

    setCommetCount(DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject()));
    setCreatedAt(QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    setDescription(data.value(ApiKey::DESCRIPTION).toString());
    setForkCount(DataUtils::getTotalCount(data.value(ApiKey::FORKS).toObject()));
    setIsFork(data.value(ApiKey::IS_FORK).toBool());
    setIsPublic(data.value(ApiKey::IS_PUBLIC).toBool());
    setOwner(DataUtils::ownerFromJson(data.value(ApiKey::OWNER).toObject()));
    setPushedAt(QDateTime::fromString(data.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate));
    setStargazerCount(data.value(ApiKey::STARGAZER_COUNT).toInt());
    setUpdatedAt(QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate));
    setViewerHasStarred(data.value(ApiKey::VIEWER_HAS_STARRED).toBool());
}

quint32 Gist::commetCount() const
{
    return m_commetCount;
}

const QDateTime &Gist::createdAt() const
{
    return m_createdAt;
}

const QString &Gist::description() const
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

const QDateTime &Gist::pushedAt() const
{
    return m_pushedAt;
}

quint32 Gist::stargazerCount() const
{
    return m_stargazerCount;
}

const QDateTime &Gist::updatedAt() const
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
    emit commetCountChanged();
}

void Gist::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged();
}

void Gist::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged();
}

void Gist::setFileCount(quint32 count)
{
    if (m_fileCount == count)
        return;

    m_fileCount = count;
    emit fileCountChanged();
}

void Gist::setForkCount(quint32 count)
{
    if (m_forkCount == count)
        return;

    m_forkCount = count;
    emit forkCountChanged();
}

void Gist::setIsFork(bool isFork)
{
    if (m_isFork == isFork)
        return;

    m_isFork = isFork;
    emit isForkChanged();
}

void Gist::setIsPublic(bool isPublic)
{
    if (m_isPublic == isPublic)
        return;

    m_isPublic = isPublic;
    emit isPublicChanged();
}

void Gist::setOwner(Owner *owner)
{
    if (m_owner == owner)
        return;

    m_owner = owner;
    emit ownerChanged();
}

void Gist::setPushedAt(const QDateTime &pushedAt)
{
    if (m_pushedAt == pushedAt)
        return;

    m_pushedAt = pushedAt;
    emit pushedAtChanged();
}

void Gist::setStargazerCount(quint32 count)
{
    if (m_stargazerCount == count)
        return;

    m_stargazerCount = count;
    emit stargazerCountChanged();
}

void Gist::setUpdatedAt(const QDateTime &updatedAt)
{
    if (m_updatedAt == updatedAt)
        return;

    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

void Gist::setViewerHasStarred(bool starred)
{
    if (m_viewerHasStarred == starred)
        return;

    m_viewerHasStarred = starred;
    emit viewerHasStarredChanged();
}
