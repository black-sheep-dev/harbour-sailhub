#include "fundinglink.h"

#include <QJsonObject>

#include "src/api/keys.h"


FundingLinkListItem::FundingLinkListItem(const QJsonObject &data)
{
    const QString pf = data.value(ApiKey::PLATFORM).toString();

    if (pf == QLatin1String("COMMUNITY_BRIDGE")) {
        platform = FundingLink::CommunityBridge;
        name = QStringLiteral("CommunityBridge");
    } else if (pf == QLatin1String("GITHUB")) {
        platform = FundingLink::GitHub;
        name = QStringLiteral("GitHub");
    } else if (pf == QLatin1String("ISSUEHUNT")) {
        platform = FundingLink::IssueHunt;
        name = QStringLiteral("IssueHunt");
    } else if (pf == QLatin1String("KO_FI")) {
        platform = FundingLink::KoFi;
        name = QStringLiteral("Ko-fi");
    } else if (pf == QLatin1String("LIBERAPAY")){
        platform = FundingLink::Liberpay;
        name = QStringLiteral("Liberpay");
    } else if (pf == QLatin1String("OPEN_COLLECTIVE")) {
        platform = FundingLink::OpenCollective;
        name = QStringLiteral("OpenCollective");
    } else if (pf == QLatin1String("OTECHIE")) {
        platform = FundingLink::Otechie;
        name = QStringLiteral("Otechi");
    } else if (pf == QLatin1String("PATREON")) {
        platform = FundingLink::Patreon;
        name = QStringLiteral("Patreon");
    } else if (pf == QLatin1String("TIDELIFT")) {
        platform = FundingLink::Tidelift;
        name = QStringLiteral("Tidelift");
    } else {
        platform = FundingLink::Custom;
        name = QStringLiteral("Custom");
    }


    url = data.value(ApiKey::URL).toString();
}
