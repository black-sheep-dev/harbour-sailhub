#ifndef ISSUE_H
#define ISSUE_H

#include "interactable.h"

#include "src/entities/owner.h"
#include "src/enums/issuestate.h"
#include "viewer.h"

#include <QDateTime>

struct IssueListItem : public NodeListItem {
    IssueListItem() = default;
    IssueListItem(const QJsonObject &data);

    bool closed{false};
    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
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
    Q_PROPERTY(quint32 labelCount READ labelCount WRITE setLabelCount NOTIFY labelCountChanged)
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
    Q_PROPERTY(quint32 number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(quint32 participantCount READ participantCount WRITE setParticipantCount NOTIFY participantCountChanged)
    Q_PROPERTY(QString repository READ repository WRITE setRepository NOTIFY repositoryChanged)
    Q_PROPERTY(QString repositoryId READ repositoryId WRITE setRepositoryId NOTIFY repositoryIdChanged)
    Q_PROPERTY(quint8 repositoryPermission READ repositoryPermission WRITE setRepositoryPermission NOTIFY repositoryPermissionChanged)
    Q_PROPERTY(quint8 state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(quint8 viewerSubscription READ viewerSubscription WRITE setViewerSubscription NOTIFY viewerSubscriptionChanged)

public:
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
    Issue(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    quint32 assigneeCount() const;
    quint32 commentCount() const;
    bool edited() const;
    quint32 labelCount() const;
    bool locked() const;
    quint32 number() const;
    quint32 participantCount() const;
    QString repository() const;
    quint8 repositoryPermission() const;
    QString repositoryId() const;
    quint8 state() const;
    QString title() const;
    quint8 viewerSubscription() const;

signals:
    // properties
    void assigneeCountChanged(quint32 count);
    void commentCountChanged(quint32 count);
    void labelCountChanged(quint32 count);
    void numberChanged(quint32 number);
    void participantCountChanged(quint32 count);
    void repositoryChanged(const QString &repository);
    void repositoryIdChanged(const QString &id);
    void repositoryPermissionChanged(quint8 permission);
    void stateChanged(quint8 state);
    void titleChanged(const QString &title); 
    void viewerSubscriptionChanged(quint8 subscription);

    void lockedChanged(bool locked);

public slots:
    // properties
    void setAssigneeCount(quint32 count);
    void setCommentCount(quint32 count);
    void setLabelCount(quint32 count);
    void setLocked(bool locked);
    void setNumber(quint32 number);
    void setParticipantCount(quint32 count);
    void setRepository(const QString &repository);
    void setRepositoryId(const QString &id);
    void setRepositoryPermission(quint8 permission);
    void setState(quint8 state);
    void setTitle(const QString &title);
    void setViewerSubscription(quint8 subscription);

private:
    // properties
    quint32 m_assigneeCount{0};
    quint32 m_commentCount{0};
    quint32 m_labelCount{0};
    bool m_locked{false};
    quint32 m_number{0};
    quint32 m_participantCount{0};
    QString m_repository;
    QString m_repositoryId;
    quint8 m_repositoryPermission{0};
    quint8 m_state{IssueState::Unknown};
    QString m_title;
    quint8 m_viewerSubscription{0};

};

#endif // ISSUE_H
