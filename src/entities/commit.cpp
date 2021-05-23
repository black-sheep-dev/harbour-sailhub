#include "commit.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
CommitListItem::CommitListItem(const QJsonObject &obj) :
    NodeListItem(obj)
{
    const QJsonObject author = obj.value(ApiKey::COMMITTER).toObject().value(ApiKey::USER).toObject();

    authorAvatar = author.value(ApiKey::AVATAR_URL).toString();
    authorLogin = author.value(ApiKey::LOGIN).toString();
    messageHeadline = obj.value(ApiKey::MESSAGE_HEADLINE).toString();
    pushedAtTimeSpan = DataUtils::timeSpanText(QDateTime::fromString(obj.value(ApiKey::COMMITTER).toObject().value(ApiKey::DATE).toString(), Qt::ISODate), true);
}

// Object
Commit::Commit(QObject *parent) :
    Node(parent)
{

}

