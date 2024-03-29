#ifndef OWNER_H
#define OWNER_H

#include "node.h"

class Owner : public Node
{
    Q_OBJECT

    Q_PROPERTY(QString avatarUrl READ avatarUrl WRITE setAvatarUrl NOTIFY avatarUrlChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)

public:
    explicit Owner(QObject *parent = nullptr);

    const QString &avatarUrl() const;
    const QString &login() const;

signals:
    void avatarUrlChanged();
    void loginChanged();

public slots:
    void setAvatarUrl(const QString &url);
    void setLogin(const QString &login);

private:
    QString m_avatarUrl;
    QString m_login;
};

#endif // OWNER_H
