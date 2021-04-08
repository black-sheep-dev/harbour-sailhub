#ifndef PULLREQUEST_H
#define PULLREQUEST_H

#include "node.h"

#include <QDateTime>

struct PullRequestListItem {
    quint32 commentCount{0};
    QDateTime createdAt;
    QString createdAtTimeSpan;
    QString nodeId;
    quint32 number{0};
    QString repository;
    quint8 state;
    QString timeSpan;
    QString title;
    QDateTime updatedAt;
    QString updatedAtTimeSpan;
};

class PullRequest : public Node
{
    Q_OBJECT

public:
    enum PullRequestState {
        StateUnknown    = 0x0,
        StateOpen       = 0x1,
        StateClosed     = 0x2,
        StateMerged     = 0x3
    };
    Q_ENUM(PullRequestState)
    Q_DECLARE_FLAGS(PullRequestStates, PullRequestState)

    enum PullRequestType {
        Undefined,
        Repo,
        User
    };
    Q_ENUM(PullRequestType)

    explicit PullRequest(QObject *parent = nullptr);

signals:

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PullRequest::PullRequestStates)

#endif // PULLREQUEST_H
