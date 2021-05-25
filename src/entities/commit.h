#ifndef COMMIT_H
#define COMMIT_H

#include "node.h"

#include "owner.h"

struct CommitListItem : public NodeListItem {
    CommitListItem() = default;
    CommitListItem(const QJsonObject &data);

    QString authorAvatar;
    QString authorLogin;
    QString messageHeadline;
    QString pushedAtTimeSpan;
};

class Commit : public Node
{
    Q_OBJECT

//    Q_PROPERTY(quint32 additions READ additions WRITE setAdditions NOTIFY additionsChanged)
//    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
//    Q_PROPERTY(bool authoredByCommitter READ authoredByCommitter WRITE setAuthoredByCommitter NOTIFY authoredByCommitterChanged)
//    Q_PROPERTY(quint32 chnagedFiles READ chnagedFiles WRITE setChnagedFiles NOTIFY chnagedFilesChanged)
//    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
//    Q_PROPERTY(QDateTime committedDate READ committedDate WRITE setCommittedDate NOTIFY committedDateChanged)
//    Q_PROPERTY(Owner* committer READ committer WRITE setCommitter NOTIFY committerChanged)
//    Q_PROPERTY(quint32 deletions READ deletions WRITE setDeletions NOTIFY deletionsChanged)
//    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
//    Q_PROPERTY(QString messageHeadline READ messageHeadline WRITE setMessageHeadline NOTIFY messageHeadlineChanged)
//    Q_PROPERTY(QDateTime pushedDate READ pushedDate WRITE setPushedDate NOTIFY pushedDateChanged)

public:
    enum CommitType {
        Undefined,
        PullRequest
    };
    Q_ENUM(CommitType)

    explicit Commit(QObject *parent = nullptr);

signals:

public slots:

private:

};

#endif // COMMIT_H
