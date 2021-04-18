#ifndef COMMENT_H
#define COMMENT_H

#include "node.h"

#include <QDateTime>
#include <QVariantMap>

#include "interactable.h"

struct CommentListItem {
    QString body;
};

class Comment : public Interactable
{
    Q_OBJECT

    Q_PROPERTY(QString bodyExcerpt READ bodyExcerpt WRITE setBodyExcerpt NOTIFY bodyExcerptChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString createdAtTimeSpan READ createdAtTimeSpan WRITE setCreatedAtTimeSpan NOTIFY createdAtTimeSpanChanged)
    Q_PROPERTY(QDateTime lastEditAt READ lastEditAt WRITE setLastEditAt NOTIFY lastEditAtChanged)

public:
    enum CommentType {
        Undefined,
        Issue,
        PullRequest
    };
    Q_ENUM(CommentType)

    explicit Comment(QObject *parent = nullptr);

    QString bodyExcerpt() const;
    QDateTime createdAt() const;
    QString createdAtTimeSpan() const;
    QDateTime lastEditAt() const;

signals:
    void bodyExcerptChanged(const QString &excerpt);
    void createdAtChanged(const QDateTime &createdAt);
    void createdAtTimeSpanChanged(const QString &timeSpan);
    void lastEditAtChanged(const QDateTime &lastEditAt);

public slots:
    void setBodyExcerpt(const QString &excerpt);
    void setCreatedAt(const QDateTime &createdAt);
    void setCreatedAtTimeSpan(QString createdAtTimeSpan);
    void setLastEditAt(const QDateTime &lastEditAt);

private:
    QString m_bodyExcerpt;
    QDateTime m_createdAt;
    QString m_createdAtTimeSpan;
    QDateTime m_lastEditAt;
};

#endif // COMMENT_H
