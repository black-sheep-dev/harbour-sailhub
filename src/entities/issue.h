#ifndef ISSUE_H
#define ISSUE_H

#include "interactable.h"

#include "src/entities/owner.h"
#include "viewer.h"

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

class Issue : public Interactable
{
    Q_OBJECT

    Q_PROPERTY(quint32 assigneeCount READ assigneeCount WRITE setAssigneeCount NOTIFY assigneeCountChanged)
    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString createdAtTimeSpan READ createdAtTimeSpan WRITE setCreatedAtTimeSpan NOTIFY createdAtTimeSpanChanged)
    Q_PROPERTY(quint32 labelCount READ labelCount WRITE setLabelCount NOTIFY labelCountChanged)
    Q_PROPERTY(quint32 number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(quint32 participantCount READ participantCount WRITE setParticipantCount NOTIFY participantCountChanged)
    Q_PROPERTY(QString repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(quint8 states READ states WRITE setStates NOTIFY statesChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)

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
        Assigned,
        CreatedBy,
        Mentioned,
        Repo,
        Repos,
        User
    };
    Q_ENUM(IssueType)

    explicit Issue(QObject *parent = nullptr);

    // properties
    quint32 assigneeCount() const;
    quint32 commentCount() const;
    QDateTime createdAt() const;
    QString createdAtTimeSpan() const;
    bool edited() const;
    quint32 labelCount() const;
    quint32 number() const;
    quint32 participantCount() const;
    QString repository() const;
    quint8 states() const;
    QString title() const;
    QDateTime updatedAt() const; 

signals:
    // properties
    void assigneeCountChanged(quint32 count);
    void commentCountChanged(quint32 count);
    void createdAtChanged(const QDateTime &timestamp);
    void createdAtTimeSpanChanged(const QString &timeSpan);
    void labelCountChanged(quint32 count);
    void numberChanged(quint32 number);
    void participantCountChanged(quint32 count);
    void repositoryChanged(const QString &repository);
    void statesChanged(quint8 states);
    void titleChanged(const QString &title);
    void updatedAtChanged(const QDateTime &timestamp);

public slots:
    // properties
    void setAssigneeCount(quint32 count);
    void setCommentCount(quint32 count);
    void setCreatedAt(const QDateTime &timestamp);
    void setCreatedAtTimeSpan(const QString &timeSpan);
    void setLabelCount(quint32 count);
    void setNumber(quint32 number);
    void setParticipantCount(quint32 count);
    void setRepository(const QString &repository);
    void setStates(quint8 states);
    void setTitle(const QString &title);
    void setUpdatedAt(const QDateTime &timestamp); 

private:
    // properties

    quint32 m_assigneeCount{0};
    quint32 m_commentCount{0};
    QDateTime m_createdAt;
    QString m_createdAtTimeSpan;
    quint32 m_labelCount{0};
    quint32 m_number{0};
    quint32 m_participantCount{0};
    QString m_repository;
    quint8 m_states{StateUnknown};
    QString m_title;
    QDateTime m_updatedAt;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Issue::IssueStates)

#endif // ISSUE_H
