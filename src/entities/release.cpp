#include "release.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
ReleaseListItem::ReleaseListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    createdAtTimeSpan = DataUtils::timeSpanText(createdAt, true);
    isDraft = data.value(ApiKey::IS_DRAFT).toBool();
    isLatest = data.value(ApiKey::IS_LATEST).toBool();
    isPrerelease = data.value(ApiKey::IS_PRERELEASE).toBool();
}

// Object
Release::Release(QObject *parent) :
    Node(parent)
{

}

Release::Release(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Release::setData(const QJsonObject &data)
{
    Node::setData(data);

    // author
    auto author = DataUtils::ownerFromJson(data.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(this);
        setAuthor(author);
    }

    setAssetCount(DataUtils::getTotalCount(data.value(ApiKey::RELEASE_ASSETS).toObject()));
    setCreatedAt(QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    setDescription(data.value(ApiKey::DESCRIPTION).toString());
    setIsDraft(data.value(ApiKey::IS_DRAFT).toBool());
    setIsLatest(data.value(ApiKey::IS_LATEST).toBool());
    setIsPrerelease(data.value(ApiKey::IS_PRERELEASE).toBool());
    setPublishedAt(QDateTime::fromString(data.value(ApiKey::PUBLISHED_AT).toString(), Qt::ISODate));
    setRepository(data.value(ApiKey::REPOSITORY).toObject()
                           .value(ApiKey::NAME_WITH_OWNER).toString());
    setTagCommit(data.value(ApiKey::TAG_COMMIT).toObject()
                          .value(ApiKey::ABBREVIATED_OID).toString());
    setTagName(data.value(ApiKey::TAG_NAME).toString());
}

quint32 Release::assetCount() const
{
    return m_assetCount;
}

Owner *Release::author() const
{
    return m_author;
}

const QDateTime &Release::createdAt() const
{
    return m_createdAt;
}

const QString &Release::description() const
{
    return m_description;
}

bool Release::isDraft() const
{
    return m_isDraft;
}

bool Release::isLatest() const
{
    return m_isLatest;
}

bool Release::isPrerelease() const
{
    return m_isPrerelease;
}

const QDateTime &Release::publishedAt() const
{
    return m_publishedAt;
}

const QString &Release::repository() const
{
    return m_repository;
}

const QString &Release::tagCommit() const
{
    return m_tagCommit;
}

const QString &Release::tagName() const
{
    return m_tagName;
}

void Release::setAssetCount(quint32 assetCount)
{
    if (m_assetCount == assetCount)
        return;

    m_assetCount = assetCount;
    emit assetCountChanged();
}

void Release::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged();
}

void Release::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged();
}

void Release::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged();
}

void Release::setIsDraft(bool isDraft)
{
    if (m_isDraft == isDraft)
        return;

    m_isDraft = isDraft;
    emit isDraftChanged();
}

void Release::setIsLatest(bool isLatest)
{
    if (m_isLatest == isLatest)
        return;

    m_isLatest = isLatest;
    emit isLatestChanged();
}

void Release::setIsPrerelease(bool isPrerelease)
{
    if (m_isPrerelease == isPrerelease)
        return;

    m_isPrerelease = isPrerelease;
    emit isPrereleaseChanged();
}

void Release::setPublishedAt(const QDateTime &publishedAt)
{
    if (m_publishedAt == publishedAt)
        return;

    m_publishedAt = publishedAt;
    emit publishedAtChanged();
}

void Release::setRepository(const QString &repository)
{
    if (m_repository == repository)
        return;

    m_repository = repository;
    emit repositoryChanged();
}

void Release::setTagCommit(const QString &tagCommit)
{
    if (m_tagCommit == tagCommit)
        return;

    m_tagCommit = tagCommit;
    emit tagCommitChanged();
}

void Release::setTagName(const QString &tagName)
{
    if (m_tagName == tagName)
        return;

    m_tagName = tagName;
    emit tagNameChanged();
}
