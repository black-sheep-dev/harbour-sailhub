#include "downloader.h"

#ifdef QT_DEBUG
    #include <QDebug>
#endif

#include <QFile>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QStandardPaths>

Downloader::Downloader(QNetworkAccessManager *manager, QObject *parent) :
    QObject(parent),
    m_manager(manager)
{

}

void Downloader::download(const QString &url, const QString &filename)
{
#ifdef QT_DEBUG
    qDebug() << "DOWNLOAD: " << url;
#endif

    if (url.isEmpty()) {
        emit downloadFailed(ErrorInvalidDownloadUrl, url);
        return;
    }

    QNetworkRequest request(url);
    request.setMaximumRedirectsAllowed(10);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    auto reply = m_manager->get(request);
    reply->setProperty("url", url);
    reply->setProperty("filename", filename);
    connect(reply, &QNetworkReply::finished, this, &Downloader::onFinished);
    connect(reply, &QNetworkReply::downloadProgress, this, &Downloader::onDownloadProgress);
}

void Downloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    auto reply = qobject_cast<QNetworkReply *>(sender());

    if (reply == nullptr)
        return;

    const QString url = reply->property("url").toString();
    quint8 percentage = qRound(double(bytesReceived / bytesTotal) * 100);

    emit downloadProgress(percentage, url);
}

void Downloader::onFinished()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());

    if (reply == nullptr)
        return;

     const QString url = reply->property("url").toString();
     QString fileName = reply->property("filename").toString();

#ifdef QT_DEBUG
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << url;
#endif

    const QString redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
    if (!redirectUrl.isEmpty()) {
#ifdef QT_DEBUG
        qDebug() << "REDIRECT: " << redirectUrl;
#endif
        download(redirectUrl, fileName);
        reply->deleteLater();
        return;
    }

    if (reply->error()) {
        reply->deleteLater();
        emit downloadFailed(ErrorDownloadFailed, url);
        return;
    }

    // save file
    if (fileName.isEmpty())
        fileName = url.split('/').last();

    fileName = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + fileName;
    QString name = fileName;

    int count{2};
    while (QFile(name).exists()) {
        name = fileName + QStringLiteral("(%1)").arg(count);
        count++;
    }

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly)) {
        emit downloadFailed(ErrorWriteFile, url);
        return;
    }

    file.write(reply->readAll());
    file.close();

    // cleanup
    reply->deleteLater();

    // finish
    emit finished(url);
}
