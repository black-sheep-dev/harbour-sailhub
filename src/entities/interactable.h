#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "node.h"
#include "owner.h"

class Interactable : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(bool edited READ edited WRITE setEdited NOTIFY editedChanged)
    Q_PROPERTY(quint32 reactionConfusedCount READ reactionConfusedCount WRITE setReactionConfusedCount NOTIFY reactionConfusedCountChanged)
    Q_PROPERTY(quint32 reactionEyesCount READ reactionEyesCount WRITE setReactionEyesCount NOTIFY reactionEyesCountChanged)
    Q_PROPERTY(quint32 reactionHeartCount READ reactionHeartCount WRITE setReactionHeartCount NOTIFY reactionHeartCountChanged)
    Q_PROPERTY(quint32 reactionHoorayCount READ reactionHoorayCount WRITE setReactionHoorayCount NOTIFY reactionHoorayCountChanged)
    Q_PROPERTY(quint32 reactionLaughCount READ reactionLaughCount WRITE setReactionLaughCount NOTIFY reactionLaughCountChanged)
    Q_PROPERTY(quint32 reactionRocketCount READ reactionRocketCount WRITE setReactionRocketCount NOTIFY reactionRocketCountChanged)
    Q_PROPERTY(quint32 reactionThumbsDownCount READ reactionThumbsDownCount WRITE setReactionThumbsDownCount NOTIFY reactionThumbsDownCountChanged)
    Q_PROPERTY(quint32 reactionThumbsUpCount READ reactionThumbsUpCount WRITE setReactionThumbsUpCount NOTIFY reactionThumbsUpCountChanged)
    Q_PROPERTY(bool viewerDidAuthor READ viewerDidAuthor WRITE setViewerDidAuthor NOTIFY viewerDidAuthorChanged)
    Q_PROPERTY(quint8 viewerReactions READ viewerReactions WRITE setViewerReactions NOTIFY viewerReactionsChanged)

public:
    explicit Interactable(QObject *parent = nullptr);

    Q_INVOKABLE void updateReactionCount(quint8 reactions);

    // properties
    Owner *author() const;
    QString body() const;
    bool edited() const;
    quint32 reactionConfusedCount() const;
    quint32 reactionEyesCount() const;
    quint32 reactionHeartCount() const;
    quint32 reactionHoorayCount() const;
    quint32 reactionLaughCount() const;
    quint32 reactionRocketCount() const;
    quint32 reactionThumbsDownCount() const;
    quint32 reactionThumbsUpCount() const;
    bool viewerDidAuthor() const;
    quint8 viewerReactions() const;

signals:
    // properties
    void authorChanged(Owner* author);
    void bodyChanged(QString body);
    void editedChanged(bool edited);
    void reactionConfusedCountChanged(quint32 reactionConfusedCount);
    void reactionEyesCountChanged(quint32 reactionEyesCount);
    void reactionHeartCountChanged(quint32 reactionHeartCount);
    void reactionHoorayCountChanged(quint32 reactionHoorayCount);
    void reactionLaughCountChanged(quint32 reactionLaughCount);
    void reactionRocketCountChanged(quint32 reactionRocketCount);
    void reactionThumbsDownCountChanged(quint32 reactionThumbsDownCount);
    void reactionThumbsUpCountChanged(quint32 reactionThumbsUpCount);
    void viewerDidAuthorChanged(bool viewerDidAuthor);
    void viewerReactionsChanged(quint8 viewerReactions);

public slots:
    // properties
    void setAuthor(Owner* author);
    void setBody(const QString &body);
    void setEdited(bool edited);
    void setReactionConfusedCount(quint32 count);
    void setReactionEyesCount(quint32 count);
    void setReactionHeartCount(quint32 count);
    void setReactionHoorayCount(quint32 count);
    void setReactionLaughCount(quint32 count);
    void setReactionRocketCount(quint32 count);
    void setReactionThumbsDownCount(quint32 count);
    void setReactionThumbsUpCount(quint32 count);
    void setViewerDidAuthor(bool authored);
    void setViewerReactions(quint8 reactions);

private:
    Owner* m_author{nullptr};
    QString m_body;
    bool m_edited{false};
    quint32 m_reactionConfusedCount{0};
    quint32 m_reactionEyesCount{0};
    quint32 m_reactionHeartCount{0};
    quint32 m_reactionHoorayCount{0};
    quint32 m_reactionLaughCount{0};
    quint32 m_reactionRocketCount{0};
    quint32 m_reactionThumbsDownCount{0};
    quint32 m_reactionThumbsUpCount{0};
    bool m_viewerDidAuthor{false};
    quint8 m_viewerReactions{0};
};

#endif // INTERACTABLE_H
