#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>

class License : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
    explicit License(QObject *parent = nullptr);

    const QString &name() const;
    const QString &url() const;

signals:
    void nameChanged();
    void urlChanged();

public slots:
    void setName(const QString &name);
    void setUrl(const QString &url);

private:
    QString m_name;
    QString m_url;
};

#endif // LICENSE_H
