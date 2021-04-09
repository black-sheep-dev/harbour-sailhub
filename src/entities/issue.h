#ifndef ISSUE_H
#define ISSUE_H

#include "node.h"

#include "src/entities/owner.h"
#include "src/models/commentsmodel.h"

#include <QDateTime>

struct IssueListItem {
    bool closed{false};
    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
    QString nodeId;
    quint32 number{0};
    QString repository;
    QString title;
    quint8 state{0};
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class Issue : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString createdAtTimeSpan READ createdAtTimeSpan WRITE setCreatedAtTimeSpan NOTIFY createdAtTimeSpanChanged)
    Q_PROPERTY(bool edited READ edited WRITE setEdited NOTIFY editedChanged)
    Q_PROPERTY(quint32 number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(quint8 states READ states WRITE setStates NOTIFY statesChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(bool viewerCanUpdate READ viewerCanUpdate WRITE setViewerCanUpdate NOTIFY viewerCanUpdateChanged)

public:
    enum IssueState {
        StateUnknown    = 0x0,
        StateOpen       = 0x1,
        StateClosed     = 0x2
    };
    Q_ENUM(IssueState)
    Q_DECLARE_FLAGS(IssueStates, IssueState)

    enum IssueType {
        Undefined,
        Repo,
        User
    };
    Q_ENUM(IssueType)

    explicit Issue(QObject *parent = nullptr);

    Owner *author() const;
    QString body() const;
    quint32 commentCount() const;
    QDateTime createdAt() const;
    QString createdAtTimeSpan() const;
    bool edited() const;
    quint32 number() const;
    QString repository() const;
    quint8 states() const;
    QString title() const;
    QDateTime updatedAt() const;
    bool viewerCanUpdate() const;

signals:
    void authorChanged(Owner *author);
    void bodyChanged(const QString &body);
    void commentCountChanged(quint32 count);
    void createdAtChanged(const QDateTime &timestamp);
    void createdAtTimeSpanChanged(const QString &timeSpan);
    void editedChanged(bool edited);
    void numberChanged(quint32 number);
    void repositoryChanged(const QString &repository);
    void statesChanged(quint8 states);
    void titleChanged(const QString &title);
    void updatedAtChanged(const QDateTime &timestamp);
    void viewerCanUpdateChanged(bool viewerCanUpdate);

public slots:
    void setAuthor(Owner *author);
    void setBody(const QString &body);
    void setCommentCount(quint32 count);
    void setCreatedAt(const QDateTime &timestamp);
    void setCreatedAtTimeSpan(const QString &timeSpan);
    void setEdited(bool edited);
    void setNumber(quint32 number);
    void setRepository(const QString &repository);
    void setStates(quint8 states);
    void setTitle(const QString &title);
    void setUpdatedAt(const QDateTime &timestamp);
    void setViewerCanUpdate(bool viewerCanUpdate);

private:
    Owner* m_author{nullptr};
    QString m_body;
    quint32 m_commentCount{0};
    QDateTime m_createdAt;
    QString m_createdAtTimeSpan;
    bool m_edited{false};
    quint32 m_number{0};
    QString m_repository;
    quint8 m_states{StateUnknown};
    QString m_title;
    QDateTime m_updatedAt;
    bool m_viewerCanUpdate{false};
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Issue::IssueStates)

#endif // ISSUE_H
