#include "releaseasset.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

ReleaseAssetListItem::ReleaseAssetListItem(const QJsonObject &data)
{
    contentType = data.value(ApiKey::CONTENT_TYPE).toString();
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    downloadCount = data.value(ApiKey::DOWNLOAD_COUNT).toInt();
    downloadUrl = data.value(ApiKey::DOWNLOAD_URL).toString();
    name = data.value(ApiKey::NAME).toString();
    size = data.value(ApiKey::SIZE).toInt();
    updatedAt = QDateTime::fromString(data.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
}
