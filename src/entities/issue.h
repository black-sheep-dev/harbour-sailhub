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
    QString nodeId;
    quint32 number{0};
    QString repository;
    QString title;
    quint8 state{0};
};

class Issue : public Node
{
    Q_OBJECT

    Q_PROPERTY(Owner* author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(quint32 commentCount READ commentCount WRITE setCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(quint8 states READ states WRITE setStates NOTIFY statesChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    enum IssueState {
        StateUnknown    = 0x0,
        StateOpen       = 0x1,
        StateClosed     = 0x2
    };
    Q_ENUM(IssueState)
    Q_DECLARE_FLAGS(IssueStates, IssueState)

    explicit Issue(QObject *parent = nullptr);

    Owner *author() const;
    quint32 commentCount() const;
    quint8 states() const;
    QString title() const;

signals:
    void authorChanged(Owner *author);
    void commentCountChanged(quint32 count);
    void statesChanged(quint8 states);
    void titleChanged(const QString &title);


public slots:
    void setAuthor(Owner *author);
    void setCommentCount(quint32 count);
    void setStates(quint8 states);
    void setTitle(const QString &title);

private:
    Owner* m_author{nullptr};
    quint32 m_commentCount{0};
    quint8 m_states{StateUnknown};
    QString m_title;


};
Q_DECLARE_OPERATORS_FOR_FLAGS(Issue::IssueStates)

#endif // ISSUE_H
