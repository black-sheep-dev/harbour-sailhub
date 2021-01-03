#ifndef COMMENT_H
#define COMMENT_H

#include "node.h"

#include <QDateTime>

#include "owner.h"

class Comment : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime lastEditAt READ lastEditAt WRITE setLastEditAt NOTIFY lastEditAtChanged)
    Q_PROPERTY(bool viewerCanDelete READ viewerCanDelete WRITE setViewerCanDelete NOTIFY viewerCanDeleteChanged)
    Q_PROPERTY(bool viewerCanReact READ viewerCanReact WRITE setViewerCanReact NOTIFY viewerCanReactChanged)
    Q_PROPERTY(bool viewerCanUpdate READ viewerCanUpdate WRITE setViewerCanUpdate NOTIFY viewerCanUpdateChanged)
    Q_PROPERTY(bool viewerDidAuthor READ viewerDidAuthor WRITE setViewerDidAuthor NOTIFY viewerDidAuthorChanged)

public:
    enum CommentType {
        CommentUndefined,
        CommentIssue
    };
    Q_ENUM(CommentType)

    explicit Comment(QObject *parent = nullptr);

    Owner *author() const;
    QString body() const;
    QDateTime createdAt() const;
    QDateTime lastEditAt() const;
    bool viewerCanDelete() const;
    bool viewerCanReact() const;
    bool viewerCanUpdate() const;
    bool viewerDidAuthor() const;

signals:
    void authorChanged(Owner *author);
    void bodyChanged(const QString &body);
    void createdAtChanged(const QDateTime &createdAt);
    void lastEditAtChanged(const QDateTime &lastEditAt);
    void viewerCanDeleteChanged(bool viewerCanDelete);
    void viewerCanReactChanged(bool viewerCanReact);
    void viewerCanUpdateChanged(bool viewerCanUpdate);
    void viewerDidAuthorChanged(bool viewerDidAuthor);

public slots:
    void setAuthor(Owner *author);
    void setBody(const QString &body);
    void setCreatedAt(const QDateTime &createdAt);
    void setLastEditAt(const QDateTime &lastEditAt);
    void setViewerCanDelete(bool viewerCanDelete);
    void setViewerCanReact(bool viewerCanReact);
    void setViewerCanUpdate(bool viewerCanUpdate);
    void setViewerDidAuthor(bool viewerDidAuthor);

private:
    Owner *m_author{nullptr};
    QString m_body;
    QDateTime m_createdAt;
    QDateTime m_lastEditAt;
    bool m_viewerCanDelete{false};
    bool m_viewerCanReact{false};
    bool m_viewerCanUpdate{false};
    bool m_viewerDidAuthor{false};
};

#endif // COMMENT_H
