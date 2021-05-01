#ifndef FUNDINGLINKSMODEL_H
#define FUNDINGLINKSMODEL_H

#include "basemodel.h"

#include "src/entities/fundinglink.h"

class FundingLinksModel : public BaseModel
{
    Q_OBJECT

public:
    enum FundingLinkRoles {
        NameRole        = Qt::UserRole + 1,
        PlatformRole,
        UrlRole
    };
    Q_ENUM(FundingLinkRoles)

    explicit FundingLinksModel(QObject *parent = nullptr);

    void setFundingLinks(const QList<FundingLinkListItem> &links);
private:
    QList<FundingLinkListItem> m_links;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // BaseModel interface
public:
    void clear() override;
    void parseQueryResult(const QJsonObject &data) override;
    GraphQLQuery query() const override;
};

#endif // FUNDINGLINKSMODEL_H
