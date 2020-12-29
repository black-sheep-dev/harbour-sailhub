#include "license.h"

License::License(QObject *parent) :
    QObject(parent)
{

}

QString License::name() const
{
    return m_name;
}

QString License::url() const
{
    return m_url;
}

void License::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void License::setUrl(const QString &url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged(m_url);
}
