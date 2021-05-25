#ifndef RELEASEASSET_H
#define RELEASEASSET_H

#include <QDateTime>
#include <QJsonObject>

struct ReleaseAssetListItem {
    ReleaseAssetListItem() = default;
    ReleaseAssetListItem(const QJsonObject &data);

    QString contentType;
    QDateTime createdAt;
    quint32 downloadCount{0};
    QString downloadUrl;
    QString name;
    quint32 size;
    QDateTime updatedAt;
};

#endif // RELEASEASSET_H
