#ifndef DISCUSSIONCOMMENTSMODEL_H
#define DISCUSSIONCOMMENTSMODEL_H

#include "paginationmodel.h"

#include "src/entities/discussioncomment.h"

class DiscussionCommentsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum DiscussionCommentRoles {
        AuthorAvatarRole            = Qt::UserRole + 1,
        AuthorLoginRole,
        BodyRole,
        CreatedAtTimeSpanRole

    };
    Q_ENUM(DiscussionCommentRoles)

    explicit DiscussionCommentsModel(QObject *parent = nullptr);

    Q_INVOKABLE DiscussionComment *commentAt(const int index);
    Q_INVOKABLE int count();

    void addComment(DiscussionComment *comment);
    void addComments(const QList<DiscussionComment *> &comments);
    void setComments(const QList<DiscussionComment *> &comments);

signals:
    void commentsAdded(int lastIndex, int count);

private:
    QList<DiscussionComment *> m_comments;


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // PaginationModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
};

#endif // DISCUSSIONCOMMENTSMODEL_H
