#ifndef FUNDINGLINK_H
#define FUNDINGLINK_H

#include <QObject>

struct FundingLinkListItem {
    FundingLinkListItem() = default;
    FundingLinkListItem(const QJsonObject &data);

    QString name;
    quint8 platform{0};
    QString url;
};

class FundingLink
{
    Q_GADGET

public:
    enum Platform {
        Undefined,
        CommunityBridge,
        Custom,
        GitHub,
        IssueHunt,
        KoFi,
        Liberpay,
        OpenCollective,
        Otechie,
        Patreon,
        Tidelift
    };
    Q_ENUM(Platform)
};

#endif // FUNDINGLINK_H
