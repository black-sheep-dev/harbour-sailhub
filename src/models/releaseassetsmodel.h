#ifndef RELEASEASSETSMODEL_H
#define RELEASEASSETSMODEL_H

#include "paginationmodel.h"

#include "src/entities/releaseasset.h"

class ReleaseAssetsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum ReleaseAssetRoles {
        ContentTypeRole             = Qt::UserRole + 1,
        CreatedAtRole,
        DownloadCountRole,
        DownloadUrlRole,
        NameRole,
        SizeRole,
        UpdatedAtRole
    };
    Q_ENUM(ReleaseAssetRoles)

    explicit ReleaseAssetsModel(QObject *parent = nullptr);

    void addReleaseAsset(const ReleaseAssetListItem &asset);
    void addReleaseAssets(const QList<ReleaseAssetListItem> &assets);
    void setReleaseAssets(const QList<ReleaseAssetListItem> &assets);

private:
    QList<ReleaseAssetListItem> m_assets;


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

#endif // RELEASEASSETSMODEL_H
