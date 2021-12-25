#ifndef DISCUSSIONCOMMENT_H
#define DISCUSSIONCOMMENT_H

#include "interactable.h"

class DiscussionComment : public Interactable
{
    Q_OBJECT

    Q_PROPERTY(bool createdViaEmail READ createdViaEmail WRITE setCreatedViaEmail NOTIFY createdViaEmailChanged)
    Q_PROPERTY(QDateTime deletedAt READ deletedAt WRITE setDeletedAt NOTIFY deletedAtChanged)
    Q_PROPERTY(QString discussionId READ discussionId WRITE setDiscussionId NOTIFY discussionIdChanged)
    Q_PROPERTY(Owner* editor READ editor WRITE setEditor NOTIFY editorChanged)
    Q_PROPERTY(bool includesCreatedEdit READ includesCreatedEdit WRITE setIncludesCreatedEdit NOTIFY includesCreatedEditChanged)
    Q_PROPERTY(bool isAnswer READ isAnswer WRITE setIsAnswer NOTIFY isAnswerChanged)
    Q_PROPERTY(bool isMinimized READ isMinimized WRITE setIsMinimized NOTIFY isMinimizedChanged)
    Q_PROPERTY(QString minimizedReason READ minimizedReason WRITE setMinimizedReason NOTIFY minimizedReasonChanged)
    Q_PROPERTY(quint32 replyCount READ replyCount WRITE setReplyCount NOTIFY replyCountChanged)
    Q_PROPERTY(QString replyToId READ replyToId WRITE setReplyToId NOTIFY replyToIdChanged)

public:
    enum DiscussionCommentType {
        Undefined,
        Comment,
        Reply
    };
    Q_ENUM(DiscussionCommentType)

    explicit DiscussionComment(QObject *parent = nullptr);
    DiscussionComment(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    bool createdViaEmail() const;
    const QDateTime &deletedAt() const;
    const QString &discussionId() const;
    Owner *editor() const;
    bool includesCreatedEdit() const;
    bool isAnswer() const;
    bool isMinimized() const;
    const QString &minimizedReason() const;
    quint32 replyCount() const;
    const QString &replyToId() const;

signals:
    // properties
    void createdViaEmailChanged();
    void deletedAtChanged();
    void discussionIdChanged();
    void editorChanged();
    void includesCreatedEditChanged();
    void isAnswerChanged();
    void isMinimizedChanged();
    void minimizedReasonChanged();
    void replyCountChanged();
    void replyToIdChanged();

public slots:
    // properties
    void setCreatedViaEmail(bool createdViaEmail);
    void setDeletedAt(const QDateTime &deletedAt);
    void setDiscussionId(const QString &discussionId);
    void setEditor(Owner *editor);
    void setIncludesCreatedEdit(bool includesCreatedEdit);
    void setIsAnswer(bool isAnswer);
    void setIsMinimized(bool isMinimized);
    void setMinimizedReason(const QString &minimizedReason);
    void setReplyCount(quint32 replyCount);
    void setReplyToId(const QString &replyToId);

private:
    // properties
    bool m_createdViaEmail{false};
    QDateTime m_deletedAt;
    QString m_discussionId;
    Owner *m_editor{nullptr};
    bool m_includesCreatedEdit{false};
    bool m_isAnswer{false};
    bool m_isMinimized{false};
    QString m_minimizedReason;
    quint32 m_replyCount{0};
    QString m_replyToId;
};

#endif // DISCUSSIONCOMMENT_H
