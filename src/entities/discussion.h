#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "interactable.h"

#include <QDateTime>

struct DiscussionListItem : public NodeListItem {
    QString authorAvatar;
    QString authorLogin;
    QString category;
    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
    QString emoji;
    bool locked{false};
    quint8 lockReason{0};
    QString title;
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class Discussion : public Interactable
{
    Q_OBJECT

    Q_PROPERTY(quint8 activeLockReason READ activeLockReason WRITE setActiveLockReason NOTIFY activeLockReasonChanged)
    Q_PROPERTY(QDateTime answerChosenAt READ answerChosenAt WRITE setAnswerChosenAt NOTIFY answerChosenAtChanged)
    Q_PROPERTY(Owner* answerChosenBy READ answerChosenBy WRITE setAnswerChosenBy NOTIFY answerChosenByChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString categoryEmoji READ categoryEmoji WRITE setCategoryEmoji NOTIFY categoryEmojiChanged)
    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(bool createdViaEmail READ createdViaEmail WRITE setCreatedViaEmail NOTIFY createdViaEmailChanged)
    Q_PROPERTY(Owner* editor READ editor WRITE setEditor NOTIFY editorChanged)
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
    Q_PROPERTY(quint32 number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QDateTime publishedAt READ publishedAt WRITE setPublishedAt NOTIFY publishedAtChanged)
    Q_PROPERTY(QString repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(QString repositoryId READ repositoryId WRITE setRepositoryId NOTIFY repositoryIdChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(quint8 viewerSubscription READ viewerSubscription WRITE setViewerSubscription NOTIFY viewerSubscriptionChanged)


public:
    explicit Discussion(QObject *parent = nullptr);

    quint8 activeLockReason() const;
    QDateTime answerChosenAt() const;
    Owner *answerChosenBy() const;
    QString category() const;
    QString categoryEmoji() const;
    QString categoryId() const;
    quint32 commentCount() const;
    bool createdViaEmail() const;
    Owner *editor() const;
    bool locked() const;
    quint32 number() const;
    QDateTime publishedAt() const;
    QString repository() const;
    QString repositoryId() const;
    QString title() const;
    quint8 viewerSubscription() const;

signals:
    void activeLockReasonChanged(quint8 activeLockReason);
    void answerChosenAtChanged(const QDateTime &answerChosenAt);
    void answerChosenByChanged(Owner *answerChosenBy);
    void categoryChanged(const QString &category);
    void categoryEmojiChanged(const QString &categoryEmoji);
    void categoryIdChanged(const QString &categoryId);
    void commentCountChanged(quint32 commentCount);
    void createdViaEmailChanged(bool createdViaEmail);
    void editorChanged(Owner *editor);
    void lockedChanged(bool locked);
    void numberChanged(quint32 number);
    void publishedAtChanged(const QDateTime &publishedAt);
    void repositoryChanged(const QString &repository);
    void repositoryIdChanged(const QString &repositoryId);
    void titleChanged(const QString &title);
    void viewerSubscriptionChanged(quint8 subscription);

public slots:
    void setActiveLockReason(quint8 reason);
    void setAnswerChosenAt(const QDateTime &answerChosenAt);
    void setAnswerChosenBy(Owner *answerChosenBy);
    void setCategory(const QString &category);
    void setCategoryEmoji(const QString &emoji);
    void setCategoryId(const QString &id);
    void setCommentCount(quint32 count);
    void setCreatedViaEmail(bool createdViaEmail);
    void setEditor(Owner *editor);
    void setLocked(bool locked);
    void setNumber(quint32 number);
    void setPublishedAt(const QDateTime &publishedAt);
    void setRepository(const QString &repository);
    void setRepositoryId(const QString &id);
    void setTitle(const QString &title);
    void setViewerSubscription(quint8 subscription);

private:
    quint8 m_activeLockReason{0};
    QDateTime m_answerChosenAt;
    Owner *m_answerChosenBy{nullptr};
    QString m_category;
    QString m_categoryEmoji;
    QString m_categoryId;
    quint32 m_commentCount{0};
    bool m_createdViaEmail{false};
    Owner *m_editor{nullptr};
    bool m_locked{false};
    quint32 m_number{0};
    QDateTime m_publishedAt;
    QString m_repository;
    QString m_repositoryId;
    QString m_title;
    quint8 m_viewerSubscription{0};
};

#endif // DISCUSSION_H
