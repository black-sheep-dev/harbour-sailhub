#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "node.h"
#include "owner.h"

#include <QDateTime>

class Interactable : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString createdAtTimeSpan READ createdAtTimeSpan WRITE setCreatedAtTimeSpan NOTIFY createdAtTimeSpanChanged)
    Q_PROPERTY(bool edited READ edited WRITE setEdited NOTIFY editedChanged)
    Q_PROPERTY(QDateTime lastEditedAt READ lastEditedAt WRITE setLastEditedAt NOTIFY lastEditedAtChanged)
    Q_PROPERTY(quint32 reactionConfusedCount READ reactionConfusedCount WRITE setReactionConfusedCount NOTIFY reactionConfusedCountChanged)
    Q_PROPERTY(quint32 reactionEyesCount READ reactionEyesCount WRITE setReactionEyesCount NOTIFY reactionEyesCountChanged)
    Q_PROPERTY(quint32 reactionHeartCount READ reactionHeartCount WRITE setReactionHeartCount NOTIFY reactionHeartCountChanged)
    Q_PROPERTY(quint32 reactionHoorayCount READ reactionHoorayCount WRITE setReactionHoorayCount NOTIFY reactionHoorayCountChanged)
    Q_PROPERTY(quint32 reactionLaughCount READ reactionLaughCount WRITE setReactionLaughCount NOTIFY reactionLaughCountChanged)
    Q_PROPERTY(quint32 reactionRocketCount READ reactionRocketCount WRITE setReactionRocketCount NOTIFY reactionRocketCountChanged)
    Q_PROPERTY(quint32 reactionThumbsDownCount READ reactionThumbsDownCount WRITE setReactionThumbsDownCount NOTIFY reactionThumbsDownCountChanged)
    Q_PROPERTY(quint32 reactionThumbsUpCount READ reactionThumbsUpCount WRITE setReactionThumbsUpCount NOTIFY reactionThumbsUpCountChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QString updatedAtTimeSpan READ updatedAtTimeSpan WRITE setUpdatedAtTimeSpan NOTIFY updatedAtTimeSpanChanged)
    Q_PROPERTY(bool viewerDidAuthor READ viewerDidAuthor WRITE setViewerDidAuthor NOTIFY viewerDidAuthorChanged)
    Q_PROPERTY(quint8 viewerReactions READ viewerReactions WRITE setViewerReactions NOTIFY viewerReactionsChanged)

public:
    explicit Interactable(QObject *parent = nullptr);
    Interactable(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    Q_INVOKABLE void updateReactionCount(quint8 reactions);

    // properties
    Owner *author() const;
    const QString &body() const;
    const QDateTime &createdAt() const;
    const QString &createdAtTimeSpan() const;
    bool edited() const;
    const QDateTime &lastEditedAt() const;
    quint32 reactionConfusedCount() const;
    quint32 reactionEyesCount() const;
    quint32 reactionHeartCount() const;
    quint32 reactionHoorayCount() const;
    quint32 reactionLaughCount() const;
    quint32 reactionRocketCount() const;
    quint32 reactionThumbsDownCount() const;
    quint32 reactionThumbsUpCount() const;
    const QDateTime &updatedAt() const;
    const QString &updatedAtTimeSpan() const;
    bool viewerDidAuthor() const;
    quint8 viewerReactions() const;

signals:
    // properties
    void authorChanged();
    void bodyChanged();
    void createdAtChanged();
    void createdAtTimeSpanChanged();
    void editedChanged();
    void lastEditedAtChanged();
    void reactionConfusedCountChanged();
    void reactionEyesCountChanged();
    void reactionHeartCountChanged();
    void reactionHoorayCountChanged();
    void reactionLaughCountChanged();
    void reactionRocketCountChanged();
    void reactionThumbsDownCountChanged();
    void reactionThumbsUpCountChanged();
    void updatedAtChanged();
    void updatedAtTimeSpanChanged();
    void viewerDidAuthorChanged();
    void viewerReactionsChanged();

public slots:
    // properties
    void setAuthor(Owner* author);
    void setBody(const QString &body);
    void setCreatedAt(const QDateTime &createdAt);
    void setCreatedAtTimeSpan(const QString &createdAtTimeSpan);
    void setEdited(bool edited);
    void setLastEditedAt(const QDateTime &lastEditedAt);
    void setReactionConfusedCount(quint32 count);
    void setReactionEyesCount(quint32 count);
    void setReactionHeartCount(quint32 count);
    void setReactionHoorayCount(quint32 count);
    void setReactionLaughCount(quint32 count);
    void setReactionRocketCount(quint32 count);
    void setReactionThumbsDownCount(quint32 count);
    void setReactionThumbsUpCount(quint32 count);
    void setUpdatedAt(const QDateTime &updatedAt);
    void setUpdatedAtTimeSpan(const QString &updatedAtTimeSpan);
    void setViewerDidAuthor(bool authored);
    void setViewerReactions(quint8 reactions);

private:
    Owner* m_author{nullptr};
    QString m_body;
    QDateTime m_createdAt;
    QString m_createdAtTimeSpan;
    bool m_edited{false};
    QDateTime m_lastEditedAt;
    quint32 m_reactionConfusedCount{0};
    quint32 m_reactionEyesCount{0};
    quint32 m_reactionHeartCount{0};
    quint32 m_reactionHoorayCount{0};
    quint32 m_reactionLaughCount{0};
    quint32 m_reactionRocketCount{0};
    quint32 m_reactionThumbsDownCount{0};
    quint32 m_reactionThumbsUpCount{0};
    QDateTime m_updatedAt;
    QString m_updatedAtTimeSpan;
    bool m_viewerDidAuthor{false};
    quint8 m_viewerReactions{0};
};

#endif // INTERACTABLE_H
