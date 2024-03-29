#ifndef PULLREQUEST_H
#define PULLREQUEST_H

#include "issue.h"

#include <QDateTime>
#include "src/enums/pullrequeststate.h"

struct PullRequestListItem : public NodeListItem {
    PullRequestListItem() = default;
    PullRequestListItem(const QJsonObject &data);

    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
    quint32 number{0};
    QString repository;
    quint8 state;
    QString timeSpan;
    QString title;
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class PullRequest : public Issue
{
    Q_OBJECT

    Q_PROPERTY(quint32 additions READ additions WRITE setAdditions NOTIFY additionsChanged)
    Q_PROPERTY(QString baseRefName READ baseRefName WRITE setBaseRefName NOTIFY baseRefNameChanged)
    Q_PROPERTY(bool canBeRebased READ canBeRebased WRITE setCanBeRebased NOTIFY canBeRebasedChanged)
    Q_PROPERTY(quint32 changedFiles READ changedFiles WRITE setChangedFiles NOTIFY changedFilesChanged)
    Q_PROPERTY(quint32 commitCount READ commitCount WRITE setCommitCount NOTIFY commitCountChanged)
    Q_PROPERTY(quint32 deletions READ deletions WRITE setDeletions NOTIFY deletionsChanged)
    Q_PROPERTY(QString headRefName READ headRefName WRITE setHeadRefName NOTIFY headRefNameChanged)
    Q_PROPERTY(bool isCrossRepository READ isCrossRepository WRITE setIsCrossRepository NOTIFY isCrossRepositoryChanged)
    Q_PROPERTY(bool maintainerCanModify READ maintainerCanModify WRITE setMaintainerCanModify NOTIFY maintainerCanModifyChanged)
    Q_PROPERTY(quint8 mergeStateStatus READ mergeStateStatus WRITE setMergeStateStatus NOTIFY mergeStateStatusChanged)
    Q_PROPERTY(bool mergeable READ mergeable WRITE setMergeable NOTIFY mergeableChanged)
    Q_PROPERTY(bool merged READ merged WRITE setMerged NOTIFY mergedChanged)
    Q_PROPERTY(QDateTime mergedAt READ mergedAt WRITE setMergedAt NOTIFY mergedAtChanged)
    Q_PROPERTY(Owner* mergedBy READ mergedBy WRITE setMergedBy NOTIFY mergedByChanged)

public:
    enum PullRequestType {
        Undefined,
        Assigned,
        CreatedBy,
        Mentioned,
        Repo,
        User
    };
    Q_ENUM(PullRequestType)

    explicit PullRequest(QObject *parent = nullptr);
    PullRequest(const QJsonObject &data, QObject *parent = nullptr);

    void setData(const QJsonObject &data);

    // properties
    quint32 additions() const;
    const QString &baseRefName() const;
    bool canBeRebased() const;
    quint32 changedFiles() const;
    quint32 commitCount() const;
    quint32 deletions() const;
    const QString &headRefName() const;
    bool isCrossRepository() const;
    bool maintainerCanModify() const;
    quint8 mergeStateStatus() const;
    bool mergeable() const;
    bool merged() const;
    const QDateTime &mergedAt() const;
    Owner *mergedBy() const;

signals:
    // properties
    void additionsChanged();
    void baseRefNameChanged();
    void canBeRebasedChanged();
    void changedFilesChanged();
    void commitCountChanged();
    void deletionsChanged();
    void headRefNameChanged();
    void isCrossRepositoryChanged();
    void maintainerCanModifyChanged();
    void mergeStateStatusChanged();
    void mergeableChanged();
    void mergedChanged();
    void mergedAtChanged();
    void mergedByChanged();


public slots:
    // properties
    void setAdditions(quint32 additions);
    void setBaseRefName(const QString &name);
    void setCanBeRebased(bool canBeRebased);
    void setChangedFiles(quint32 changedFiles);
    void setCommitCount(quint32 commitCount);
    void setDeletions(quint32 deletions);
    void setHeadRefName(const QString &name);
    void setIsCrossRepository(bool isCrossRepository);
    void setMaintainerCanModify(bool maintainerCanModify);
    void setMergeStateStatus(quint8 mergeStateStatus);
    void setMergeable(bool mergeable);
    void setMerged(bool merged);
    void setMergedAt(const QDateTime &mergedAt);
    void setMergedBy(Owner *mergedBy);

private:
    // properties
    quint32 m_additions{0};
    QString m_baseRefName;
    bool m_canBeRebased{false};
    quint32 m_changedFiles{0};
    quint32 m_commitCount{0};
    quint32 m_deletions{0};
    QString m_headRefName;
    bool m_isCrossRepository{false};
    bool m_maintainerCanModify{false};
    quint8 m_mergeStateStatus{0};
    bool m_mergeable{false};
    bool m_merged{false};
    QDateTime m_mergedAt;
    Owner *m_mergedBy{nullptr}; 
};

#endif // PULLREQUEST_H
