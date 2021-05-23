#include "releaseasset.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

ReleaseAssetListItem::ReleaseAssetListItem(const QJsonObject &obj)
{
    contentType = obj.value(ApiKey::CONTENT_TYPE).toString();
    createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    downloadCount = obj.value(ApiKey::DOWNLOAD_COUNT).toInt();
    downloadUrl = obj.value(ApiKey::DOWNLOAD_URL).toString();
    name = obj.value(ApiKey::NAME).toString();
    size = obj.value(ApiKey::SIZE).toInt();
    updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
}
