#include "organizationsmodel.h"

OrganizationsModel::OrganizationsModel(QObject *parent) :
    PaginationModel(parent)
{

}

void OrganizationsModel::addOrganization(const OrganizationListItem &organization)
{
    beginInsertRows(QModelIndex(), m_organizations.count(), m_organizations.count());
    m_organizations.append(organization);
    endInsertRows();
}

void OrganizationsModel::addOrganizations(const QList<OrganizationListItem> &organizations)
{
    beginInsertRows(QModelIndex(), m_organizations.count(), m_organizations.count() + organizations.count() - 1);
    m_organizations.append(organizations);
    endInsertRows();
}

void OrganizationsModel::setOrganizations(const QList<OrganizationListItem> &organizations)
{
    beginResetModel();
    m_organizations.clear();
    m_organizations = organizations;
    endResetModel();
}

QVariant OrganizationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto organization = m_organizations.at(index.row());

    switch (role) {
    case NameRole:
        return organization.name;

    case AvatarUrlRole:
        return organization.avatarUrl;

    case DescriptionRole:
        return organization.description;

    case LoginRole:
        return organization.login;

    case NodeIdRole:
        return organization.nodeId;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> OrganizationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AvatarUrlRole]        = "avatarUrl";
    roles[DescriptionRole]      = "description";
    roles[LoginRole]            = "login";
    roles[NameRole]             = "name";
    roles[NodeIdRole]           = "nodeId";

    return roles;
}

int OrganizationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_organizations.count();
}

void OrganizationsModel::clear()
{
    beginResetModel();
    m_organizations.clear();
    endResetModel();
}
