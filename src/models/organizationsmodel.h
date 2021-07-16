#ifndef ORGANIZATIONSMODEL_H
#define ORGANIZATIONSMODEL_H

#include "paginationmodel.h"

#include "src/entities/organization.h"

class OrganizationsModel : public PaginationModel
{
    Q_OBJECT

public:
    enum OrganizationRoles {
        AvatarUrlRole        = Qt::UserRole,
        DescriptionRole,
        LoginRole,
        NameRole,
        NodeIdRole,
    };
    Q_ENUM(OrganizationRoles)

    explicit OrganizationsModel(QObject *parent = nullptr);
    ~OrganizationsModel() override;

    void addOrganization(const OrganizationListItem &organization);
    void addOrganizations(const QList<OrganizationListItem> &organizations);
    void setOrganizations(const QList<OrganizationListItem> &organizations);

private:
    QList<OrganizationListItem> m_organizations;

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;


    // PaginationModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
};

#endif // ORGANIZATIONSMODEL_H
