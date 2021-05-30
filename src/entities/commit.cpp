#include "commit.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/enums/gitsignaturestate"

// List Item
CommitListItem::CommitListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    const QJsonObject author = data.value(ApiKey::AUTHOR).toObject().value(ApiKey::USER).toObject();

    authorAvatar = author.value(ApiKey::AVATAR_URL).toString();
    authorLogin = author.value(ApiKey::LOGIN).toString();
    messageHeadline = data.value(ApiKey::MESSAGE_HEADLINE).toString();
    pushedAtTimeSpan = DataUtils::timeSpanText(QDateTime::fromString(data.value(ApiKey::COMMITTER).toObject().value(ApiKey::DATE).toString(), Qt::ISODate), true);
    verfied = data.value(ApiKey::SIGNATURE).toObject().value(ApiKey::IS_VALID).toBool();
}

// Object
Commit::Commit(QObject *parent) :
    Node(parent)
{

}

Commit::Commit(const QJsonObject &data, QObject *parent) :
    Node(parent)
{
    setData(data);
}

void Commit::setData(const QJsonObject &data)
{
    Node::setData(data);

    setAbbreviatedOid(data.value(ApiKey::ABBREVIATED_OID).toString());
    setAdditions(data.value(ApiKey::ADDITIONS).toInt());
    setAuthor(DataUtils::ownerFromGitActorJson(data.value(ApiKey::AUTHOR).toObject()));
    setAuthorCount(DataUtils::getTotalCount(data.value(ApiKey::AUTHORS).toObject()));
    setAuthoredByCommitter(data.value(ApiKey::AUTHORED_BY_COMMITTER).toBool());
    setChangedFiles(data.value(ApiKey::CHANGED_FILES).toInt());
    setCommentCount(DataUtils::getTotalCount(data.value(ApiKey::COMMENTS).toObject()));
    setCommittedDate(QDateTime::fromString(data.value(ApiKey::COMMITTED_DATE).toString(), Qt::ISODate));
    setCommitter(DataUtils::ownerFromGitActorJson(data.value(ApiKey::COMMITTER).toObject()));
    setDeletions(data.value(ApiKey::DELETIONS).toInt());
    setMessage(data.value(ApiKey::MESSAGE).toString());
    setMessageHeadline(data.value(ApiKey::MESSAGE_HEADLINE).toString());
    setParentCount(DataUtils::getTotalCount(data.value(ApiKey::PARENTS).toObject()));
    setPushedDate(QDateTime::fromString(data.value(ApiKey::PUSHED_DATE).toString(), Qt::ISODate));

    const QJsonObject signature = data.value(ApiKey::SIGNATURE).toObject();

    setSignatureIsValid(signature.value(ApiKey::IS_VALID).toBool());
    setSignatureState(GitSignatureState::fromString(signature.value(ApiKey::STATE).toString()));
}

QString Commit::abbreviatedOid() const
{
    return m_abbreviatedOid;
}

quint32 Commit::additions() const
{
    return m_additions;
}

Owner *Commit::author() const
{
    return m_author;
}

quint32 Commit::authorCount() const
{
    return m_authorCount;
}

bool Commit::authoredByCommitter() const
{
    return m_authoredByCommitter;
}

quint32 Commit::changedFiles() const
{
    return m_changedFiles;
}

quint32 Commit::commentCount() const
{
    return m_commentCount;
}

QDateTime Commit::committedDate() const
{
    return m_committedDate;
}

Owner *Commit::committer() const
{
    return m_committer;
}

quint32 Commit::deletions() const
{
    return m_deletions;
}

QString Commit::message() const
{
    return m_message;
}

QString Commit::messageHeadline() const
{
    return m_messageHeadline;
}

quint32 Commit::parentCount() const
{
    return m_parentCount;
}

QDateTime Commit::pushedDate() const
{
    return m_pushedDate;
}

bool Commit::signatureIsValid() const
{
    return m_signatureIsValid;
}

quint8 Commit::signatureState() const
{
    return m_signatureState;
}

void Commit::setAbbreviatedOid(const QString &id)
{
    if (m_abbreviatedOid == id)
        return;

    m_abbreviatedOid = id;
    emit abbreviatedOidChanged(m_abbreviatedOid);
}

void Commit::setAdditions(quint32 count)
{
    if (m_additions == count)
        return;

    m_additions = count;
    emit additionsChanged(m_additions);
}

void Commit::setAuthor(Owner *author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(m_author);
}

void Commit::setAuthorCount(quint32 count)
{
    if (m_authorCount == count)
        return;

    m_authorCount = count;
    emit authorCountChanged(m_authorCount);
}

void Commit::setAuthoredByCommitter(bool authoredByCommitter)
{
    if (m_authoredByCommitter == authoredByCommitter)
        return;

    m_authoredByCommitter = authoredByCommitter;
    emit authoredByCommitterChanged(m_authoredByCommitter);
}

void Commit::setChangedFiles(quint32 count)
{
    if (m_changedFiles == count)
        return;

    m_changedFiles = count;
    emit changedFilesChanged(m_changedFiles);
}

void Commit::setCommentCount(quint32 count)
{
    if (m_commentCount == count)
        return;

    m_commentCount = count;
    emit commentCountChanged(m_commentCount);
}

void Commit::setCommittedDate(const QDateTime &date)
{
    if (m_committedDate == date)
        return;

    m_committedDate = date;
    emit committedDateChanged(m_committedDate);
}

void Commit::setCommitter(Owner *committer)
{
    if (m_committer == committer)
        return;

    m_committer = committer;
    emit committerChanged(m_committer);
}

void Commit::setDeletions(quint32 count)
{
    if (m_deletions == count)
        return;

    m_deletions = count;
    emit deletionsChanged(m_deletions);
}

void Commit::setMessage(const QString &message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(m_message);
}

void Commit::setMessageHeadline(const QString &headline)
{
    if (m_messageHeadline == headline)
        return;

    m_messageHeadline = headline;
    emit messageHeadlineChanged(m_messageHeadline);
}

void Commit::setParentCount(quint32 count)
{
    if (m_parentCount == count)
        return;

    m_parentCount = count;
    emit parentCountChanged(m_parentCount);
}

void Commit::setPushedDate(const QDateTime &date)
{
    if (m_pushedDate == date)
        return;

    m_pushedDate = date;
    emit pushedDateChanged(m_pushedDate);
}

void Commit::setSignatureIsValid(bool isValid)
{
    if (m_signatureIsValid == isValid)
        return;

    m_signatureIsValid = isValid;
    emit signatureIsValidChanged(m_signatureIsValid);
}

void Commit::setSignatureState(quint8 state)
{
    if (m_signatureState == state)
        return;

    m_signatureState = state;
    emit signatureStateChanged(m_signatureState);
}

