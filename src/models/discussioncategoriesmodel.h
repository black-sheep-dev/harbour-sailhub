#ifndef DISCUSSIONCATEGORIESMODEL_H
#define DISCUSSIONCATEGORIESMODEL_H

#include "paginationmodel.h"

#include "src/entities/discussioncategory.h"

class DiscussionCategoriesModel : public PaginationModel
{
    Q_OBJECT

public:
    enum DiscussionCategoryRole {
        DescriptionRole         = Qt::UserRole + 1,
        EmojiRole,
        NameRole,
        NodeIdRole
    };
    Q_ENUM(DiscussionCategoryRole)

    explicit DiscussionCategoriesModel(QObject *parent = nullptr);

    void addCategory(const DiscussionCategoryListItem &category);
    void addCategories(const QList<DiscussionCategoryListItem> &categories);
    void setCategories(const QList<DiscussionCategoryListItem> &categories);

private:
    QList<DiscussionCategoryListItem> m_categories;

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

#endif // DISCUSSIONCATEGORIESMODEL_H
