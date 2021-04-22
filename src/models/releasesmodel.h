#ifndef RELEASESMODEL_H
#define RELEASESMODEL_H

#include "paginationmodel.h"

#include "src/entities/release.h"

class ReleasesModel : public PaginationModel
{
    Q_OBJECT

public:
    enum ReleaseRoles {
        CreatedAtRole           = Qt::UserRole + 1,
        CreatedAtTimeSpanRole,
        IsLatestRole,
        NameRole,
        NodeIdRole
    };
    Q_ENUM(ReleaseRoles)

    explicit ReleasesModel(QObject *parent = nullptr);

    void addRelease(const ReleaseListItem &release);
    void addReleases(const QList<ReleaseListItem> &releases);
    void setReleases(const QList<ReleaseListItem> &releases);

private:
    QList<ReleaseListItem> m_releases;

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

#endif // RELEASESMODEL_H
