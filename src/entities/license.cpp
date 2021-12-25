#include "license.h"

License::License(QObject *parent) :
    QObject(parent)
{

}

const QString &License::name() const
{
    return m_name;
}

const QString &License::url() const
{
    return m_url;
}

void License::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

void License::setUrl(const QString &url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged();
}
