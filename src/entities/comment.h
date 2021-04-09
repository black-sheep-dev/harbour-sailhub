#ifndef COMMENT_H
#define COMMENT_H

#include "node.h"

#include <QDateTime>

#include "owner.h"

struct CommentListItem {
    QString body;
};

class Comment : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString bodyExcerpt READ bodyExcerpt WRITE setBodyExcerpt NOTIFY bodyExcerptChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString createdAtTimeSpan READ createdAtTimeSpan WRITE setCreatedAtTimeSpan NOTIFY createdAtTimeSpanChanged)
    Q_PROPERTY(bool edited READ edited WRITE setEdited NOTIFY editedChanged)
    Q_PROPERTY(QDateTime lastEditAt READ lastEditAt WRITE setLastEditAt NOTIFY lastEditAtChanged)
    Q_PROPERTY(bool viewerCanDelete READ viewerCanDelete WRITE setViewerCanDelete NOTIFY viewerCanDeleteChanged)
    Q_PROPERTY(bool viewerCanReact READ viewerCanReact WRITE setViewerCanReact NOTIFY viewerCanReactChanged)
    Q_PROPERTY(bool viewerCanUpdate READ viewerCanUpdate WRITE setViewerCanUpdate NOTIFY viewerCanUpdateChanged)
    Q_PROPERTY(bool viewerDidAuthor READ viewerDidAuthor WRITE setViewerDidAuthor NOTIFY viewerDidAuthorChanged)

public:
    enum CommentType {
        Undefined,
        Issue
    };
    Q_ENUM(CommentType)

    explicit Comment(QObject *parent = nullptr);

    Owner *author() const;
    QString body() const;
    QString bodyExcerpt() const;
    QDateTime createdAt() const;
    QString createdAtTimeSpan() const;
    bool edited() const;
    QDateTime lastEditAt() const;
    bool viewerCanDelete() const;
    bool viewerCanReact() const;
    bool viewerCanUpdate() const;
    bool viewerDidAuthor() const;

signals:
    void authorChanged(Owner *author);
    void bodyChanged(const QString &body);
    void bodyExcerptChanged(const QString &excerpt);
    void createdAtChanged(const QDateTime &createdAt);
    void createdAtTimeSpanChanged(const QString &timeSpan);
    void editedChanged(bool edited);
    void lastEditAtChanged(const QDateTime &lastEditAt);
    void viewerCanDeleteChanged(bool viewerCanDelete);
    void viewerCanReactChanged(bool viewerCanReact);
    void viewerCanUpdateChanged(bool viewerCanUpdate);
    void viewerDidAuthorChanged(bool viewerDidAuthor);

public slots:
    void setAuthor(Owner *author);
    void setBody(const QString &body);
    void setBodyExcerpt(const QString &excerpt);
    void setCreatedAt(const QDateTime &createdAt);
    void setCreatedAtTimeSpan(QString createdAtTimeSpan);
    void setEdited(bool edited);
    void setLastEditAt(const QDateTime &lastEditAt);
    void setViewerCanDelete(bool viewerCanDelete);
    void setViewerCanReact(bool viewerCanReact);
    void setViewerCanUpdate(bool viewerCanUpdate);
    void setViewerDidAuthor(bool viewerDidAuthor);

private:
    Owner *m_author{nullptr};
    QString m_body;
    QString m_bodyExcerpt;
    QDateTime m_createdAt;
    QString m_createdAtTimeSpan;
    bool m_edited{false};
    QDateTime m_lastEditAt;
    bool m_viewerCanDelete{false};
    bool m_viewerCanReact{false};
    bool m_viewerCanUpdate{false};
    bool m_viewerDidAuthor{false}; 
};

#endif // COMMENT_H
