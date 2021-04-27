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

public:
    enum CommentType {
        Undefined,
        Issue,
        PullRequest
    };
    Q_ENUM(CommentType)

    explicit Comment(QObject *parent = nullptr);

    QString bodyExcerpt() const;

signals:
    void bodyExcerptChanged(const QString &excerpt);

public slots:
    void setBodyExcerpt(const QString &excerpt);

private:
    QString m_bodyExcerpt;
};

#endif // COMMENT_H
