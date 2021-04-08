#ifndef COMMENTSMODEL_H
#define COMMENTSMODEL_H

#include "paginationmodel.h"

#include "src/entities/comment.h"

class CommentsModel : public PaginationModel
{
    Q_OBJECT
public:
    enum CommentRoles {
        AuthorIdRole          = Qt::UserRole + 1,
        AuthorAvatarUrlRole,
        AuthorLoginRole,
        BodyRole,
        CreatedAtRole,
        CreatedAtTimeSpanRole,
        EditedRole,
        LastEditAtRole,
        ViewerCanDeleteRole,
        ViewerCanReactRole,
        ViewerCanUpdateRole,
        ViewerDidAuthorRole
    };
    Q_ENUM(CommentRoles)

    explicit CommentsModel(QObject *parent = nullptr);

    void addComment(Comment *comment);
    void addComments(const QList<Comment *> &comments);
    void setComments(const QList<Comment *> &comments);

private:
    QList<Comment *> m_comments;

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

#endif // COMMENTSMODEL_H
