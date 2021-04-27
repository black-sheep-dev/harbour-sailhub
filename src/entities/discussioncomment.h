#ifndef DISCUSSIONCOMMENT_H
#define DISCUSSIONCOMMENT_H

#include "interactable.h"

class DiscussionComment : public Interactable
{
    Q_OBJECT

    Q_PROPERTY(bool createdViaEmail READ createdViaEmail WRITE setCreatedViaEmail NOTIFY createdViaEmailChanged)
    Q_PROPERTY(QDateTime deletedAt READ deletedAt WRITE setDeletedAt NOTIFY deletedAtChanged)
    Q_PROPERTY(Owner* editor READ editor WRITE setEditor NOTIFY editorChanged)
    Q_PROPERTY(bool includesCreatedEdit READ includesCreatedEdit WRITE setIncludesCreatedEdit NOTIFY includesCreatedEditChanged)
    Q_PROPERTY(bool isAnswer READ isAnswer WRITE setIsAnswer NOTIFY isAnswerChanged)
    Q_PROPERTY(bool isMinimized READ isMinimized WRITE setIsMinimized NOTIFY isMinimizedChanged)
    Q_PROPERTY(QString minimizedReason READ minimizedReason WRITE setMinimizedReason NOTIFY minimizedReasonChanged)
    Q_PROPERTY(quint32 replyCount READ replyCount WRITE setReplyCount NOTIFY replyCountChanged)
    Q_PROPERTY(QString replyToId READ replyToId WRITE setReplyToId NOTIFY replyToIdChanged)

public:
    explicit DiscussionComment(QObject *parent = nullptr);

    bool createdViaEmail() const;
    QDateTime deletedAt() const;
    Owner *editor() const;
    bool includesCreatedEdit() const;
    bool isAnswer() const;
    bool isMinimized() const;
    QString minimizedReason() const;
    quint32 replyCount() const;
    QString replyToId() const;

signals:
    void createdViaEmailChanged(bool createdViaEmail);
    void deletedAtChanged(const QDateTime &deletedAt);
    void editorChanged(Owner *editor);
    void includesCreatedEditChanged(bool includesCreatedEdit);
    void isAnswerChanged(bool isAnswer);
    void isMinimizedChanged(bool isMinimized);
    void minimizedReasonChanged(const QString &minimizedReason);
    void replyCountChanged(quint32 replyCount);
    void replyToIdChanged(const QString &replyToId);

public slots:
    void setCreatedViaEmail(bool createdViaEmail);
    void setDeletedAt(const QDateTime &deletedAt);
    void setEditor(Owner *editor);
    void setIncludesCreatedEdit(bool includesCreatedEdit);
    void setIsAnswer(bool isAnswer);
    void setIsMinimized(bool isMinimized);
    void setMinimizedReason(const QString &minimizedReason);
    void setReplyCount(quint32 replyCount);
    void setReplyToId(const QString &replyToId);

private:
    bool m_createdViaEmail{false};
    QDateTime m_deletedAt;
    Owner *m_editor{nullptr};
    bool m_includesCreatedEdit{false};
    bool m_isAnswer{false};
    bool m_isMinimized{false};
    QString m_minimizedReason;
    quint32 m_replyCount{0};
    QString m_replyToId;
};

#endif // DISCUSSIONCOMMENT_H
