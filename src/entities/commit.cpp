#include "commit.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
CommitListItem::CommitListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    const QJsonObject author = data.value(ApiKey::COMMITTER).toObject().value(ApiKey::USER).toObject();

    authorAvatar = author.value(ApiKey::AVATAR_URL).toString();
    authorLogin = author.value(ApiKey::LOGIN).toString();
    messageHeadline = data.value(ApiKey::MESSAGE_HEADLINE).toString();
    pushedAtTimeSpan = DataUtils::timeSpanText(QDateTime::fromString(data.value(ApiKey::COMMITTER).toObject().value(ApiKey::DATE).toString(), Qt::ISODate), true);
}

// Object
Commit::Commit(QObject *parent) :
    Node(parent)
{

}

