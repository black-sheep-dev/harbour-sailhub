#include "discussioncategory.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
DiscussionCategoryListItem::DiscussionCategoryListItem(const QJsonObject &data) :
    NodeListItem(data)
{
    emoji = DataUtils::getEmojiLinkFromString(data.value(ApiKey::EMOJI_HTML).toString());
    description = data.value(ApiKey::DESCRIPTION).toString();
}

// Object
DiscussionCategory::DiscussionCategory(QObject *parent) :
    QObject(parent)
{

}


