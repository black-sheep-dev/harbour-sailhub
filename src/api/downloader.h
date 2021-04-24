#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

#include <QNetworkAccessManager>

class Downloader : public QObject
{
    Q_OBJECT
public:
    enum Error {
        ErrorNone,
        ErrorInvalidDownloadUrl,
        ErrorDownloadFailed,
        ErrorWriteFile
    };
    Q_ENUM(Error)

    explicit Downloader(QNetworkAccessManager *manager, QObject *parent = nullptr);

signals:
    void downloadFailed(quint8 error, const QString &url);
    void downloadProgress(quint8 percentage, const QString &url);
    void finished(const QString &url);

public slots:
    void download(const QString &url, const QString &filename = QString());

private slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onFinished();

private:
    QNetworkAccessManager *m_manager{nullptr};
};

#endif // DOWNLOADER_H
