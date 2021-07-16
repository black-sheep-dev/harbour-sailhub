#ifndef GISTSMODEL_H
#define GISTSMODEL_H

#include "paginationmodel.h"

#include "src/entities/gist.h"

class GistsModel : public PaginationModel
{
    Q_OBJECT
public:
    enum GistRoles {
        CommentCountRole        = Qt::UserRole + 1,
        CreatedAtRole,
        DescriptionRole,
        FileCountRole,
        ForkCountRole,
        IsPublicRole,
        NodeIdRole,
        OwnerLoginRole,
        OwnerAvatarRole,
        PushedAtRole,
        StargazerCountRole,
        UpdatedAtRole
    };
    Q_ENUM(GistRoles)

    explicit GistsModel(QObject *parent = nullptr);
    ~GistsModel() override;

    void addGist(const GistListItem &gist);
    void addGists(const QList<GistListItem> &gists);
    void setGists(const QList<GistListItem> &gists);

private:
    QList<GistListItem> m_gists;

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

#endif // GISTSMODEL_H
