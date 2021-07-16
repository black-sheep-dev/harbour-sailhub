#ifndef DISCUSSIONSMODEL_H
#define DISCUSSIONSMODEL_H

#include "paginationmodel.h"

#include "src/entities/discussion.h"

class DiscussionsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum DiscussionRoles {
        AuthorAvatarRole            = Qt::UserRole + 1,
        AuthorLoginRole,
        CategoryRole,
        CommentCountRole,
        CreatedAtRole,
        CreatedAtTimeSpanRole,
        EmojiRole,
        LockedRole,
        NodeIdRole,
        TitleRole,
        UpdatedAtRole,
        UpdatedAtTimeSpanRole,
        ViewerAbilitiesRole
    };
    Q_ENUM(DiscussionRoles)

    explicit DiscussionsModel(QObject *parent = nullptr);
    ~DiscussionsModel() override;

    void addDiscussion(const DiscussionListItem &discussion);
    void addDiscussions(const QList<DiscussionListItem> &discussions);
    void setDiscussions(const QList<DiscussionListItem> &discussions);

private:
    QList<DiscussionListItem> m_discussions;


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
    QString sortField() const override;
};

#endif // DISCUSSIONSMODEL_H
