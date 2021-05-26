#include "pullrequest.h"

#include "src/api/keys.h"
#include "src/api/datautils.h"
#include "src/enums/mergestatestatus.h"

// List Item
PullRequestListItem::PullRequestListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    commentCount = DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject());
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    createdAtTimeSpan = DataUtils::timeSpanText(createdAt, true);
    number = quint32(data.value(ApiKey::NUMBER).toInt());
    repository = data.value(ApiKey::REPOSITORY).toObject()
            .value(ApiKey::NAME_WITH_OWNER).toString();
    state = PullRequestState::fromString(data.value(ApiKey::STATE).toString());

    timeSpan = DataUtils::timeSpanText(createdAt, true);
    title = data.value(ApiKey::TITLE).toString();
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    updatedAtTimeSpan = DataUtils::timeSpanText(updatedAt, true);
}

// Object
PullRequest::PullRequest(QObject *parent) :
    Issue(parent)
{

}

PullRequest::PullRequest(const QJsonObject &data, QObject *parent) :
    Issue(parent)
{
    setData(data);
}

void PullRequest::setData(const QJsonObject &data)
{
    Issue::setData(data);

    setAdditions(data.value(ApiKey::ADDITIONS).toInt());
    setBaseRefName(data.value(ApiKey::BASE_REF_NAME).toString());
    setCanBeRebased(data.value(ApiKey::CAN_BE_REBASED).toBool());
    setChangedFiles(data.value(ApiKey::CHANGED_FILES).toInt());
    setCommitCount(DataUtils::getTotalCount(data.value(ApiKey::COMMITS).toObject()));
    setDeletions(data.value(ApiKey::DELETIONS).toInt());
    setHeadRefName(data.value(ApiKey::HEAD_REF_NAME).toString());
    setIsCrossRepository(data.value(ApiKey::IS_CROSS_REPOSITORY).toBool());
    setMaintainerCanModify(data.value(ApiKey::MAINTAINER_CAN_MODIFY).toBool());
    setMergeStateStatus(MergeStateStatus::fromString(data.value(ApiKey::MERGE_STATE_STATUS).toString()));
    setMergeable(data.value(ApiKey::MERGEABLE).toBool());
    setMergedAt(QDateTime::fromString(data.value(ApiKey::MERGED_AT).toString(), Qt::ISODate));
    setMergedBy(DataUtils::ownerFromJson(data.value(ApiKey::MERGEG_BY).toObject()));
    setState(PullRequestState::fromString(data.value(ApiKey::STATE).toString()));
}

quint32 PullRequest::additions() const
{
    return m_additions;
}

QString PullRequest::baseRefName() const
{
    return m_baseRefName;
}

bool PullRequest::canBeRebased() const
{
    return m_canBeRebased;
}

quint32 PullRequest::changedFiles() const
{
    return m_changedFiles;
}

quint32 PullRequest::commitCount() const
{
    return m_commitCount;
}

quint32 PullRequest::deletions() const
{
    return m_deletions;
}

QString PullRequest::headRefName() const
{
    return m_headRefName;
}

bool PullRequest::isCrossRepository() const
{
    return m_isCrossRepository;
}

bool PullRequest::maintainerCanModify() const
{
    return m_maintainerCanModify;
}

quint8 PullRequest::mergeStateStatus() const
{
    return m_mergeStateStatus;
}

bool PullRequest::mergeable() const
{
    return m_mergeable;
}

bool PullRequest::merged() const
{
    return m_merged;
}

QDateTime PullRequest::mergedAt() const
{
    return m_mergedAt;
}

Owner *PullRequest::mergedBy() const
{
    return m_mergedBy;
}

void PullRequest::setAdditions(quint32 additions)
{
    if (m_additions == additions)
        return;

    m_additions = additions;
    emit additionsChanged(m_additions);
}

void PullRequest::setBaseRefName(const QString &name)
{
    if (m_baseRefName == name)
        return;

    m_baseRefName = name;
    emit baseRefNameChanged(m_baseRefName);
}

void PullRequest::setCanBeRebased(bool canBeRebased)
{
    if (m_canBeRebased == canBeRebased)
        return;

    m_canBeRebased = canBeRebased;
    emit canBeRebasedChanged(m_canBeRebased);
}

void PullRequest::setChangedFiles(quint32 changedFiles)
{
    if (m_changedFiles == changedFiles)
        return;

    m_changedFiles = changedFiles;
    emit changedFilesChanged(m_changedFiles);
}

void PullRequest::setCommitCount(quint32 commitCount)
{
    if (m_commitCount == commitCount)
        return;

    m_commitCount = commitCount;
    emit commitCountChanged(m_commitCount);
}

void PullRequest::setDeletions(quint32 deletions)
{
    if (m_deletions == deletions)
        return;

    m_deletions = deletions;
    emit deletionsChanged(m_deletions);
}

void PullRequest::setHeadRefName(const QString &name)
{
    if (m_headRefName == name)
        return;

    m_headRefName = name;
    emit headRefNameChanged(m_headRefName);
}

void PullRequest::setIsCrossRepository(bool isCrossRepository)
{
    if (m_isCrossRepository == isCrossRepository)
        return;

    m_isCrossRepository = isCrossRepository;
    emit isCrossRepositoryChanged(m_isCrossRepository);
}

void PullRequest::setMaintainerCanModify(bool maintainerCanModify)
{
    if (m_maintainerCanModify == maintainerCanModify)
        return;

    m_maintainerCanModify = maintainerCanModify;
    emit maintainerCanModifyChanged(m_maintainerCanModify);
}

void PullRequest::setMergeStateStatus(quint8 mergeStateStatus)
{
    if (m_mergeStateStatus == mergeStateStatus)
        return;

    m_mergeStateStatus = mergeStateStatus;
    emit mergeStateStatusChanged(m_mergeStateStatus);
}

void PullRequest::setMergeable(bool mergeable)
{
    if (m_mergeable == mergeable)
        return;

    m_mergeable = mergeable;
    emit mergeableChanged(m_mergeable);
}

void PullRequest::setMerged(bool merged)
{
    if (m_merged == merged)
        return;

    m_merged = merged;
    emit mergedChanged(m_merged);
}

void PullRequest::setMergedAt(const QDateTime &mergedAt)
{
    if (m_mergedAt == mergedAt)
        return;

    m_mergedAt = mergedAt;
    emit mergedAtChanged(m_mergedAt);
}

void PullRequest::setMergedBy(Owner *mergedBy)
{
    if (m_mergedBy == mergedBy)
        return;

    m_mergedBy = mergedBy;
    emit mergedByChanged(m_mergedBy);
}
