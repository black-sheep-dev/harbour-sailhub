#include "discussioncategory.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
DiscussionCategoryListItem::DiscussionCategoryListItem(const QJsonObject &obj) :
    NodeListItem(obj)
{
    emoji = DataUtils::getEmojiLinkFromString(obj.value(ApiKey::EMOJI_HTML).toString());
    description = obj.value(ApiKey::DESCRIPTION).toString();
}

// Object
DiscussionCategory::DiscussionCategory(QObject *parent) :
    QObject(parent)
{

}


