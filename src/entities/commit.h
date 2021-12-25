#ifndef COMMIT_H
#define COMMIT_H

#include "node.h"

#include <QDateTime>

#include "owner.h"

struct CommitListItem : public NodeListItem {
    CommitListItem() = default;
    CommitListItem(const QJsonObject &data);

    QString authorAvatar;
    QString authorLogin;
    QString messageHeadline;
    QString pushedAtTimeSpan;
    bool verfied{false};
};

class Commit : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString abbreviatedOid READ abbreviatedOid WRITE setAbbreviatedOid NOTIFY abbreviatedOidChanged)
    Q_PROPERTY(quint32 additions READ additions WRITE setAdditions NOTIFY additionsChanged)
    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(quint32 authorCount READ authorCount WRITE setAuthorCount NOTIFY authorCountChanged)
    Q_PROPERTY(bool authoredByCommitter READ authoredByCommitter WRITE setAuthoredByCommitter NOTIFY authoredByCommitterChanged)
    Q_PROPERTY(quint32 changedFiles READ changedFiles WRITE setChangedFiles NOTIFY changedFilesChanged)
    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(QDateTime committedDate READ committedDate WRITE setCommittedDate NOTIFY committedDateChanged)
    Q_PROPERTY(Owner* committer READ committer WRITE setCommitter NOTIFY committerChanged)
    Q_PROPERTY(quint32 deletions READ deletions WRITE setDeletions NOTIFY deletionsChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString messageHeadline READ messageHeadline WRITE setMessageHeadline NOTIFY messageHeadlineChanged)
    Q_PROPERTY(quint32 parentCount READ parentCount WRITE setParentCount NOTIFY parentCountChanged)
    Q_PROPERTY(QDateTime pushedDate READ pushedDate WRITE setPushedDate NOTIFY pushedDateChanged)
    Q_PROPERTY(bool signatureIsValid READ signatureIsValid WRITE setSignatureIsValid NOTIFY signatureIsValidChanged)
    Q_PROPERTY(quint8 signatureState READ signatureState WRITE setSignatureState NOTIFY signatureStateChanged)

public:
    enum CommitType {
        Undefined,
        Parent,
        PullRequest
    };
    Q_ENUM(CommitType)

    explicit Commit(QObject *parent = nullptr);
    Commit(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    const QString &abbreviatedOid() const;
    quint32 additions() const;
    Owner *author() const;
    quint32 authorCount() const;
    bool authoredByCommitter() const;
    quint32 changedFiles() const;
    quint32 commentCount() const;
    const QDateTime &committedDate() const;
    Owner *committer() const;
    quint32 deletions() const;
    const QString &message() const;
    const QString &messageHeadline() const;
    quint32 parentCount() const;
    const QDateTime &pushedDate() const;
    bool signatureIsValid() const;
    quint8 signatureState() const;

signals:
    // properties
    void abbreviatedOidChanged();
    void additionsChanged();
    void authorChanged();
    void authorCountChanged();
    void authoredByCommitterChanged();
    void changedFilesChanged();
    void commentCountChanged();
    void committedDateChanged();
    void committerChanged();
    void deletionsChanged();
    void messageChanged();
    void messageHeadlineChanged();
    void parentCountChanged();
    void pushedDateChanged();
    void signatureIsValidChanged();
    void signatureStateChanged();

public slots:
    // properties
    void setAbbreviatedOid(const QString &id);
    void setAdditions(quint32 count);
    void setAuthor(Owner *author);
    void setAuthorCount(quint32 count);
    void setAuthoredByCommitter(bool authoredByCommitter);
    void setChangedFiles(quint32 count);
    void setCommentCount(quint32 count);
    void setCommittedDate(const QDateTime &date);
    void setCommitter(Owner *committer);
    void setDeletions(quint32 count);
    void setMessage(const QString &message);
    void setMessageHeadline(const QString &headline);
    void setParentCount(quint32 count);
    void setPushedDate(const QDateTime &date);
    void setSignatureIsValid(bool isValid);
    void setSignatureState(quint8 state);

private:
    // properties
    QString m_abbreviatedOid;
    quint32 m_additions{0};
    Owner *m_author{nullptr};
    quint32 m_authorCount{0};
    bool m_authoredByCommitter{false};
    quint32 m_changedFiles{0};
    quint32 m_commentCount{0};
    QDateTime m_committedDate;
    Owner *m_committer{nullptr};
    quint32 m_deletions{0};
    QString m_message;
    QString m_messageHeadline;
    quint32 m_parentCount{0};
    QDateTime m_pushedDate;    
    bool m_signatureIsValid{false};
    quint8 m_signatureState{0};
};

#endif // COMMIT_H
