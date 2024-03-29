#include "owner.h"

Owner::Owner(QObject *parent) :
    Node(parent)
{

}

const QString &Owner::avatarUrl() const
{
    return m_avatarUrl;
}

const QString &Owner::login() const
{
    return m_login;
}

void Owner::setAvatarUrl(const QString &url)
{
    if (m_avatarUrl == url)
        return;

    m_avatarUrl = url;
    emit avatarUrlChanged();
}

void Owner::setLogin(const QString &login)
{
    if (m_login == login)
        return;

    m_login = login;
    emit loginChanged();
}
