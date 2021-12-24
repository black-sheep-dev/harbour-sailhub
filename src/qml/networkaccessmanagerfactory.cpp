#include "networkaccessmanagerfactory.h"

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>

QNetworkAccessManager *NetworkAccessManagerFactory::create(QObject *parent)
{
    auto cache = new QNetworkDiskCache(parent);
    cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/api");
    cache->setMaximumCacheSize(100000000);

    auto manager = new QNetworkAccessManager(parent);
    manager->setCache(cache);

    return manager;
}
